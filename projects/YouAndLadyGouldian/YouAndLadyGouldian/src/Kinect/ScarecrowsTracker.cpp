#include "ScarecrowsTracker.h"

#include "Kinect.h"
#include "..\Birds\BirdsFlock.h"
#include "Scarecrow.h"

ScarecrowsTracker::ScarecrowsTracker(HEKinect* inKinect, BirdsFlock* inFlock)
    : HESkeletonsTracker<Scarecrow>(inKinect)
    , mFlock(inFlock)
{

}

ScarecrowsTracker::~ScarecrowsTracker()
{

}

//------------------------------------------------------------------------------
void ScarecrowsTracker::update()
{
    HESkeletonsTracker<Scarecrow>::update();

    Scarecrow *currentSkeleton = &mTrackedSkeletons[0];
    for(int i = 0; i < NUI_SKELETON_COUNT; ++i)
    {
        if(currentSkeleton->mTrackingState == NUI_SKELETON_TRACKED)
        {
            currentSkeleton->applyEffectOnBirds(mFlock);
        }
        ++currentSkeleton;
    }
}


