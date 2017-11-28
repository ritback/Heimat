#pragma once

#include "HE_KinectDef.h"
#include "HE_SkeletonJoint.h"

template<class SkeletonJointType>
class HESkeleton
{
public:
    HESkeleton();
    virtual ~HESkeleton();

public:
    void drawSkeleton();
    void drawBone(NUI_SKELETON_POSITION_INDEX inBone0,
                  NUI_SKELETON_POSITION_INDEX inBone1);

public:
    const HESkeletonJoint& getHeadJoint();

public:
    void updateJoint(HESkeletonJoint* inJoint);

public:
    NUI_SKELETON_TRACKING_STATE mTrackingState;

protected:
    SkeletonJointType mJoints[NUI_SKELETON_POSITION_COUNT];
};

#include "HE_Skeleton.hpp"
