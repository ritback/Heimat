#pragma once

#include "ofMain.h"

struct HEFlockRules
{
public:
    HEFlockRules(const float& inCohesion = 0, const float& inSeparation = 0, const float& inAlignement = 0)
    : mCohesion(inCohesion)
    , mSeparation(inSeparation)
    , mAlignement(inAlignement)
    {
        
    };
    HEFlockRules(const HEFlockRules& inFlockRules)
    : mCohesion(inFlockRules.mCohesion)
    , mSeparation(inFlockRules.mSeparation)
    , mAlignement(inFlockRules.mAlignement)
    {
        
    };
    ~HEFlockRules() {};
    
public:
    float mCohesion = 0;
    float mSeparation = 0;
    float mAlignement = 0;
};
