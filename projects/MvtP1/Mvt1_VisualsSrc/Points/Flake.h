#pragma once

#include "ofMain.h"

#include "HE_MassParticle.h"

class Flake: public HEMassParticle
{
public:
    Flake(const ofPoint& inPos = ofPoint(0, 0), int inNumImageIndex = 0);
    virtual ~Flake();
    
public:
    void update();
    
public:
    int mFlakeImgIndex;
    ofColor mColor;
    float mWidth, mHeight;
};
