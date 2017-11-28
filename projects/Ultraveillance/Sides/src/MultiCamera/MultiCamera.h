#pragma once

#include "ofMain.h"
#include <vector>

class MultiCamera
{
public:
    MultiCamera(int inCamsWidth, int inCamsHeight);
    virtual ~MultiCamera();

public:
    virtual void update();
    
public:
    void initCameras();
    int getNumCameras();
    
public:
    ofVideoGrabber mInitVideoGrabber;
    typedef std::vector<ofVideoGrabber*> VideoGrabbers;
    typedef VideoGrabbers::iterator VideoGrabbersIt;
    VideoGrabbers mVideoGrabbers;

    typedef std::vector<ofVideoDevice> VideoDevices;
    typedef VideoDevices::iterator VideoDevicesIt;
    VideoDevices mDevices;
    
private:
    int mCamsWidth;
    int mCamsHeight;
    
};
