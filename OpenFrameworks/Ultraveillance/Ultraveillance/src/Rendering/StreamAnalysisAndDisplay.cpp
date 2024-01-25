#include "StreamAnalysisAndDisplay.h"

static float sPrintingFrequency = 5 * 1000;
float StreamAnalysisAndDisplay::mTimeToPrintAPerson = sPrintingFrequency;

//------------------------------------------------------------------------------
StreamAnalysisAndDisplay::StreamAnalysisAndDisplay(int inImgCaptureWidth, int inImgCaptureHeight,
                                                 ofVideoGrabber * inAssociatedCam)
    : mImgCaptureWidth(inImgCaptureWidth)
    , mImgCaptureHeight(inImgCaptureHeight)
    , mAssociatedCam(inAssociatedCam)
    , mCamPixels(0)
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
            mCamPixels = &(mAssociatedCam->getPixels());
        }
    }
}

void StreamAnalysisAndDisplay::processAnalysis()
{
    mFaceTracker.process(mGrayCVProcessingImage);
    mObjectRecognition.process(mCamPixels);

    printAPerson();
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

    //--------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------
    ofNoFill();
    
    for(auto& r : mObjectRecognition.mLastResults)
    {
        ofSetLineWidth(ofMap(r.prob, 0, 1, 0, 5));

        ofRectangle cur(r.x, r.y, r.w, r.h);
        cur.x *= widthRatio;
        cur.y *= heightRatio;
        cur.width *= widthRatio;
        cur.height *= heightRatio;
        cur.x += inX;
        cur.y += inY;
        ofDrawRectangle(cur.x, cur.y, cur.width, cur.height);

        ofDrawBitmapStringHighlight(mObjectRecognition.mYolo.getName(r.obj_id) + ": " + ofToString(r.prob), cur.x, cur.y);

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


//------------------------------------------------------------------------------
void StreamAnalysisAndDisplay::printAPerson()
{
    float ellapsedTime = ofGetElapsedTimeMillis();

    if(mTimeToPrintAPerson < ellapsedTime)
    {
        // If a person with probal > 0.95 is found.
        // save the subsection as PNG.
        // reset timer.

        for(auto& r : mObjectRecognition.mLastResults)
        {
            if(mObjectRecognition.mYolo.getName(r.obj_id) == "person" && r.prob > 0.9)
            {
                ofRectangle cur(r.x, r.y, r.w, r.h);
                savePersonROIToDir(cur);
                mTimeToPrintAPerson = ellapsedTime + sPrintingFrequency;
                return;
            }
        }
    }
}

void StreamAnalysisAndDisplay::savePersonROIToDir(ofRectangle& inROI)
{
    printf("printing someone\n");
    static int index = 0;
    std::ostringstream destination;
    destination << "C:\\Users\\Henri\\Google Drive\\Tycrois\\Ultraveillance\\TempPersonsImg\\";
    destination << "APerson";
    destination << index;
    destination << ".png";
    std::string destinationStr = destination.str();

    ofImage ToCrop(mGrayCVProcessingImage.getPixels());
    ofImage APersonROISubsection;
    APersonROISubsection.cropFrom(ToCrop, inROI.x, inROI.y, inROI.width, inROI.height);
    APersonROISubsection.save(destinationStr);
    ++index;
}
