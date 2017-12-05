#pragma once

#include "ofMain.h"
#include "HE_Skeleton.h"
#include "ScarecrowJoint.h"

class BirdsFlock;

class Scarecrow: public HESkeleton<ScarecrowJoint>
{
public:
    Scarecrow();
    virtual ~Scarecrow();

public:
    void applyEffectOnBirds(BirdsFlock* inFlock);

public:
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
    void checkTreeCreation(const ofPoint& inPos);

private:
    float mTreeCreationTime;
    float mLastTrunkMoveTime;

};
