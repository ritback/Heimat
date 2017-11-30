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


//------------------------------------------------------------------------------
void ScarecrowsTracker::setJointsHasMoveDistance(float inValue)
{
    for(int i = 0; i < NUI_SKELETON_COUNT; ++i)
    {
        mTrackedSkeletons[i].setJointsHasMoveDistance(inValue);
    }
}

float ScarecrowsTracker::getJointsHasMoveDistance()
{
    return mTrackedSkeletons[0].getJointsHasMoveDistance();
}

void ScarecrowsTracker::setJointsAttractionInc(float inValue)
{
    for(int i = 0; i < NUI_SKELETON_COUNT; ++i)
    {
        mTrackedSkeletons[i].setJointsAttractionInc(inValue);
    }
}

float ScarecrowsTracker::getJointsAttractionInc()
{
    return mTrackedSkeletons[0].getJointsAttractionInc();
}

void ScarecrowsTracker::setJointsAttractionMin(float inValue)
{
    for(int i = 0; i < NUI_SKELETON_COUNT; ++i)
    {
        mTrackedSkeletons[i].setJointsAttractionMin(inValue);
    }
}

float ScarecrowsTracker::getJointsAttractionMin()
{
    return mTrackedSkeletons[0].getJointsAttractionMin();
}

void ScarecrowsTracker::setJointsAttractionMax(float inValue)
{
    for(int i = 0; i < NUI_SKELETON_COUNT; ++i)
    {
        mTrackedSkeletons[i].setJointsAttractionMax(inValue);
    }
}

float ScarecrowsTracker::getJointsAttractionMax()
{
    return mTrackedSkeletons[0].getJointsAttractionMax();
}




