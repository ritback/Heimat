#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class HaarFaceTracking
{
public:
    HaarFaceTracking();
    virtual ~HaarFaceTracking();

public:
    virtual void process(const ofxCvGrayscaleImage& inImg);

public:
    static ofxCvHaarFinder mCVHaarFinder;
};



