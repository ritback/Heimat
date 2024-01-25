#pragma once

#include "ofMain.h"

#include "HE_FlowField.h"
#include "SpiritsGroup.h"
#include "SnowFlakes.h"
#include "BackgroundShapes.h"
#include "GridShapesGroup.h"

class Mvt1Visuals
{
public:
    Mvt1Visuals();
    virtual ~Mvt1Visuals();
    
public:
    void update();
    void draw();
    
public: // updateParameters
    void updateParameters(const BlobsParameters& inParameters);
    void updateParameters(const SandParameters& inParameters);
    void updateParameters(const BlinkingColorParameters& inParameters);
    void updateParameters(const FlakesParameters& inParameters, bool isBack = false);
    void updateParameters(const SpiritsParameters& inParameters);
    
public:
    void resize(int w, int h);
    
private:
    BackgroundShapes mBackgroundShapes;
    
private:
    HEFlowField mFlowField;
    
private:
    SpiritsGroup mSpiritsGroup;
    
private:
    SnowFlakes mSnowFlakesBack;
    SnowFlakes mSnowFlakesFront;
    
private:
    GridShapesGroup mGridShapesGroup;
    
};
