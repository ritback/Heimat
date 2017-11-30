#include "HE_Kinect.h"

HEDepthStreamHandlerInterface::HEDepthStreamHandlerInterface()
{

}

HEDepthStreamHandlerInterface::~HEDepthStreamHandlerInterface()
{

}

// -----------------------------------------------------------------------------
HESkeletonsStreamHandlerInterface::HESkeletonsStreamHandlerInterface()
{

}

HESkeletonsStreamHandlerInterface::~HESkeletonsStreamHandlerInterface()
{

}

// -----------------------------------------------------------------------------
HEKinectStreamHandler::HEKinectStreamHandler(INuiSensor *inKinect, NUI_IMAGE_RESOLUTION inStreamResolution)
    : mKinect(inKinect)
    , mGreyLevelMax(255)
    , mGreyLevelMin(0)
    , mStreamResolution()
{
    if (mKinect)
    {
        switch (inStreamResolution)
        {
        case NUI_IMAGE_RESOLUTION_80x60:
            mStreamResolution = ofPoint(80, 60);
            break;
        case NUI_IMAGE_RESOLUTION_320x240:
            mStreamResolution = ofPoint(320, 240);
            break;
        case NUI_IMAGE_RESOLUTION_640x480:
            mStreamResolution = ofPoint(640, 480);
            break;
        case NUI_IMAGE_RESOLUTION_1280x960:
            mStreamResolution = ofPoint(1280, 960);
            break;
        default:
            mStreamResolution = ofPoint(640, 480);
            break;
        }

        // Create an event that will be signaled when skeleton data is available
            

        mNextDepthFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        mNextSkeletonEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        mKinect->NuiImageStreamOpen(NUI_IMAGE_TYPE_DEPTH,
                                     inStreamResolution,
                                     0,
                                     2,
                                     mNextDepthFrameEvent,
                                     &mDepthStreamHandle);
        mKinect->NuiSkeletonTrackingEnable(mNextSkeletonEvent, 0);
    }
}

HEKinectStreamHandler::~HEKinectStreamHandler()
{
    if (mNextDepthFrameEvent && (mNextDepthFrameEvent != INVALID_HANDLE_VALUE))
    {
        CloseHandle(mNextDepthFrameEvent);
    }
    if (mNextSkeletonEvent && (mNextSkeletonEvent != INVALID_HANDLE_VALUE))
    {
        CloseHandle(mNextSkeletonEvent);
    }
}

// -----------------------------------------------------------------------------
void HEKinectStreamHandler::streamDepthTo(HEDepthStreamHandlerInterface* inToStream,
                                  ofPixels* inDepthChannel,
                                  float inWaitingTime)
{
   
    HRESULT hr = S_OK;
    NUI_IMAGE_FRAME imageFrame;

    hr = mKinect->NuiImageStreamGetNextFrame(mDepthStreamHandle, 0, &imageFrame);
    if (hr != S_OK)
    {
        return;
    }

    BOOL nearMode = false;
    INuiFrameTexture* pTexture = 0;// imageFrame.pFrameTexture;
    
    hr = mKinect->NuiImageFrameGetDepthImagePixelFrameTexture(
        mDepthStreamHandle, &imageFrame, &nearMode, &pTexture);

    if (FAILED(hr))
    {
        mKinect->NuiImageStreamReleaseFrame(mDepthStreamHandle, &imageFrame);
    }
    

    NUI_LOCKED_RECT LockedRect;
    pTexture->LockRect(0, &LockedRect, NULL, 0);

    if (LockedRect.Pitch != 0)
    {
        int minDepth = (nearMode ? NUI_IMAGE_DEPTH_MINIMUM_NEAR_MODE : NUI_IMAGE_DEPTH_MINIMUM) >> NUI_IMAGE_PLAYER_INDEX_SHIFT;
        int maxDepth = (nearMode ? NUI_IMAGE_DEPTH_MAXIMUM_NEAR_MODE : NUI_IMAGE_DEPTH_MAXIMUM) >> NUI_IMAGE_PLAYER_INDEX_SHIFT;

        const NUI_DEPTH_IMAGE_PIXEL * pBufferRun = reinterpret_cast<const NUI_DEPTH_IMAGE_PIXEL *>(LockedRect.pBits);
        const NUI_DEPTH_IMAGE_PIXEL * pBufferEnd = pBufferRun + (inDepthChannel->getWidth() * inDepthChannel->getHeight());

        float factor = (float) mGreyLevelMax / (maxDepth - minDepth);
        float coordOrigin = mGreyLevelMin - factor * minDepth;

        int pixelIndex = 0;

        USHORT depth;
        while (pBufferRun < pBufferEnd)
        {
            depth = pBufferRun->depth; // get depth from player index
            char kinectGreyLevel = (char) (factor * depth + coordOrigin);
            inToStream->setPixel(inDepthChannel, pixelIndex, kinectGreyLevel);

            ++pixelIndex;
            ++pBufferRun;
        }
    }

    pTexture->UnlockRect(0);
    pTexture->Release();

    mKinect->NuiImageStreamReleaseFrame(mDepthStreamHandle, &imageFrame);
}

