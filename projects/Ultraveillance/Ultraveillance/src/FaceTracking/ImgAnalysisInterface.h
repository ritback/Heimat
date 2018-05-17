#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include <vector>

struct AnalysisROI
{
public:
    AnalysisROI();
    ~AnalysisROI();

public:
    void invalidate();

public:
    ofRectangle mROI;
};

//------------------------------------------------------------------------------
class ImgAnalysisInterface
{
public:
    ImgAnalysisInterface();
    virtual ~ImgAnalysisInterface();

public:
    virtual void process(const ofxCvGrayscaleImage& inImg) = 0;

    // TODO: setup a region of interest coordinates based on 0 to 1 scale.
    // every images rendering would need to be controlled by that 0 to 1 scale
    // (that should have been done since the begining...)
    // this would allow to completely separate analysis and rendering...

public:
    typedef std::vector<AnalysisROI> ROIs;
    typedef ROIs::iterator ROIsIt;
    ROIs mROIs;
};



