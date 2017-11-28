#include "HE_KinectApp.h"

//------------------------------------------------------------------------------
template<class SkeletonTrackerType>
HEKinectBaseApp<SkeletonTrackerType>::HEKinectBaseApp(bool inUseSkeleton, bool inUseDepthImage)
    : mKinect(inUseSkeleton, inUseDepthImage)
    , mUseDepthImage(inUseDepthImage)
    , mUseSkeletons(inUseSkeleton)
    , mKinectImage(0)
    , mSkeletonsTracker(0)
{
    if(mUseDepthImage)
    {
        mKinectImage = new HEKinectDepthImage(&mKinect,
                                              ofPoint(0, 0),
                                       ofPoint(ofGetWindowWidth(), ofGetWindowHeight()));
    }
    if(mUseSkeletons)
    {
        mSkeletonsTracker = new SkeletonTrackerType(&mKinect);
    }
}

template<class SkeletonTrackerType>
HEKinectBaseApp<SkeletonTrackerType>::~HEKinectBaseApp()
{
    if(mUseDepthImage)
    {
        delete mKinectImage;
    }
    if(mUseSkeletons)
    {
        delete mSkeletonsTracker;
    }
}

//------------------------------------------------------------------------------
template<class SkeletonTrackerType>
void HEKinectBaseApp<SkeletonTrackerType>::updateDepthImage()
{
    if (mKinect.isAvailable())
    {
        if (mUseDepthImage)
        {
            mKinectImage->update();
        }
    }
}

template<class SkeletonTrackerType>
void HEKinectBaseApp<SkeletonTrackerType>::renderDepthImage()
{
    if (!mKinect.isAvailable())
    {
        ofBackground(255, 0, 0);
        ofSetColor(0);
        for (int i = 0; i < ofGetWindowWidth()/100; ++i)
            for (int j = 0; j < ofGetWindowHeight() / 50; ++j)
                ofDrawBitmapString("NO KINECT!", i*100, j*50);
        return;
    }

    if(mUseDepthImage)
    {
        mKinectImage->render();
    }
}

//------------------------------------------------------------------------------
template<class SkeletonTrackerType>
void HEKinectBaseApp<SkeletonTrackerType>::updateSkeletons()
{
    if (mKinect.isAvailable())
    {
        if (mUseSkeletons)
        {
            mSkeletonsTracker->update();
        }
    }
}

template<class SkeletonTrackerType>
void HEKinectBaseApp<SkeletonTrackerType>::renderSkeletons()
{
    if (!mKinect.isAvailable())
    {
        ofBackground(255, 0, 0);
        ofSetColor(0);
        for (int i = 0; i < ofGetWindowWidth() / 100; ++i)
            for (int j = 0; j < ofGetWindowHeight() / 50; ++j)
                ofDrawBitmapString("NO KINECT!", i * 100, j * 50);
        return;
    }

    if (mUseSkeletons)
    {
        mSkeletonsTracker->render();
    }
}
