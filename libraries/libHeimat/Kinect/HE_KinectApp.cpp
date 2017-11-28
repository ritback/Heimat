#include "HE_KinectApp.h"

//------------------------------------------------------------------------------
HEKinectApp::HEKinectApp(bool inUseSkeleton, bool inUseDepthImage)
    : HEKinectBaseApp<HESkeletonsTracker<HESkeleton<HESkeletonJoint>>>(inUseSkeleton, inUseDepthImage)
{

}

HEKinectApp::~HEKinectApp()
{

}
