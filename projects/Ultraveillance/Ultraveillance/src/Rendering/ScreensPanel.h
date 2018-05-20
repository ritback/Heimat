#pragma once

#include "ofMain.h"
#include "MultiCamera/MultiCamera.h"
#include <vector>

class StreamAnalysisAndDisplay;

class ScreensPanel
{
public:
    ScreensPanel(int inImgsCaptureWidth, int inImgsCaptureHeight);
    ~ScreensPanel();

public:
    void update();
    void draw();

public:
    void drawImgs();
    void drawAnalysisResults();
    void drawExtractedROIs();
    void drawCameras();

public:
    void needUpdateCamsDevices();
    
public:
    void setDrawingsWidth(float inDimension);
    float getDrawingsWidth();
    void setDrawingsHeight(float inDimension);
    float getDrawingsHeight();

    void setDrawingsColumnsPos(float* inDimension);
    void setDrawingsLinesPos(float* inDimension);
    float* getDrawingsColumnsPos();
    float* getDrawingsLinesPos();

    void updateDrawingsPosition();

private:
    // randomize array of display index
    void randomizeDisplays();

private:
    // Update the number of analysis needed for cams if needed.
    // assign analysis to cams.
    void resyncCamDevices();

private:
    static const int NUM_SCREENS = 9;

private:
    typedef std::vector<StreamAnalysisAndDisplay*> Streams;
    typedef Streams::iterator StreamsIt;
    // each stream is associated to a cam and is responsible for its analysis and display
    Streams mStreams;

private:
    MultiCamera mCams;

private:
    int mRandomDisplayIndexes[NUM_SCREENS];

private:
    int mImgsCaptureWidth;
    int mImgsCaptureHeight;

private:
    ofPoint mDrawingsPositions[NUM_SCREENS];
    float mDrawingsWidth;
    float mDrawingsHeight;
    float mColumnsPosX[3];
    float mLinesPosY[3];

private: // update Camera from time to time and check if the number of Cam changed
    void checkResyncDevicesNeeded(float inEllapsedTime);
    int mPreviousNumCamDevices;
    float mTimeToCheckIfResyncNeeded;

private:
    void checkTimeToShuffleDisplays(float inEllapsedTime);
    float mTimeToShuffleDisplays;

};
