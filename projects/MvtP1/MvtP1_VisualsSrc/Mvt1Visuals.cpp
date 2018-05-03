#include "Mvt1Visuals.h"


Mvt1Visuals::Mvt1Visuals()
: mFlowField()
, mBackgroundShapes()
, mSpiritsGroup(&mFlowField)
, mSnowFlakesBack(&mFlowField)
, mSnowFlakesFront(&mFlowField)
, mGridShapesGroup(&mFlowField)
{
    // Let's strat the visuals
}

Mvt1Visuals::~Mvt1Visuals()
{
    
}

// -----------------------------------------------------------------------------
void Mvt1Visuals::update()
{
    mSnowFlakesBack.update();
    mSnowFlakesFront.update();
    
    mGridShapesGroup.update();
    
    mSpiritsGroup.update();
}


void Mvt1Visuals::draw()
{
    mFlowField.drawFboFlowField();
    
    ofBackground(18, 7, 1);
    
    //mFlowField.drawNoise();
    //mFlowField.drawField();
    
    // ---------------------------------------
    mBackgroundShapes.drawShader();
    
    mSnowFlakesBack.draw();
    mGridShapesGroup.draw();
    
    mSpiritsGroup.draw();
    mSnowFlakesFront.draw();
    
}

// -----------------------------------------------------------------------------
void Mvt1Visuals::updateParameters(const BlobsParameters& inParameters)
{
    mBackgroundShapes.updateParameters(inParameters);
}

void Mvt1Visuals::updateParameters(const SandParameters& inParameters)
{
    mBackgroundShapes.updateParameters(inParameters);
}

void Mvt1Visuals::updateParameters(const BlinkingColorParameters& inParameters)
{
    mBackgroundShapes.updateParameters(inParameters);
}

void Mvt1Visuals::updateParameters(const FlakesParameters& inParameters, bool isBack)
{
    if (isBack)
        mSnowFlakesBack.updateParameters(inParameters);
    else
        mSnowFlakesFront.updateParameters(inParameters);
}

void Mvt1Visuals::updateParameters(const SpiritsParameters& inParameters)
{
    mSpiritsGroup.updateParameters(inParameters);
}


// -----------------------------------------------------------------------------
void Mvt1Visuals::resize(int w, int h)
{
    mFlowField.resize(w, h);
}
