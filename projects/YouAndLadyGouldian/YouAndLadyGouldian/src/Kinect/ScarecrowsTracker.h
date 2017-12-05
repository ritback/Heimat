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

public:
    void setJointsEffectRange(float inValue);
    float getJointsEffectRange();
    void setJointsHasMoveDistance(float inValue);
    float getJointsHasMoveDistance();
    void setJointsAttractionInc(float inValue);
    float getJointsAttractionInc();
    void setJointsAttractionMin(float inValue);
    float getJointsAttractionMin();
    void setJointsAttractionMax(float inValue);
    float getJointsAttractionMax();

public:
    void setTreeCreationTime(float inValue);
    float getTreeCreationTime();

private:
    BirdsFlock* mFlock;
};
