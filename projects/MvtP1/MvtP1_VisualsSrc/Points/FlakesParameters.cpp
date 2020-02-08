#include "FlakesParameters.h"

// -----------------------------------------------------------------------------
void FlakesParameters::setDefault()
{
    mNumFlakes = 100;
    mForceFieldMag = 5.1;
    mWorldViscosity = 0.3;
    mMass = 15.0;
    mMaxColor.set(255, 255, 255);
    mMinColor.set(0, 0, 0);
}

void FlakesParameters::updateParameters(const FlakesParameters& inParameters)
{
    if (inParameters.mNumFlakes != -1)
    {
        mNumFlakes = inParameters.mNumFlakes;
    }
    if (inParameters.mForceFieldMag != -1)
    {
        mForceFieldMag = inParameters.mForceFieldMag;
    }
    if (inParameters.mWorldViscosity != -1)
    {
        mWorldViscosity = inParameters.mWorldViscosity;
    }
    if (inParameters.mMass != -1)
    {
        mMass = inParameters.mMass;
    }
    if(inParameters.mUpdateColor)
    {
        mMaxColor = inParameters.mMaxColor;
        mMinColor = inParameters.mMinColor;
        mUpdateColor = false;
    }
}


