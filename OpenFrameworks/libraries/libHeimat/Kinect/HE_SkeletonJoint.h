#pragma once

#include "HE_KinectDef.h"

class HESkeletonJoint
{
public:
    HESkeletonJoint();
    HESkeletonJoint(const HESkeletonJoint& inJoint);
    virtual ~HESkeletonJoint();

public:
    virtual void update(const HESkeletonJoint& inJoint);
    virtual void render();

protected:
    virtual void renderInferred();
    virtual void renderTracked();

public:
    NUI_SKELETON_POSITION_TRACKING_STATE mTrackingState;
    int mPositionIndex;
    ofPoint mPos;
};
