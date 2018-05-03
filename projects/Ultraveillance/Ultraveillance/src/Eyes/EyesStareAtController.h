#pragma once


#include "ofMain.h"

class EyesStareAtController
{
public:
    EyesStareAtController(EyesContainer* inEyes);
    ~EyesStareAtController();
    
public:
    void update();
    
public:
    void updateClosestHeadPosition(float inPosX, float inPosY);
    
public:
    void updateStreamWindowSize(float inWidth, float inHeigth);
    
public:
    ofPoint mClosestHeadPosition;
    ofPoint mClosestHeadPositionTarget;
    ofPoint mStreamWindowSize;
    
private:
    EyesContainer* mEyes;
};


