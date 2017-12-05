#include "HE_Skeleton.h"


template<class SkeletonJointType>
HESkeleton<SkeletonJointType>::HESkeleton()
{

}

template<class SkeletonJointType>
HESkeleton<SkeletonJointType>::~HESkeleton()
{

}

// -----------------------------------------------------------------------------
template<class SkeletonJointType>
void HESkeleton<SkeletonJointType>::drawSkeleton()
{
    ofPushStyle();
    // Render Torso
    drawBone(NUI_SKELETON_POSITION_HEAD, NUI_SKELETON_POSITION_SHOULDER_CENTER);
    drawBone(NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_LEFT);
    drawBone(NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_RIGHT);
    drawBone(NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SPINE);
    drawBone(NUI_SKELETON_POSITION_SPINE, NUI_SKELETON_POSITION_HIP_CENTER);
    drawBone(NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_LEFT);
    drawBone(NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_RIGHT);

    // Left Arm
    drawBone(NUI_SKELETON_POSITION_SHOULDER_LEFT, NUI_SKELETON_POSITION_ELBOW_LEFT);
    drawBone(NUI_SKELETON_POSITION_ELBOW_LEFT, NUI_SKELETON_POSITION_WRIST_LEFT);
    drawBone(NUI_SKELETON_POSITION_WRIST_LEFT, NUI_SKELETON_POSITION_HAND_LEFT);

    // Right Arm
    drawBone(NUI_SKELETON_POSITION_SHOULDER_RIGHT, NUI_SKELETON_POSITION_ELBOW_RIGHT);
    drawBone(NUI_SKELETON_POSITION_ELBOW_RIGHT, NUI_SKELETON_POSITION_WRIST_RIGHT);
    drawBone(NUI_SKELETON_POSITION_WRIST_RIGHT, NUI_SKELETON_POSITION_HAND_RIGHT);

    // Left Leg
    drawBone(NUI_SKELETON_POSITION_HIP_LEFT, NUI_SKELETON_POSITION_KNEE_LEFT);
    drawBone(NUI_SKELETON_POSITION_KNEE_LEFT, NUI_SKELETON_POSITION_ANKLE_LEFT);
    drawBone(NUI_SKELETON_POSITION_ANKLE_LEFT, NUI_SKELETON_POSITION_FOOT_LEFT);

    // Right Leg
    drawBone(NUI_SKELETON_POSITION_HIP_RIGHT, NUI_SKELETON_POSITION_KNEE_RIGHT);
    drawBone(NUI_SKELETON_POSITION_KNEE_RIGHT, NUI_SKELETON_POSITION_ANKLE_RIGHT);
    drawBone(NUI_SKELETON_POSITION_ANKLE_RIGHT, NUI_SKELETON_POSITION_FOOT_RIGHT);

    for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i)
    {   
        mJoints[i].render();
    }

    ofPopStyle();
}

// -----------------------------------------------------------------------------
template<class SkeletonJointType>
void HESkeleton<SkeletonJointType>::drawBone(NUI_SKELETON_POSITION_INDEX inBone0,
                        NUI_SKELETON_POSITION_INDEX inBone1)
{

    const HESkeletonJoint &joint0 = mJoints[inBone0];
    const HESkeletonJoint &joint1 = mJoints[inBone1];

    NUI_SKELETON_POSITION_TRACKING_STATE joint0State = joint0.mTrackingState;
    NUI_SKELETON_POSITION_TRACKING_STATE joint1State = joint1.mTrackingState;

    // If we can't find either of these joints, exit
    if (joint0State == NUI_SKELETON_POSITION_NOT_TRACKED
        || joint1State == NUI_SKELETON_POSITION_NOT_TRACKED)
    {
        return;
    }

    // Don't draw if both points are inferred
    if (joint0State == NUI_SKELETON_POSITION_INFERRED
        && joint1State == NUI_SKELETON_POSITION_INFERRED)
    {
        return;
    }

    // We assume all drawn bones are inferred unless BOTH joints are tracked
    if (joint0State == NUI_SKELETON_POSITION_TRACKED
        && joint1State == NUI_SKELETON_POSITION_TRACKED)
    {
        ofSetColor(255); // track color
    }
    else
    {
        ofSetColor(255, 0, 0); // inferred color
    }

    bool ignoreDepthWhenDrawing = true;
    if(ignoreDepthWhenDrawing)
    {
        ofDrawLine(ofPoint(joint0.mPos.x, joint0.mPos.y),
                   ofPoint(joint1.mPos.x, joint1.mPos.y));
    }
    else
    {
        ofDrawLine(joint0.mPos,
                   joint1.mPos);
    }
}
// -----------------------------------------------------------------------------
template<class SkeletonJointType>
const HESkeletonJoint& HESkeleton<SkeletonJointType>::getHeadJoint()
{
    return mJoints[NUI_SKELETON_POSITION_HEAD];
}

