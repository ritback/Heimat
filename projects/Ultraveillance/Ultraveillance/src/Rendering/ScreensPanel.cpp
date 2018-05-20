#include "ScreensPanel.h"
#include "StreamAnalysisAndDisplay.h"
#include <algorithm>


//------------------------------------------------------------------------------
ScreensPanel::ScreensPanel(int inImgsCaptureWidth, int inImgsCaptureHeight)
    : mImgsCaptureWidth(inImgsCaptureWidth)
    , mImgsCaptureHeight(inImgsCaptureHeight)
    , mCams(inImgsCaptureWidth, inImgsCaptureHeight)
    , mDrawingsPositions()
    , mDrawingsWidth(inImgsCaptureWidth)
    , mDrawingsHeight(inImgsCaptureHeight)
    , mRandomDisplayIndexes()
    , mTimeToShuffleDisplays(ofGetElapsedTimeMillis() + 1000)
    , mTimeToCheckIfResyncNeeded(ofGetElapsedTimeMillis() + 10000)
{
    float widthSpacing = ofGetWindowWidth() / 4;
    mColumnsPosX[0] = 1 * widthSpacing;
    mColumnsPosX[1] = 2 * widthSpacing;
    mColumnsPosX[2] = 3 * widthSpacing;

    float heightSpacing = ofGetWindowWidth() / 4;
    mLinesPosY[0] = 1 * heightSpacing;
    mLinesPosY[1] = 2 * heightSpacing;
    mLinesPosY[2] = 3 * heightSpacing;

    updateDrawingsPosition();

    resyncCamDevices();

    randomizeDisplays();
}

ScreensPanel::~ScreensPanel()
{
    for (StreamsIt it = mStreams.begin();
         it != mStreams.end();
         ++it)
    {
        delete (*it);
    }
}

//------------------------------------------------------------------------------
void ScreensPanel::update()
{
    float ellapsedTime = ofGetElapsedTimeMillis();
    checkResyncDevicesNeeded(ellapsedTime);
    checkTimeToShuffleDisplays(ellapsedTime);


    mCams.update();

    for (StreamsIt it = mStreams.begin();
         it != mStreams.end();
         ++it)
    {
        (*it)->updateCVImg();
        (*it)->processAnalysis();
    }

}

void ScreensPanel::draw()
{
    drawImgs();
    drawAnalysisResults();
    drawExtractedROIs();
}

//------------------------------------------------------------------------------
void ScreensPanel::drawImgs()
{
    ofSetColor(255);

    for(int i = 0; i < NUM_SCREENS; ++i)
    {
        int displayIndex = mRandomDisplayIndexes[i];
        mStreams[displayIndex]->drawImg(mDrawingsPositions[i].x, mDrawingsPositions[i].y,
                                        mDrawingsWidth, mDrawingsHeight);
    }
}

void ScreensPanel::drawAnalysisResults()
{
    ofSetColor(255);

    for (int i = 0; i < NUM_SCREENS; ++i)
    {
        int displayIndex = mRandomDisplayIndexes[i];
        mStreams[displayIndex]->drawAnalysisResultsROIs(mDrawingsPositions[i].x, mDrawingsPositions[i].y,
                                    mDrawingsWidth, mDrawingsHeight);
    }
}

void ScreensPanel::drawExtractedROIs()
{
    ofSetColor(255);

    for (int i = 0; i < NUM_SCREENS; ++i)
    {
        float ROIDrawingWidth = mDrawingsWidth / 8;
        float ROIDrawingHeight = ROIDrawingWidth * 5 / 4;

        int displayIndex = mRandomDisplayIndexes[i];
        mStreams[displayIndex]->drawExtractedROIs(mDrawingsPositions[i].x + mDrawingsWidth - ROIDrawingWidth,
                       mDrawingsPositions[i].y,
                       ROIDrawingWidth, ROIDrawingHeight);
    }
}

void ScreensPanel::drawCameras()
{
    ofSetColor(255);
    unsigned int i = 0;
    for (MultiCamera::VideoGrabbersIt it = (mCams.mVideoGrabbers).begin();
         it != (mCams.mVideoGrabbers).end();
         ++i, ++it)
    {
        if (i >= NUM_SCREENS) break;
        (*it)->draw(mDrawingsPositions[i].x, mDrawingsPositions[i].y,
                    mDrawingsWidth, mDrawingsHeight);
    }
}

