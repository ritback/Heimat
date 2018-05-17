#pragma once

#include "ofMain.h"
#include "ImgAnalysisInterface.h"


class HaarFaceTracking: public ImgAnalysisInterface
{
public:
    HaarFaceTracking();
    virtual ~HaarFaceTracking();

public:
    virtual void process(const ofxCvGrayscaleImage& inImg);

public:
    ofxCvHaarFinder mCVHaarFinder;

};



