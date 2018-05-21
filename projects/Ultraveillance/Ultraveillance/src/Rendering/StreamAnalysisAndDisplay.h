#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "HaarFaceTracking.h"
#include "Yolo2ObjRecognition.h"

class StreamAnalysisAndDisplay
{
public:
    StreamAnalysisAndDisplay(int inImgCaptureWidth, int inImgCaptureHeight,
                    ofVideoGrabber* inAssociatedCam = 0);
    ~StreamAnalysisAndDisplay();

public:
    void updateCVImg();
    void processAnalysis();

public:
    void drawImg(float inX, float inY, float inWidth = 0, float inHeight = 0);
    void drawAnalysisResults(float inX, float inY, float inWidth = 0, float inHeight = 0);
    void drawExtractedROIs(float inX, float inY, float inWidth = 0, float inHeight = 0);

public:
    void setCam(ofVideoGrabber* inCam);
    ofVideoGrabber* getCam();

private:
    ofxCvColorImage mColorCVImage;
    ofxCvGrayscaleImage mGrayCVProcessingImage;
    ofTexture mROITexture;
    ofPixels* mCamPixels;

private: // analysis
    HaarFaceTracking mFaceTracker;
    Yolo2ObjRecognition mObjectRecognition;

private:
    void printAPerson();
    void savePersonROIToDir(ofRectangle& inROI);
    static float mTimeToPrintAPerson;

private:
    int mImgCaptureWidth;
    int mImgCaptureHeight;

private:
    ofVideoGrabber* mAssociatedCam;

};
