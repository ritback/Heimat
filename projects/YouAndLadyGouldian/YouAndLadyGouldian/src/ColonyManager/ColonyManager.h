#pragma once

#include "ofMain.h"

class BirdsFlock;
class Forest;

class ColonyManager
{
public:
    ColonyManager(BirdsFlock* inFlock, Forest * inForest);
    ~ColonyManager();

public:
    void update();

public:
    void urlResponse(ofHttpResponse& inResponse);

public:
    void updateFlockWithWeb(bool inValue);
    bool isFlockUpdatedWithWeb();

private:
    void setNumBirds();

private:
    void updateURL();

private:
    BirdsFlock* mFlock;
    Forest* mForest;
    int mNumSeed;
    float mSmoothNumBirds;

private:
    float mNextUpdateTime;
    bool mUpdateNumBirdsWithWeb;
};
 
