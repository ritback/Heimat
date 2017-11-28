#include "Kinect.h"

Kinect::Kinect(BirdsFlock* inFlock)
    : mKinect(true, true)
    , mSilhouette(&mKinect)
    , mScarecrowsTracker(&mKinect, inFlock)
{

}

Kinect::~Kinect()
{

}

//------------------------------------------------------------------------------
void Kinect::updateSilhoutte()
{
    if(mKinect.isAvailable())
    {
        mSilhouette.update();
    }
}

void Kinect::renderSilhouette()
{
    if(!mKinect.isAvailable())
    {
        ofBackground(255, 0, 0);
        ofSetColor(0);
        for(int i = 0; i < ofGetWindowWidth() / 100; ++i)
            for(int j = 0; j < ofGetWindowHeight() / 50; ++j)
                ofDrawBitmapString("NO KINECT!", i * 100, j * 50);
        return;
    }

    mSilhouette.render();
    
}

//------------------------------------------------------------------------------
void Kinect::updateScarecrows()
{
    if(mKinect.isAvailable())
    {
        mScarecrowsTracker.update();
    }
}

void Kinect::renderScarecrows()
{
    if(!mKinect.isAvailable())
    {
        ofBackground(255, 0, 0);
        ofSetColor(0);
        for(int i = 0; i < ofGetWindowWidth() / 100; ++i)
            for(int j = 0; j < ofGetWindowHeight() / 50; ++j)
                ofDrawBitmapString("NO KINECT!", i * 100, j * 50);
        return;
    }

    mScarecrowsTracker.render();

}