// -----------------------------------------------------------------------------
void HEKinectStreamHandler::streamSkeletonsTo(HESkeletonsStreamHandlerInterface* inToStream,
                                      float inWaitingTime)
{

    NUI_SKELETON_FRAME skeletonFrame = { 0 };

    HRESULT hr = mKinect->NuiSkeletonGetNextFrame(10, &skeletonFrame);
    if (FAILED(hr))
    {
        return;
    }

    // smooth out the skeleton data
    mKinect->NuiTransformSmooth(&skeletonFrame, NULL);

    inToStream->processSkeletons(skeletonFrame);
}

// -----------------------------------------------------------------------------
ofPoint HEKinectStreamHandler::getStreamResolution()
{
    return mStreamResolution;
}

// -----------------------------------------------------------------------------
void HEKinectStreamHandler::setGreyLevelMax(float inGreyLevelMax)
{
    mGreyLevelMax = inGreyLevelMax;
}

void HEKinectStreamHandler::setGreyLevelMin(float inGreyLevelMin)
{
    mGreyLevelMin = inGreyLevelMin;
}

// -----------------------------------------------------------------------------
int HEKinect::mSensorIndex = 0;

HEKinect::HEKinect(bool bGetSkeleton, bool bGetDepthImage)
	: mNuiSensor(0)
	, mStreamHandler(0)
{
    mIsConnected = createFirstConnected(bGetSkeleton, bGetDepthImage);
	mStreamHandler = new HEKinectStreamHandler(mNuiSensor);
}

HEKinect::~HEKinect()
{
    if (mNuiSensor != NULL)
    {
        mNuiSensor->NuiShutdown();
        mNuiSensor->Release();
        mNuiSensor = NULL;
        delete mStreamHandler;
    }
}

// -----------------------------------------------------------------------------
HEKinectStreamHandler* HEKinect::getStreamHandler()
{
    return mStreamHandler;
}

// -----------------------------------------------------------------------------
bool HEKinect::isAvailable()
{
    if (mIsConnected && mNuiSensor)
    {
        return true;
    }
    return false;
}

// -----------------------------------------------------------------------------
int HEKinect::getSensorNumber()
{
    int iSensorCount = 0;
    HRESULT hr = NuiGetSensorCount(&iSensorCount);
    if(hr != S_OK)
        iSensorCount = -1;
    return iSensorCount;
}

// -----------------------------------------------------------------------------
bool HEKinect::createFirstConnected(bool bGetSkeleton, bool bGetDepthImage)
{
    INuiSensor * nuiSensor = 0;

    int iSensorCount = 0;
    HRESULT hr = NuiGetSensorCount(&iSensorCount);
    if (hr != S_OK) return false;

    hr = NuiCreateSensorByIndex(mSensorIndex, &nuiSensor);
    if(hr != S_OK || nuiSensor == 0) return false;

    ++mSensorIndex;

    if (nuiSensor != NULL && nuiSensor->NuiStatus() == S_OK)
    {
        mNuiSensor = nuiSensor;
        DWORD fNuiInitializeFlag = 0;
        if(bGetSkeleton)
            fNuiInitializeFlag |= NUI_INITIALIZE_FLAG_USES_SKELETON;
        if(bGetDepthImage)
            fNuiInitializeFlag |= NUI_INITIALIZE_FLAG_USES_DEPTH;

        if (fNuiInitializeFlag == 0) return false;

        hr = mNuiSensor->NuiInitialize(fNuiInitializeFlag);
    }
    else
    {
        if (nuiSensor)
            nuiSensor->Release();
        return false;
    }
    return true;
}
