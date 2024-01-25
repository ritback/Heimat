#pragma once

#include "HE_KinectDef.h"
#include "HE_Kinect.h"

class HESkeletonJoint;

template<class SkeletonType>
class HESkeletonsTracker: public HESkeletonsStreamHandlerInterface
{
public:
    HESkeletonsTracker(HEKinect* inKinect);
    ~HESkeletonsTracker();

public:
    virtual void update(); // update position of skeleton
    virtual void render(); // render skeletons (drawbone and render joints)

public:
    virtual void processSkeletons(NUI_SKELETON_FRAME& skeletonFrame) override;

public:
    void getHeadsJoints(HESkeletonJoint* outJoints, int* outSize); // must be an array of NUI_SKELETON_COUNT

private:
    ofPoint skeletonToScreen(Vector4 inSkeletonPoint,
                             float inScreenWidth,
                             float inScreenHeight);

protected:
    HEKinect* mKinect;
    SkeletonType mTrackedSkeletons[NUI_SKELETON_COUNT];
};

#include "HE_SkeletonsTracker.hpp"
