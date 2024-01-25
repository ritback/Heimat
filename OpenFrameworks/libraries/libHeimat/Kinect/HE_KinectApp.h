#pragma once

#include "ofMain.h"

#include "HE_Kinect.h"
#include "HE_KinectDepthImage.h"
#include "HE_Skeleton.h"
#include "HE_SkeletonJoint.h"
#include "HE_SkeletonsTracker.h"


template<class SkeletonTrackerType>
class HEKinectBaseApp
{
public:
    HEKinectBaseApp(bool inUseSkeleton = true, bool inUseDepthImage = true);
    virtual ~HEKinectBaseApp();

public:
    void updateDepthImage();
    void renderDepthImage();

public:
    void updateSkeletons();
    void renderSkeletons();
    
public:
    HEKinect mKinect;
    const bool mUseDepthImage;
    HEKinectDepthImage* mKinectImage;
    const bool mUseSkeletons;
    SkeletonTrackerType* mSkeletonsTracker;
};

#include "HE_KinectApp.hpp"

//------------------------------------------------------------------------------
// sample of basic implementation...
class HEKinectApp: public HEKinectBaseApp<HESkeletonsTracker<HESkeleton<HESkeletonJoint>>>
{
public:
    HEKinectApp(bool inUseSkeleton = true, bool inUseDepthImage = true);
    virtual ~HEKinectApp();

};

