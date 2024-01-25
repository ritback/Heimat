#include "HE_SkeletonsTracker.h"

template<class SkeletonType>
HESkeletonsTracker<SkeletonType>::HESkeletonsTracker(HEKinect* inKinect)
    : mKinect(inKinect)
{

}

template<class SkeletonType>
HESkeletonsTracker<SkeletonType>::~HESkeletonsTracker()
{

}

// -----------------------------------------------------------------------------
template<class SkeletonType>
void HESkeletonsTracker<SkeletonType>::update()
{
    HEKinectStreamHandler* stream = mKinect->getStreamHandler();
    stream->streamSkeletonsTo(this, 1);

    /*
    // to be called in class redefinition
    SkeletonType *currentSkeleton = &mTrackedSkeletons[0];
    for (int i = 0; i < NUI_SKELETON_COUNT; ++i)
    {
        if (currentSkeleton->mTrackingState == NUI_SKELETON_TRACKED)
        {
            currentSkeleton->update();
        }
        ++currentSkeleton;
    }
    */
}

// -----------------------------------------------------------------------------
template<class SkeletonType>
void HESkeletonsTracker<SkeletonType>::render()
{
    SkeletonType *currentSkeleton = &mTrackedSkeletons[0];
    for (int i = 0; i < NUI_SKELETON_COUNT; ++i)
    {
        if (currentSkeleton->mTrackingState == NUI_SKELETON_TRACKED)
        {
            currentSkeleton->drawSkeleton();
        }
        ++currentSkeleton;
    }
}

// -----------------------------------------------------------------------------
template<class SkeletonType>
void HESkeletonsTracker<SkeletonType>::processSkeletons(NUI_SKELETON_FRAME& skeletonFrame)
{
    SkeletonType *currentSkeleton = &mTrackedSkeletons[0];
    HESkeletonJoint aJoint{};
    for (int i = 0; i < NUI_SKELETON_COUNT; ++i)
    {
        currentSkeleton->mTrackingState = NUI_SKELETON_NOT_TRACKED;
        NUI_SKELETON_TRACKING_STATE trackingState = skeletonFrame.SkeletonData[i].eTrackingState;
        if (trackingState == NUI_SKELETON_TRACKED)
        {
            currentSkeleton->mTrackingState = NUI_SKELETON_TRACKED;
            NUI_SKELETON_DATA *skeletonData = &(skeletonFrame.SkeletonData[i]);
            for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; ++j)
            {
                aJoint.mTrackingState = skeletonData->eSkeletonPositionTrackingState[j];
                aJoint.mPos = skeletonToScreen(skeletonFrame.SkeletonData[i].SkeletonPositions[j],
                                                 ofGetWindowWidth(), ofGetWindowHeight());
                aJoint.mPositionIndex = j;
                currentSkeleton->updateJoint(&aJoint);
            }
        }
        else if (trackingState == NUI_SKELETON_POSITION_ONLY)
        {
            currentSkeleton->mTrackingState = NUI_SKELETON_POSITION_ONLY;
        }
        else
        {
            currentSkeleton->mTrackingState = NUI_SKELETON_NOT_TRACKED;
        }
        ++currentSkeleton;
    }
}

// -----------------------------------------------------------------------------
template<class SkeletonType>
void HESkeletonsTracker<SkeletonType>::getHeadsJoints(HESkeletonJoint* outJoints, int* outSize)
{
    *outSize = 0;
    SkeletonType *currentSkeleton = &mTrackedSkeletons[0];
    HESkeletonJoint aJoint{};
    for (int i = 0; i < NUI_SKELETON_COUNT; ++i)
    {
        if (currentSkeleton->mTrackingState == NUI_SKELETON_TRACKED)
        {
            outJoints[*outSize].copy(currentSkeleton->getHeadJoint());
            ++(*outSize);
        }
        ++currentSkeleton;
    }
}

// -----------------------------------------------------------------------------
template<class SkeletonType>
ofPoint HESkeletonsTracker<SkeletonType>::skeletonToScreen(Vector4 inSkeletonPoint,
                                                         float inScreenWidth,
                                                         float inScreenHeight)
{
    LONG x, y;
    USHORT depth;

    NUI_IMAGE_RESOLUTION res = NUI_IMAGE_RESOLUTION_320x240;
    NuiTransformSkeletonToDepthImage(inSkeletonPoint, &x, &y, &depth, res);

    float screenPointX = static_cast<float>(x * inScreenWidth);
    float screenPointY = static_cast<float>(y * inScreenHeight);
    float depthPointZ = static_cast<float>(depth);

    switch (res)
    {
        case NUI_IMAGE_RESOLUTION_80x60:
            screenPointX /= 80;
            screenPointY /= 60;
            break;
        case NUI_IMAGE_RESOLUTION_320x240:
            screenPointX /= 320;
            screenPointY /= 240;
            break;
        case NUI_IMAGE_RESOLUTION_640x480:
            screenPointX /= 640;
            screenPointY /= 480;
            break;
        case NUI_IMAGE_RESOLUTION_1280x960:
            screenPointX /= 1280;
            screenPointY /= 960;
            break;
    }

    return ofPoint(screenPointX, screenPointY, depthPointZ);
}
