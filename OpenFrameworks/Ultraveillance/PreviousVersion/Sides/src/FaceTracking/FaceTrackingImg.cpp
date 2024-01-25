#include "FaceTrackingImg.h"

//------------------------------------------------------------------------------
FaceTrackingImg::FaceTrackingImg(int inImgCaptureWidth, int inImgCaptureHeight, ofVideoGrabber * inAssociatedCam)
    : mImgCaptureWidth(inImgCaptureWidth)
    , mImgCaptureHeight(inImgCaptureHeight)
    , mAssociatedCam(inAssociatedCam)
{
    mColorCVImage.allocate(mImgCaptureWidth, mImgCaptureHeight);
    mGrayCVProcessingImage.allocate(mImgCaptureWidth, mImgCaptureHeight);
    mGrayCVProcessingImage.setUseTexture(true);

    mCVHaarFinder.setup("haarcascade_frontalface_default.xml");
}

FaceTrackingImg::~FaceTrackingImg()
{
    
}

//------------------------------------------------------------------------------
void FaceTrackingImg::updateImg()
{
    if (mAssociatedCam)
    {
        //if (mAssociatedCam->isFrameNew())
        {
            mColorCVImage.setFromPixels(mAssociatedCam->getPixels());
            mGrayCVProcessingImage = mColorCVImage;
            mROITexture = mGrayCVProcessingImage.getTexture();
        }
    }
}

void FaceTrackingImg::processFaceTracking()
{
    mCVHaarFinder.findHaarObjects(mGrayCVProcessingImage, 10, 10);
}

//------------------------------------------------------------------------------
void FaceTrackingImg::drawImg(float inX, float inY, float inWidth, float inHeight)
{
    if (inWidth == 0) inWidth = mImgCaptureWidth;
    if (inHeight == 0) inHeight = mImgCaptureHeight;

    mGrayCVProcessingImage.draw(inX, inY, inWidth, inHeight);
}

void FaceTrackingImg::drawFacesRecognition(float inX, float inY, float inWidth, float inHeight)
{
    if (inWidth == 0) inWidth = mImgCaptureWidth;
    if (inHeight == 0) inHeight = mImgCaptureHeight;

    ofPushStyle();
    ofNoFill();
    ofSetColor(255);

    float widthRatio = inWidth / mImgCaptureWidth;
    float heightRatio = inHeight / mImgCaptureHeight;

    for (unsigned int i = 0; i < mCVHaarFinder.blobs.size(); i++)
    {
        ofRectangle cur = mCVHaarFinder.blobs[i].boundingRect;
        cur.x *= widthRatio;
        cur.y *= heightRatio;
        cur.width *= widthRatio;
        cur.height *= heightRatio;
        cur.x += inX;
        cur.y += inY;
        ofDrawRectangle(cur.x, cur.y, cur.width, cur.height);
    }

    ofPopStyle();
}

void FaceTrackingImg::drawROI(float inX, float inY, float inWidth, float inHeight)
{
    if (inWidth == 0) inWidth = mImgCaptureWidth / 4;
    if (inHeight == 0) inHeight = mImgCaptureHeight / 4;

    for (unsigned int i = 0; i < mCVHaarFinder.blobs.size(); i++)
    {
        ofRectangle cur = mCVHaarFinder.blobs[i].boundingRect;        
        mROITexture.drawSubsection(inX, inY + i * inHeight,
                                   inWidth, inHeight,
                                   cur.x, cur.y,
                                   cur.width, cur.height);
    }
}

//------------------------------------------------------------------------------
void FaceTrackingImg::setCam(ofVideoGrabber* inCam)
{
    mAssociatedCam = inCam;
}

ofVideoGrabber* FaceTrackingImg::getCam()
{
    return mAssociatedCam;
}
