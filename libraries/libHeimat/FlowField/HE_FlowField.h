#pragma once

#include "ofMain.h"

#include "../Helpers/HEHelpers_Shader.h"

class HEFlowField
{
public:
    HEFlowField();
    virtual ~HEFlowField();
    
public:
    void drawFboFlowField();
    
public:
    void drawNoise();
    void drawField();
    
public:
    float getFlowFieldDirection(const ofPoint& inPos);
    ofPoint getForceFieldForce(const ofPoint& inPos, float inForceMag);
    
public:
    void resize(int w, int h);
    
private:
    void resizeFboAndCanvas(int w, int h);
    
public:
    bool mFboDrawn;
    
private:
    ofFbo mFbo;
    ofPixels mFboPixels;
    HEShaderHelper mShader;
    ofImage mPixelCanvas;
    
    
};


// -----------------------------------------------------------------------------
template<class Type>
static Type scalingMap(Type valueIn, Type baseMin, Type baseMax, Type limitMin, Type limitMax)
{
    return ((limitMax - limitMin) * (valueIn - baseMin) / (baseMax - baseMin)) + limitMin;
}


