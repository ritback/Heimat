#pragma once

#include "ofMain.h"

#include "HEHelpers_Shader.h"

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
    ofPoint mRandomPos;
    ofPoint mSize;
    HEShaderHelper mTreeShader;
    double mGlobalTime;

private:
    float mAlpha;
    float mActivationTime;
    float mActivationDuration;

};
 
