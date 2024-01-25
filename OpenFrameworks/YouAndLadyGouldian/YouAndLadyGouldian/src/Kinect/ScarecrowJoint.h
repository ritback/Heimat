#pragma once

#include "ofMain.h"
#include "HE_SkeletonJoint.h"

#include <deque>

class ScarecrowJoint: public HESkeletonJoint
{
public:
    ScarecrowJoint();
    ScarecrowJoint(const ScarecrowJoint& inJoint);
    virtual ~ScarecrowJoint();

public:
    virtual void update(const HESkeletonJoint& inJoint) override;

public:
    void setAttraction(float inValue);
    float getAttraction();

public:
    void setEffectRange(float inValue);
    float getEffectRange();
    void setHasMoveDistance(float inValue);
    float getHasMoveDistance();
    void setAttractionInc(float inValue);
    float getAttractionInc();
    void setAttractionMin(float inValue);
    float getAttractionMin();
    void setAttractionMax(float inValue);
    float getAttractionMax();

protected:
    virtual void renderTracked() override;

private:
    void updateAttraction();
    bool hasMove(); // if the joint as moove during the last 10 frames...

private:
    typedef std::deque<ofPoint*> Tail;
    typedef Tail::iterator TailIt;
    Tail mTail;

private:
    float mEffectRange;
    float mAttraction;
    float mAttractionMin;
    float mAttractionMax;
    float mAttractionInc;
    float mHasMoveDistance;
    int mUpdateTailFrameCount;
};
