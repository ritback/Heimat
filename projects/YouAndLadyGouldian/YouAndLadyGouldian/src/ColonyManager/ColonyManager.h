#pragma once

#include "ofMain.h"

#include "BirdsFlock.h"

class ColonyManager
{
public:
    ColonyManager(BirdsFlock* inFlock);
    ~ColonyManager();

public:
    void update();

public:
    void urlResponse(ofHttpResponse& inResponse);

private:
    void setNumBirds();

private:
    void updateURL();

private:
    BirdsFlock* mFlock;
    int mNumSeed;

private:
    float mNextUpdateTime;
    bool mShouldUpdateNumBirds;
};
 
