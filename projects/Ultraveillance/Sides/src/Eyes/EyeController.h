#pragma once

#include "ofMain.h"
#include "EyeWithAnimations.h"

class EyeController
{
public:
    EyeController(float inX, float inY, float inWidth, float inHeight);
    ~EyeController();
    
public:
    void render();
    void update();
    
public:
    void stareAt(float inToX, float inToY);
    
public:
    void setPos(const ofPoint& inPos);
    void setSize(const ofPoint& inSize);
    const ofPoint& getPos();
    const ofPoint& getSize();
    
private:
    EyeWithAnimations mEye;
    
private:
    float mNextBlinkTime;
    
private:
    float mNextLookElsewhereTime;
    
};

