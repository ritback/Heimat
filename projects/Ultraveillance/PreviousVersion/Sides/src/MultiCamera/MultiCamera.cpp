#include "MultiCamera.h"

//------------------------------------------------------------------------------
MultiCamera::MultiCamera(int inCamsWidth, int inCamsHeight)
    : mCamsWidth(inCamsWidth)
    , mCamsHeight(inCamsHeight)
{
    initCameras();

    ofSetVerticalSync(true);
}

MultiCamera::~MultiCamera()
{
    for (VideoGrabbersIt it = mVideoGrabbers.begin();
         it != mVideoGrabbers.end();
         ++it)
    {
        delete (*it);
    }
}

//------------------------------------------------------------------------------
void MultiCamera::update()
{
    ofBackground(100, 100, 100);
    for (VideoGrabbersIt it = mVideoGrabbers.begin();
         it != mVideoGrabbers.end();
         ++it)
    {
        (*it)->update();
    }
}

//------------------------------------------------------------------------------
void MultiCamera::initCameras()
{
    for (VideoGrabbersIt it = mVideoGrabbers.begin();
         it != mVideoGrabbers.end();
         ++it)
    {
        (*it)->close();
        delete (*it);
    }
    mVideoGrabbers.clear();
    
    mDevices = mInitVideoGrabber.listDevices();

    for (int i = 0; i < mDevices.size(); i++) // camera 4 is reserved
    {
        if (mDevices[i].bAvailable && i != 3)
        {
            ofLogNotice() << mDevices[i].id << ": " << mDevices[i].deviceName;

            ofVideoGrabber* newGrabber = new ofVideoGrabber();
            newGrabber->setVerbose(false);
            int indexCamera = mDevices[i].id;
            newGrabber->setDeviceID(mDevices[i].id);
            newGrabber->setDesiredFrameRate(30);
            newGrabber->initGrabber(mCamsWidth, mCamsHeight);

            mVideoGrabbers.push_back(newGrabber);
        }
        else
        {
            ofLogNotice() << mDevices[i].id << ": " << mDevices[i].deviceName << " - unavailable ";
        }
    }

}


//------------------------------------------------------------------------------
int MultiCamera::getNumCameras()
{
    VideoDevices devices = mInitVideoGrabber.listDevices();
    return (int)devices.size();
}

