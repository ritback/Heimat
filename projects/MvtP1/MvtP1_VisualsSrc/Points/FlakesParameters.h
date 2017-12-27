#pragma once

#include "ofMain.h"

struct FlakesParameters
{
    int mNumFlakes = -1; // from 0 to 150
    float mForceFieldMag = -1; // force of the force field. From 0 to 20
    float mWorldViscosity = -1; // force of the force field. From 0 to 1
    float mMass = -1; // force of the force field. From 1 to 20
    
    void setDefault();
    void updateParameters(const FlakesParameters& inParameters);
};

