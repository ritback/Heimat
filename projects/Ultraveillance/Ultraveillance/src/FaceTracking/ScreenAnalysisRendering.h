#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ScreenAnalysisRendering
{
public:
    ScreenAnalysisRendering(int inImgCaptureWidth, int inImgCaptureHeight,
                    ofVideoGrabber* inAssociatedCam = 0);
    virtual ~ScreenAnalysisRendering();

public:
    virtual void updateImg();
    virtual void processFaceTracking();

public:
    virtual void drawImg(float inX, float inY, float inWidth = 0, float inHeight = 0);
    virtual void drawFacesRecognition(float inX, float inY, float inWidth = 0, float inHeight = 0);

public:
    virtual void drawROI(float inX, float inY, float inWidth = 0, float inHeight = 0);

public:
    void setCam(ofVideoGrabber* inCam);
    ofVideoGrabber* getCam();

private:
    ofxCvColorImage mColorCVImage;
    ofxCvGrayscaleImage mGrayCVProcessingImage;
    ofTexture mROITexture;

private:
    ofxCvHaarFinder mCVHaarFinder;

private:
    int mImgCaptureWidth;
    int mImgCaptureHeight;

private:
    ofVideoGrabber* mAssociatedCam;

};
