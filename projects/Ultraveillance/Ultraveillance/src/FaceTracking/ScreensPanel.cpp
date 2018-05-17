#include "ScreensPanel.h"
#include "ScreenAnalysisRendering.h"
#include <algorithm>


//------------------------------------------------------------------------------
ScreensPanel::ScreensPanel(int inImgsCaptureWidth, int inImgsCaptureHeight)
    : mImgsCaptureWidth(inImgsCaptureWidth)
    , mImgsCaptureHeight(inImgsCaptureHeight)
    , mCams(inImgsCaptureWidth, inImgsCaptureHeight)
    , mDrawingsPositions()
    , mDrawingsWidth(inImgsCaptureWidth)
    , mDrawingsHeight(inImgsCaptureHeight)
    , mCurrentImgFaceTrackingIndex(0)
    , mNumSimultaneousFaceTracking(1)
    , mUpdateCamsDevices(false)
    , mTimeToShuffleCams(ofGetElapsedTimeMillis() + 10000)
    , mTimeToCheckCams(ofGetElapsedTimeMillis() + 10000)
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
    for (int i = 0; i < NUM_IMGS; ++i)
    {
        mScreens.push_back(new ScreenAnalysisRendering(mImgsCaptureWidth, mImgsCaptureHeight));
    }
    bindCamsToImgs();
}

ScreensPanel::~ScreensPanel()
{
    for (ScreensIt it = mScreens.begin();
         it != mScreens.end();
         ++it)
    {
        delete (*it);
    }
}

//------------------------------------------------------------------------------
void ScreensPanel::update()
{
    float ellapsedTime = ofGetElapsedTimeMillis();
    if (mTimeToCheckCams < ellapsedTime)
    {
        mTimeToCheckCams += 30000;
        if (mNumCamDevice != mCams.getNumCameras())
        {
            mUpdateCamsDevices = true;
        }
    }

    if (mUpdateCamsDevices)
    {
        mNumCamDevice = mCams.getNumCameras();
        mCams.initCameras();
        bindCamsToImgs();
        mUpdateCamsDevices = false;
    }

    if (mTimeToShuffleCams < ellapsedTime)
    {
        mTimeToShuffleCams += ofRandom(60, 120) * 1000;
        bindCamsToImgs();
    }

    mCams.update();

    for (int i = 0; i < NUM_IMGS; ++i)
    {
        mScreens[i]->updateImg();
    }

    if (mNumSimultaneousFaceTracking > NUM_IMGS)
        mNumSimultaneousFaceTracking = NUM_IMGS;

    for (int i = 0; i < mNumSimultaneousFaceTracking; ++mCurrentImgFaceTrackingIndex, ++i)
    {
        mCurrentImgFaceTrackingIndex = mCurrentImgFaceTrackingIndex % NUM_IMGS;
        mScreens[mCurrentImgFaceTrackingIndex]->processFaceTracking();
    }
}

void ScreensPanel::draw()
{
    drawImgs();
    drawFacesRecognition();
    drawROIs();
    drawCameras();
}

//------------------------------------------------------------------------------
void ScreensPanel::drawImgs()
{
    ofSetColor(255);
    unsigned int i = 0;
    for (ScreensIt it = mScreens.begin();
         it != mScreens.end();
         ++i, ++it)
    {
        (*it)->drawImg(mDrawingsPositions[i].x, mDrawingsPositions[i].y,
                       mDrawingsWidth, mDrawingsHeight);
    }
}

void ScreensPanel::drawFacesRecognition()
{
    ofSetColor(255);
    unsigned int i = 0;
    for (ScreensIt it = mScreens.begin();
         it != mScreens.end();
         ++i, ++it)
    {
        (*it)->drawFacesRecognition(mDrawingsPositions[i].x, mDrawingsPositions[i].y,
                                    mDrawingsWidth, mDrawingsHeight);
    }
}

void ScreensPanel::drawROIs()
{
    ofSetColor(255);
    unsigned int i = 0;
    for (ScreensIt it = mScreens.begin();
         it != mScreens.end();
         ++i, ++it)
    {
        float ROIDrawingWidth = mDrawingsWidth / 8;
        float ROIDrawingHeight = ROIDrawingWidth * 5 / 4;
        (*it)->drawHaarFaceROI(mDrawingsPositions[i].x + mDrawingsWidth - ROIDrawingWidth,
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
        if (i >= NUM_IMGS) break;
        (*it)->draw(mDrawingsPositions[i].x, mDrawingsPositions[i].y,
                    mDrawingsWidth, mDrawingsHeight);
    }
}


//------------------------------------------------------------------------------
void ScreensPanel::needUpdateCamsDevices()
{
    mUpdateCamsDevices = true;
}


void ScreensPanel::setNumSimultaneousFaceTracking(int inNum)
{
    mNumSimultaneousFaceTracking = inNum;
}

int ScreensPanel::getNumSimultaneousFaceTracking()
{
    return mNumSimultaneousFaceTracking;

}


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

    for (int i = 0; i < NUM_IMGS; ++columnIndex, ++i)
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
void ScreensPanel::bindCamsToImgs()
{
    MultiCamera::VideoGrabbersIt camIt = (mCams.mVideoGrabbers).begin();

    int randomIndexes[NUM_IMGS];
    int camsSize = (mCams.mVideoGrabbers).size();
    for (int i = 0; i < NUM_IMGS; ++i)
    {
        randomIndexes[i] = i % camsSize;
    }
    std::random_shuffle(&randomIndexes[0], &randomIndexes[NUM_IMGS]);

    for (int i = 0; i < NUM_IMGS; ++i)
    {
        MultiCamera::VideoGrabbersIt camIt = (mCams.mVideoGrabbers).begin();
        int camIndex = randomIndexes[i];
        mScreens[i]->setCam((mCams.mVideoGrabbers)[camIndex]);

    }
}

