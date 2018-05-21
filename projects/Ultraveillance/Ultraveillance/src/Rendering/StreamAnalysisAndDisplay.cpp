#include "StreamAnalysisAndDisplay.h"

//------------------------------------------------------------------------------
StreamAnalysisAndDisplay::StreamAnalysisAndDisplay(int inImgCaptureWidth, int inImgCaptureHeight,
                                                 ofVideoGrabber * inAssociatedCam)
    : mImgCaptureWidth(inImgCaptureWidth)
    , mImgCaptureHeight(inImgCaptureHeight)
    , mAssociatedCam(inAssociatedCam)
{
    mColorCVImage.allocate(mImgCaptureWidth, mImgCaptureHeight);
    mGrayCVProcessingImage.allocate(mImgCaptureWidth, mImgCaptureHeight);
    mGrayCVProcessingImage.setUseTexture(true);

}

StreamAnalysisAndDisplay::~StreamAnalysisAndDisplay()
{
    
}

//------------------------------------------------------------------------------
void StreamAnalysisAndDisplay::updateCVImg()
{
    if (mAssociatedCam)
    {
        if (mAssociatedCam->isFrameNew())
        {
            mColorCVImage.setFromPixels(mAssociatedCam->getPixels());
            mGrayCVProcessingImage = mColorCVImage;
            mROITexture = mGrayCVProcessingImage.getTexture();
        }
    }
}

void StreamAnalysisAndDisplay::processAnalysis()
{
    mFaceTracker.process(mGrayCVProcessingImage);
}

//------------------------------------------------------------------------------
void StreamAnalysisAndDisplay::drawImg(float inX, float inY, float inWidth, float inHeight)
{
    if (inWidth == 0) inWidth = mImgCaptureWidth;
    if (inHeight == 0) inHeight = mImgCaptureHeight;

    mGrayCVProcessingImage.draw(inX, inY, inWidth, inHeight);
}

void StreamAnalysisAndDisplay::drawAnalysisResults(float inX, float inY, float inWidth, float inHeight)
{
    if (inWidth == 0) inWidth = mImgCaptureWidth;
    if (inHeight == 0) inHeight = mImgCaptureHeight;

    ofPushStyle();
    ofNoFill();
    ofSetColor(255);

    float widthRatio = inWidth / mImgCaptureWidth;
    float heightRatio = inHeight / mImgCaptureHeight;

    for (unsigned int i = 0; i < mFaceTracker.mCVHaarFinder.blobs.size(); i++)
    {
        ofRectangle cur(mFaceTracker.mCVHaarFinder.blobs[i].boundingRect);
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

void StreamAnalysisAndDisplay::drawExtractedROIs(float inX, float inY, float inWidth, float inHeight)
{
    if (inWidth == 0) inWidth = mImgCaptureWidth / 4;
    if (inHeight == 0) inHeight = mImgCaptureHeight / 4;

    for(unsigned int i = 0; i < mFaceTracker.mCVHaarFinder.blobs.size(); i++)
    {
        ofRectangle cur(mFaceTracker.mCVHaarFinder.blobs[i].boundingRect);
        mROITexture.drawSubsection(inX, inY + i * inHeight,
                                   inWidth, inHeight,
                                   cur.x, cur.y,
                                   cur.width, cur.height);
    }
}

//------------------------------------------------------------------------------
void StreamAnalysisAndDisplay::setCam(ofVideoGrabber* inCam)
{
    mAssociatedCam = inCam;
}

ofVideoGrabber* StreamAnalysisAndDisplay::getCam()
{
    return mAssociatedCam;
}