// -----------------------------------------------------------------------------
template<class SkeletonJointType>
void HESkeleton<SkeletonJointType>::updateJoint(HESkeletonJoint* inJoint)
{
    HESkeletonJoint* joint = &(mJoints[inJoint->mPositionIndex]);
    joint->update(*inJoint);
}

// -----------------------------------------------------------------------------
template<class SkeletonJointType>
bool HESkeleton<SkeletonJointType>::isJointOnRightSide(const NUI_SKELETON_POSITION_INDEX& index)
{
    bool ret = false;
    switch (index)
    {
    case NUI_SKELETON_POSITION_SHOULDER_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_ELBOW_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_WRIST_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_HAND_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_HIP_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_KNEE_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_ANKLE_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_FOOT_RIGHT: ret = true; break;
    default:
        break;
    }
    return ret;
}

template<class SkeletonJointType>
bool HESkeleton<SkeletonJointType>::isJointOnLeftSide(const NUI_SKELETON_POSITION_INDEX& index)
{
    bool ret = false;
    switch (index)
    {
    case NUI_SKELETON_POSITION_SHOULDER_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_ELBOW_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_WRIST_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_HAND_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_HIP_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_KNEE_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_ANKLE_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_FOOT_LEFT: ret = true; break;
    default:
        break;
    }
    return ret;
}

template<class SkeletonJointType>
bool HESkeleton<SkeletonJointType>::isJointOnRightHandComponent(const NUI_SKELETON_POSITION_INDEX& index)
{
    bool ret = false;
    switch (index)
    {
    case NUI_SKELETON_POSITION_WRIST_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_HAND_RIGHT: ret = true; break;
    default:
        break;
    }
    return ret;
}

template<class SkeletonJointType>
bool HESkeleton<SkeletonJointType>::isJointOnLeftHandComponent(const NUI_SKELETON_POSITION_INDEX& index)
{
    bool ret = false;
    switch (index)
    {
    case NUI_SKELETON_POSITION_WRIST_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_HAND_LEFT: ret = true; break;
    default:
        break;
    }
    return ret;
}




template<class SkeletonJointType>
bool HESkeleton<SkeletonJointType>::isJointOnRightArm(const NUI_SKELETON_POSITION_INDEX& index)
{
    bool ret = false;
    switch (index)
    {
    case NUI_SKELETON_POSITION_SHOULDER_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_ELBOW_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_WRIST_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_HAND_RIGHT: ret = true; break;
    default:
        break;
    }
    return ret;
}

template<class SkeletonJointType>
bool HESkeleton<SkeletonJointType>::isJointOnRightLeg(const NUI_SKELETON_POSITION_INDEX& index)
{
    bool ret = false;
    switch (index)
    {
    case NUI_SKELETON_POSITION_HIP_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_KNEE_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_ANKLE_RIGHT: ret = true; break;
    case NUI_SKELETON_POSITION_FOOT_RIGHT: ret = true; break;
    default:
        break;
    }
    return ret;
}

template<class SkeletonJointType>
bool HESkeleton<SkeletonJointType>::isJointOnLeftArm(const NUI_SKELETON_POSITION_INDEX& index)
{
    bool ret = false;
    switch (index)
    {
    case NUI_SKELETON_POSITION_SHOULDER_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_ELBOW_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_WRIST_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_HAND_LEFT: ret = true; break;
    default:
        break;
    }
    return ret;
}

template<class SkeletonJointType>
bool HESkeleton<SkeletonJointType>::isJointOnLeftLeg(const NUI_SKELETON_POSITION_INDEX& index)
{
    bool ret = false;
    switch (index)
    {
    case NUI_SKELETON_POSITION_HIP_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_KNEE_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_ANKLE_LEFT: ret = true; break;
    case NUI_SKELETON_POSITION_FOOT_LEFT: ret = true; break;
    default:
        break;
    }
    return ret;
}

template<class SkeletonJointType>
bool HESkeleton<SkeletonJointType>::isJointOnTrunk(const NUI_SKELETON_POSITION_INDEX& index)
{
    bool ret = false;
    switch (index)
    {
    case NUI_SKELETON_POSITION_HIP_CENTER: ret = true; break;
    case NUI_SKELETON_POSITION_SPINE: ret = true; break;
    case NUI_SKELETON_POSITION_SHOULDER_CENTER: ret = true; break;
    default:
        break;
    }
    return ret;
}
