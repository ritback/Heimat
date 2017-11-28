#pragma once

#include "ofMain.h"

struct BlobsParameters
{
    float mBpm = -1;
    float mBpmAmplitude = -1;
    float mDistortionAmount = -1;
    float mDistortionSpeed = -1;
    float mMvtSpeed = -1;
    float mMvtRange = -1;
    
    void setDefault();
    void updateParameters(const BlobsParameters& inParameters);
};

// -----------------------------------------------------------------------------
struct SandParameters
{
    bool mUpdateColor = false;
    float mSandSpeed = -1;
    float mSandAmount = -1;
    float mSandColor[3] = {-1, -1, -1};
    
    void setDefault();
    void updateParameters(const SandParameters& inParameters);
};


// -----------------------------------------------------------------------------
struct BlinkingColorParameters
{
    bool mUpdateDisplay = false;
    bool mDisplay = false; // 0 don't display, 1 display, -1 parameter not set.
    
    float mColorChangeSpeed = -1;
    float mBrightness = -1;
    float mColorAmount = -1;
    float mAlpha = -1;
    
    void setDefault();
    void updateParameters(const BlinkingColorParameters& inParameters);
};
