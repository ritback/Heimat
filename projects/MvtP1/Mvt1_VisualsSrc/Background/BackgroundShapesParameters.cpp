#include "BackgroundShapesParameters.h"

void BlobsParameters::setDefault()
{
    mBpm = 90;
    mBpmAmplitude = 1;
    mDistortionAmount = 1;
    mDistortionSpeed = 1;
    mMvtSpeed = 1;
    mMvtRange = 1;
}

void BlobsParameters::updateParameters(const BlobsParameters& inParameters)
{
    if (inParameters.mBpm != -1)
    {
        mBpm = inParameters.mBpm;
    }
    if (inParameters.mBpmAmplitude != -1)
    {
        mBpmAmplitude = inParameters.mBpmAmplitude;
    }
    if (inParameters.mDistortionAmount != -1)
    {
        mDistortionAmount = inParameters.mDistortionAmount;
    }
    if (inParameters.mDistortionSpeed != -1)
    {
        mDistortionSpeed = inParameters.mDistortionSpeed;
    }
    if (inParameters.mMvtSpeed != -1)
    {
        mMvtSpeed = inParameters.mMvtSpeed;
    }
    if (inParameters.mMvtRange != -1)
    {
        mMvtRange = inParameters.mMvtRange;
    }
    
}



// -----------------------------------------------------------------------------
void SandParameters::setDefault()
{
    mUpdateColor = false;
    mSandColor[0] = 254.5;
    mSandColor[1] = 175.7;
    mSandColor[2] = 50.3;
    mSandSpeed = 0.03;
    mSandAmount = 0.5;
}

void SandParameters::updateParameters(const SandParameters& inParameters)
{
    if (inParameters.mSandSpeed != -1)
    {
        mSandSpeed = inParameters.mSandSpeed;
    }
    if (inParameters.mSandAmount != -1)
    {
        mSandAmount = inParameters.mSandAmount;
    }
    if (inParameters.mUpdateColor)
    {
        if (inParameters.mSandColor[0] != -1)
            mSandColor[0] = inParameters.mSandColor[0];
        if (inParameters.mSandColor[1] != -1)
            mSandColor[1] = inParameters.mSandColor[1];
        if (inParameters.mSandColor[2] != -1)
            mSandColor[2] = inParameters.mSandColor[2];
    }
}

// -----------------------------------------------------------------------------
void BlinkingColorParameters::setDefault()
{
    mUpdateDisplay = true;
    mDisplay = false;
    mColorChangeSpeed = 0.1;
    mBrightness = 0.8;
    mColorAmount = 1.0;
    mAlpha = 1.0;
}

void BlinkingColorParameters::updateParameters(const BlinkingColorParameters& inParameters)
{
    if (inParameters.mUpdateDisplay)
    {
        mDisplay = inParameters.mDisplay;
    }
    if (inParameters.mColorChangeSpeed != -1)
    {
        mColorChangeSpeed = inParameters.mColorChangeSpeed;
    }
    if (inParameters.mBrightness != -1)
    {
        mBrightness = inParameters.mBrightness;
    }
    if (inParameters.mColorAmount != -1)
    {
        mColorAmount = inParameters.mColorAmount;
    }
    if (inParameters.mAlpha != -1)
    {
        mAlpha = inParameters.mAlpha;
    }
}
