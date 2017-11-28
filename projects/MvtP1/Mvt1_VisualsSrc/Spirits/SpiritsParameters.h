#pragma once

#include "ofMain.h"

struct SpiritsParameters
{
    int mNumSpirits = -1; // from 0 to 150
    float mForceFieldMag = -1; // force of the force field. From 0 to 20
    float mHeadMass = -1; // force of the force field. From 1 to 20
    float mLength = -1;
    
    void setDefault();
    void updateParameters(const SpiritsParameters& inParameters);
};

