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
    void checkTreeCreation(const ofPoint& inPos);

private:
    void limitTrunkAttractionToElbow(ScarecrowJoint* joint, int i);
    void detectTrunkMoves(ScarecrowJoint* joint, int i);

private:
    void applyForceToBirds(BirdsFlock* inFlock, const ofPoint& inJointPos, float forceMag, float inRange);

private:
    void applyForceToBirdsBetween2Joints(BirdsFlock* inFlock,
                                         NUI_SKELETON_POSITION_INDEX inJoint1,
                                         NUI_SKELETON_POSITION_INDEX inJoint2);

private:
    float mTreeCreationTime;
    float mLastTrunkMoveTime;

};
