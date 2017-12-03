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

private:
    BirdsFlock* mFlock;
    int mSeedNum;
    int mTreeNum;

};
 
