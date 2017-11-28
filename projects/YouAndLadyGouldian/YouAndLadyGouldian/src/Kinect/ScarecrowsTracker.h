#pragma once

#include "ofMain.h"
#include "HE_SkeletonsTracker.h"
#include "Scarecrow.h"

class Kinect;
class BirdsFlock;

class ScarecrowsTracker : public HESkeletonsTracker<Scarecrow>
{
public:
    ScarecrowsTracker(HEKinect* inKinect, BirdsFlock* inFlock);
    virtual ~ScarecrowsTracker();

public:
    virtual void update() override;

private:
    BirdsFlock* mFlock;
};
