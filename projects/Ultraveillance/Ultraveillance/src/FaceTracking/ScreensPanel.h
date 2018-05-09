#pragma once

#include "ofMain.h"
#include "MultiCamera/MultiCamera.h"
#include <vector>

class ScreenAnalysisRendering;

class ScreensPanel
{
public:
    ScreensPanel(int inImgsCaptureWidth, int inImgsCaptureHeight);
    ~ScreensPanel();

public:
    void update();

public:
    void drawImgs();
    void drawFacesRecognition();
    void drawROIs();
    void drawCameras();

public:
    void needUpdateCamsDevices();
    void setNumSimultaneousFaceTracking(int inNum);
    int getNumSimultaneousFaceTracking();
    
    void setDrawingsWidth(float inDimension);
    float getDrawingsWidth();
    void setDrawingsHeight(float inDimension);
    float getDrawingsHeight();

    void setDrawingsColumnsPos(float* inDimension);
    void setDrawingsLinesPos(float* inDimension);
    float* getDrawingsColumnsPos();
    float* getDrawingsLinesPos();

private:
    void bindCamsToImgs();

private:
    void updateDrawingsPosition();

private:
    static const int NUM_IMGS = 9;
    typedef std::vector<ScreenAnalysisRendering*> Screens;
    typedef Screens::iterator ScreensIt;
    Screens mScreens;

private:
    MultiCamera mCams;

private:
    int mImgsCaptureWidth;
    int mImgsCaptureHeight;

private:
    ofPoint mDrawingsPositions[NUM_IMGS];
    float mDrawingsWidth;
    float mDrawingsHeight;
    float mColumnsPosX[3];
    float mLinesPosY[3];

private:
    unsigned int mNumSimultaneousFaceTracking;
    unsigned int mCurrentImgFaceTrackingIndex;

private:
    bool mUpdateCamsDevices;
    int mNumCamDevice;
    float mTimeToCheckCams;

private:
    float mTimeToShuffleCams;

};
