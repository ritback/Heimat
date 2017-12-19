#include "SpiritsParameters.h"

// -----------------------------------------------------------------------------
void SpiritsParameters::setDefault()
{
    mNumSpirits = 10;
    mForceFieldMag = 5.1;
    mHeadMass = 5.0;
    mLength = 50;
}

void SpiritsParameters::updateParameters(const SpiritsParameters& inParameters)
{
    if (inParameters.mNumSpirits != -1)
    {
        mNumSpirits = inParameters.mNumSpirits;
    }
    if (inParameters.mForceFieldMag != -1)
    {
        mForceFieldMag = inParameters.mForceFieldMag;
    }
    if (inParameters.mHeadMass != -1)
    {
        mHeadMass = inParameters.mHeadMass;
    }
    if (inParameters.mLength != -1)
    {
        mLength = inParameters.mLength;
    }
}


