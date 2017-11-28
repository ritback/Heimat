#include "HE_SkeletonJoint.h"

HESkeletonJoint::HESkeletonJoint()
    : mTrackingState(NUI_SKELETON_POSITION_NOT_TRACKED)
    , mPos(0, 0, 0)
    , mPositionIndex(0)
{

}

HESkeletonJoint::HESkeletonJoint(const HESkeletonJoint& inJoint)
    : mTrackingState(inJoint.mTrackingState)
    , mPos(inJoint.mPos)
    , mPositionIndex(inJoint.mPositionIndex)
{

}

HESkeletonJoint::~HESkeletonJoint()
{

}


// -----------------------------------------------------------------------------
void HESkeletonJoint::update(const HESkeletonJoint& inJoint)
{
    mTrackingState = inJoint.mTrackingState;
    mPos = inJoint.mPos;
    mPositionIndex = inJoint.mPositionIndex;
}

void HESkeletonJoint::render()
{
    if (mTrackingState == NUI_SKELETON_POSITION_INFERRED)
    {
        renderInferred();
    }
    else if (mTrackingState == NUI_SKELETON_POSITION_TRACKED)
    {
        renderTracked();
    }
}

// -----------------------------------------------------------------------------
void HESkeletonJoint::renderInferred()
{
    ofSetColor(255, 0, 0);

    float radius = 5;
    bool ignoreDepthWhenDrawing = true;
    if(ignoreDepthWhenDrawing)
    {
        ofDrawCircle(ofPoint(mPos.x, mPos.y), radius);
    }
    else
    {
        ofDrawCircle(mPos, radius);
    }
}

void HESkeletonJoint::renderTracked()
{
    ofSetColor(255, 255, 255);

    float radius = 5;
    bool ignoreDepthWhenDrawing = true;
    if(ignoreDepthWhenDrawing)
    {
        ofDrawCircle(ofPoint(mPos.x, mPos.y), radius);
    }
    else
    {
        ofDrawCircle(mPos, radius);
    }
}
