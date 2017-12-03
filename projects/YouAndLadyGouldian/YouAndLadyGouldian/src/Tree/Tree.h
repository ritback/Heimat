#pragma once

#include "ofMain.h"

#include "HEHelpers_Shader.h"

class HEKinect;

class Tree
{
public:
    Tree();
    ~Tree();

public:
    void update();
    void render();

public:
    void activate(const ofPoint& inPos);

private:
    void updateAlpha();

public:
    bool mIsVisible;

private:
    ofPoint mPos;
    ofPoint mSize;
    HEShaderHelper mTreeShader;
    ofImage mPixelCanvas;

private:
    float mAlpha;
    float mActivationTime;
    float mActivationDuration;

};
 
