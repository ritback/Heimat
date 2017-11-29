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

protected:
    bool isJointOnRightSide(const NUI_SKELETON_POSITION_INDEX& index);
    bool isJointOnLeftSide(const NUI_SKELETON_POSITION_INDEX& index);
    bool isJointOnRightHandComponent(const NUI_SKELETON_POSITION_INDEX& index);
    bool isJointOnLeftHandComponent(const NUI_SKELETON_POSITION_INDEX& index);
    bool isJointOnRightArm(const NUI_SKELETON_POSITION_INDEX& index);
    bool isJointOnRightLeg(const NUI_SKELETON_POSITION_INDEX& index);
    bool isJointOnLeftArm(const NUI_SKELETON_POSITION_INDEX& index);
    bool isJointOnLeftLeg(const NUI_SKELETON_POSITION_INDEX& index);
    bool isJointOnTrunk(const NUI_SKELETON_POSITION_INDEX& index);

public:
    NUI_SKELETON_TRACKING_STATE mTrackingState;

protected:
    SkeletonJointType mJoints[NUI_SKELETON_POSITION_COUNT];
};

#include "HE_Skeleton.hpp"
