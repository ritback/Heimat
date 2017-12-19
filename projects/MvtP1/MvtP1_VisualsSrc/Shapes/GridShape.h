#pragma once

#include "ofMain.h"

#include "HE_MassParticle.h"

class GridShape: public HEMassParticle
{
public:
    GridShape(const ofPoint& inPos = ofPoint(0, 0), int inImageIndex = 0);
    virtual ~GridShape();
    
public:
    void update();
    
public:
    int mShapeImgIndex;
    ofColor mColor;
    float mWidth, mHeight;
    ofPoint mCentralPos;
};
