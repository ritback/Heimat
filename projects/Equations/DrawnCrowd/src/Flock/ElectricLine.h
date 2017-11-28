#pragma once

#include "ofMain.h"

#include <vector>

class ElectricLine
{
public:
    ElectricLine();
    ElectricLine(const ofPoint& inStart, const ofPoint& inEnd);
    virtual ~ElectricLine();
    
public:
    void update(const ofPoint* inNewStart = 0, const ofPoint* inNewEnd = 0);
    void render();
    
public:
    void resetLine(const ofPoint* inNewStart, const ofPoint* inNewEnd);
    void setInvisible();
    
private:
    void init();
    
private:
    typedef std::vector<ofPolyline*> LightningLines;
    typedef LightningLines::iterator LightningLinesIt;
    
private:
    LightningLines mLightningLines;
    
private:
    ofPoint mStart;
    ofPoint mEnd;
    
    int mNumLightning;
    
private:
    bool mIsVisible;
    
};

