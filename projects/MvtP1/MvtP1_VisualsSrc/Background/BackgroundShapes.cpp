#include "BackgroundShapes.h"


BackgroundShapes::BackgroundShapes()
: mBlobsShader("Blobs")
, mSandShader("Sand")
, mBlinkingColorShader("BlinkingColor")
, mPixelCanvas()
{
    mPixelCanvas.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
    
    // set DefaultParam
    mBlobsParameters.setDefault();
    mSandParameters.setDefault();
    mBlinkingColorParameters.setDefault();
}

BackgroundShapes::~BackgroundShapes()
{
    
}

// -----------------------------------------------------------------------------
void BackgroundShapes::updateParameters(const BlobsParameters& inParameters)
{
    mBlobsParameters.updateParameters(inParameters);
}

void BackgroundShapes::updateParameters(const SandParameters& inParameters)
{
    mSandParameters.updateParameters(inParameters);
}

void BackgroundShapes::updateParameters(const BlinkingColorParameters& inParameters)
{
    mBlinkingColorParameters.updateParameters(inParameters);
}

// -----------------------------------------------------------------------------
void BackgroundShapes::drawShader()
{
    if (mBlinkingColorParameters.mDisplay)
        drawBlinkingColorShader();
    
    drawSandShader();
    drawBlobsShader();
    
}

// -----------------------------------------------------------------------------

void BackgroundShapes::drawBlobsShader()
{
    
    mBlobsShader.begin();
    
    ofPoint sResolution = ofGetWindowSize();
    float pRes[3] = {sResolution.x, sResolution.y, 0};
    mBlobsShader.setUniform3fv("uResolution", pRes, 1);
    
    mBlobsShader.setUniform1f("uGlobalTime", ofGetElapsedTimef());
    
    // Blobs parameters
    mBlobsShader.setUniform1f("uBpm", mBlobsParameters.mBpm);
    mBlobsShader.setUniform1f("uBpmAmplitude", mBlobsParameters.mBpmAmplitude);
    mBlobsShader.setUniform1f("uDistortionAmount", mBlobsParameters.mDistortionAmount);
    mBlobsShader.setUniform1f("uDistortionSpeed", mBlobsParameters.mDistortionSpeed);
    mBlobsShader.setUniform1f("uMvtSpeed", mBlobsParameters.mMvtSpeed);
    mBlobsShader.setUniform1f("uMvtRange", mBlobsParameters.mMvtRange);
    
    mPixelCanvas.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    mBlobsShader.end();
}

void BackgroundShapes::drawSandShader()
{
    mSandShader.begin();
    
    ofPoint sResolution = ofGetWindowSize();
    float pRes[3] = {sResolution.x, sResolution.y, 0};
    mSandShader.setUniform3fv("uResolution", pRes, 1);
    
    mSandShader.setUniform1f("uGlobalTime", ofGetElapsedTimef());
    
    mSandShader.setUniform1f("uSandSpeed", mSandParameters.mSandSpeed);
    mSandShader.setUniform1f("uSandAmount", mSandParameters.mSandAmount);
    mSandShader.setUniform3fv("uSandColor", mSandParameters.mSandColor, 1);
    
    
    mPixelCanvas.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    mSandShader.end();
}


void BackgroundShapes::drawBlinkingColorShader()
{
    mBlinkingColorShader.begin();
    
    ofPoint sResolution = ofGetWindowSize();
    float pRes[3] = {sResolution.x, sResolution.y, 0};
    mBlinkingColorShader.setUniform3fv("uResolution", pRes, 1);
    
    mBlinkingColorShader.setUniform1f("uGlobalTime", ofGetElapsedTimef());
    
    mBlinkingColorShader.setUniform1f("uColorChangeSpeed", mBlinkingColorParameters.mColorChangeSpeed);
    mBlinkingColorShader.setUniform1f("uBrightness", mBlinkingColorParameters.mBrightness);
    mBlinkingColorShader.setUniform1f("uColorAmount", mBlinkingColorParameters.mColorAmount);
    mBlinkingColorShader.setUniform1f("uAlpha", mBlinkingColorParameters.mAlpha);
    
    
    mPixelCanvas.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    mBlinkingColorShader.end();
}
