#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include <vector>

struct AnalysisROI: public ofRectangle
{
public:
    AnalysisROI() : ofRectangle() { invalidate(); };
    AnalysisROI(float px, float py, float w, float h) : ofRectangle(px, py, w, h) {};
    AnalysisROI(const ofPoint& p, float w, float h) : ofRectangle(p, w, h) {};
    AnalysisROI(const ofPoint& p0, const ofPoint& p1) : ofRectangle(p0, p1) {};
    AnalysisROI(ofRectangle& inRect) : ofRectangle(inRect) {};
    virtual ~AnalysisROI() {};

public:
    void invalidate() { set(-1, -1, 0, 0); };
    bool isValid()
    {
        if(x < 0 || y < 0 || width <= 0 || height <= 0)
        {
            return false;
        }
        return true;
    };
};
 
//------------------------------------------------------------------------------
class ImgAnalysisInterface
{
public:
    ImgAnalysisInterface();
    virtual ~ImgAnalysisInterface();

public:
    virtual void process(const ofxCvGrayscaleImage& inImg) = 0;

    // TODO: setup a region of interest array
    // coordinates based on the image provided in the process function.

public:
    const ofRectangle* getROI(const int& inIndex = 0);
    int getROISize();

protected:
    typedef std::vector<AnalysisROI*> ROIs;
    typedef ROIs::iterator ROIsIt;

    // Helpers for inherited classes
protected:
    void pushROI(AnalysisROI& inROI);
    void invalidateRestOfROIFrom(ROIsIt& inIt);
    void invalidateROIs();
    // find the first invalid ROI of the stack.
    // if none exist, create one and returns it.
    void findFirstInvalidROI(ROIsIt& outIt);
    AnalysisROI* findFirstInvalidROI();

protected:
    ROIs mROIs;
};