//------------------------------------------------------------------------------
void ScreensPanel::needUpdateCamsDevices()
{
    mTimeToCheckIfResyncNeeded = ofGetElapsedTimeMillis() - 10;
}

//------------------------------------------------------------------------------
void ScreensPanel::setDrawingsWidth(float inDimension)
{
    mDrawingsWidth = inDimension;
    updateDrawingsPosition();
}

float ScreensPanel::getDrawingsWidth()
{
    return mDrawingsWidth;
}

void ScreensPanel::setDrawingsHeight(float inDimension)
{
    mDrawingsHeight = inDimension;
    updateDrawingsPosition();
}

float ScreensPanel::getDrawingsHeight()
{
    return mDrawingsHeight;
}


void ScreensPanel::setDrawingsColumnsPos(float* inDimension)
{
    mColumnsPosX[0] = inDimension[0];
    mColumnsPosX[1] = inDimension[1];
    mColumnsPosX[2] = inDimension[2];
    updateDrawingsPosition();
}

void ScreensPanel::setDrawingsLinesPos(float* inDimension)
{
    mLinesPosY[0] = inDimension[0];
    mLinesPosY[1] = inDimension[1];
    mLinesPosY[2] = inDimension[2];
    updateDrawingsPosition();
}

float* ScreensPanel::getDrawingsColumnsPos()
{
    return mColumnsPosX;
}

float* ScreensPanel::getDrawingsLinesPos()
{
    return mLinesPosY;
}

//------------------------------------------------------------------------------
void ScreensPanel::updateDrawingsPosition()
{
    int numColumn = 3;
    int columnIndex = 0;
    int lineIndex = 0;

    for (int i = 0; i < NUM_SCREENS; ++columnIndex, ++i)
    {
        if (columnIndex >= numColumn)
        {
            columnIndex = 0;
            ++lineIndex;
        }
        mDrawingsPositions[i].x = mColumnsPosX[columnIndex] - mDrawingsWidth/2;
        mDrawingsPositions[i].y = mLinesPosY[lineIndex] - mDrawingsHeight / 2;
    }
}

//------------------------------------------------------------------------------
void ScreensPanel::randomizeDisplays()
{
    int numCams = (mCams.mVideoGrabbers).size();

    for(int i = 0; i < NUM_SCREENS; ++i)
    {
        mRandomDisplayIndexes[i] = i % numCams;
    }
    std::random_shuffle(&mRandomDisplayIndexes[0], &mRandomDisplayIndexes[NUM_SCREENS]);

}

void ScreensPanel::resyncCamDevices()
{
    int numCams = (mCams.mVideoGrabbers).size();
    
    // check number of Analysis and cam.
    if(mStreams.size() != numCams)
    {
        while(mStreams.size() < numCams)
        {
            mStreams.push_back(new StreamAnalysisAndDisplay(mImgsCaptureWidth, mImgsCaptureHeight));
        }
        while(mStreams.size() > numCams)
        {
            delete mStreams.back();
            mStreams.pop_back();
        }
    }

    // bind Cam and analysis.
    for (int i = 0; i < numCams; ++i)
    {
        mStreams[i]->setCam((mCams.mVideoGrabbers)[i]);
    }
}

//------------------------------------------------------------------------------
void ScreensPanel::checkResyncDevicesNeeded(float inEllapsedTime)
{
    if(mTimeToCheckIfResyncNeeded < inEllapsedTime)
    {
        mTimeToCheckIfResyncNeeded += 3 * 60 * 1000;
        if(mPreviousNumCamDevices != mCams.getNumCameras())
        {
            mPreviousNumCamDevices = mCams.getNumCameras();
            mCams.initCameras();
            resyncCamDevices();
        }
    } 
}

void ScreensPanel::checkTimeToShuffleDisplays(float inEllapsedTime)
{
    if(mTimeToShuffleDisplays < inEllapsedTime)
    {
        mTimeToShuffleDisplays += ofRandom(60, 120) * 1000;
        resyncCamDevices();
    }

}


