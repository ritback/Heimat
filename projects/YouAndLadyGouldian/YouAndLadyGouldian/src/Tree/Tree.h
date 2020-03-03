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
    static void incrementTreeGrowth();

private:
    void growthActivation();
    void restart();

private:
    void updateAlpha();

private:
    static bool mShouldActivateTreeGrowth;
    static int mActivationCounter;

private:
    ofPoint mRandomPos;
    HEShaderHelper mTreeShader;
    double mGlobalTime;

private:
    float mAlpha;
    float mActivationTime;
    float mActivationDuration;
    bool mIsVisible;

};
 
