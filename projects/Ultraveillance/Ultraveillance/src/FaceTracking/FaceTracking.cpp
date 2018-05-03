#include "FaceTracking.h"
#include "FaceTrackingImg.h"
#include <algorithm>


//------------------------------------------------------------------------------
FaceTracking::FaceTracking(int inImgsCaptureWidth, int inImgsCaptureHeight)
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

    mColumnsPosX[0] = ofGetWindowWidth() * 1 / 4;
    mColumnsPosX[1] = ofGetWindowWidth() * 2 / 4;
    mColumnsPosX[2] = ofGetWindowWidth() * 3 / 4;

    mLinesPosY[0] = ofGetWindowHeight() * 1 / 4;
    mLinesPosY[1] = ofGetWindowHeight() * 2 / 4;
    mLinesPosY[2] = ofGetWindowHeight() * 3 / 4;

    updateDrawingsPosition();
    for (int i = 0; i < NUM_IMGS; ++i)
    {
        mFaceTrackingImgs.push_back(new FaceTrackingImg(mImgsCaptureWidth, mImgsCaptureHeight));
    }
    bindCamsToImgs();
}

FaceTracking::~FaceTracking()
{
    for (FaceTrackingImgsIt it = mFaceTrackingImgs.begin();
         it != mFaceTrackingImgs.end();
         ++it)
    {
        delete (*it);
    }
}

//------------------------------------------------------------------------------
void FaceTracking::update()
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
        mFaceTrackingImgs[i]->updateImg();
    }

    if (mNumSimultaneousFaceTracking > NUM_IMGS)
        mNumSimultaneousFaceTracking = NUM_IMGS;

    for (int i = 0; i < mNumSimultaneousFaceTracking; ++mCurrentImgFaceTrackingIndex, ++i)
    {
        mCurrentImgFaceTrackingIndex = mCurrentImgFaceTrackingIndex % NUM_IMGS;
        mFaceTrackingImgs[mCurrentImgFaceTrackingIndex]->processFaceTracking();
    }
}

//------------------------------------------------------------------------------
void FaceTracking::drawImgs()
{
    ofSetColor(255);
    unsigned int i = 0;
    for (FaceTrackingImgsIt it = mFaceTrackingImgs.begin();
         it != mFaceTrackingImgs.end();
         ++i, ++it)
    {
        (*it)->drawImg(mDrawingsPositions[i].x, mDrawingsPositions[i].y,
                       mDrawingsWidth, mDrawingsHeight);
    }
}

void FaceTracking::drawFacesRecognition()
{
    ofSetColor(255);
    unsigned int i = 0;
    for (FaceTrackingImgsIt it = mFaceTrackingImgs.begin();
         it != mFaceTrackingImgs.end();
         ++i, ++it)
    {
        (*it)->drawFacesRecognition(mDrawingsPositions[i].x, mDrawingsPositions[i].y,
                                    mDrawingsWidth, mDrawingsHeight);
    }
}

void FaceTracking::drawROIs()
{
    ofSetColor(255);
    unsigned int i = 0;
    for (FaceTrackingImgsIt it = mFaceTrackingImgs.begin();
         it != mFaceTrackingImgs.end();
         ++i, ++it)
    {
        float ROIDrawingWidth = mDrawingsWidth / 8;
        float ROIDrawingHeight = ROIDrawingWidth * 5 / 4;
        (*it)->drawROI(mDrawingsPositions[i].x + mDrawingsWidth - ROIDrawingWidth,
                       mDrawingsPositions[i].y,
                       ROIDrawingWidth, ROIDrawingHeight);
    }
}

void FaceTracking::drawCameras()
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
void FaceTracking::needUpdateCamsDevices()
{
    mUpdateCamsDevices = true;
}


void FaceTracking::setNumSimultaneousFaceTracking(int inNum)
{
    mNumSimultaneousFaceTracking = inNum;
}

int FaceTracking::getNumSimultaneousFaceTracking()
{
    return mNumSimultaneousFaceTracking;

}


void FaceTracking::setDrawingsWidth(float inDimension)
{
    mDrawingsWidth = inDimension;
    updateDrawingsPosition();
}

float FaceTracking::getDrawingsWidth()
{
    return mDrawingsWidth;
}

void FaceTracking::setDrawingsHeight(float inDimension)
{
    mDrawingsHeight = inDimension;
    updateDrawingsPosition();
}

float FaceTracking::getDrawingsHeight()
{
    return mDrawingsHeight;
}


void FaceTracking::setDrawingsColumnsPos(float* inDimension)
{
    mColumnsPosX[0] = inDimension[0];
    mColumnsPosX[1] = inDimension[1];
    mColumnsPosX[2] = inDimension[2];
    updateDrawingsPosition();
}

void FaceTracking::setDrawingsLinesPos(float* inDimension)
{
    mLinesPosY[0] = inDimension[0];
    mLinesPosY[1] = inDimension[1];
    mLinesPosY[2] = inDimension[2];
    updateDrawingsPosition();
}

float* FaceTracking::getDrawingsColumnsPos()
{
    return mColumnsPosX;
}

float* FaceTracking::getDrawingsLinesPos()
{
    return mLinesPosY;
}

//------------------------------------------------------------------------------
void FaceTracking::updateDrawingsPosition()
{
    int numColumn = 3;
    int columnIndex = 0;
    int lineIndex = 0;

    for (int i = 0; i < NUM_IMGS; ++columnIndex, ++i)
    {
        if (columnIndex == 1 && lineIndex == 1)
        {
            ++columnIndex;
        }

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
void FaceTracking::bindCamsToImgs()
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
        mFaceTrackingImgs[i]->setCam((mCams.mVideoGrabbers)[camIndex]);

    }
}

