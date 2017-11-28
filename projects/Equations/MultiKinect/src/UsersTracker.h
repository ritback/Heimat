#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Kinect/Kinect_Kinect.h"
#include "Kinect/Kinect_DepthImage_MultiKinect.h"
#include "Kinect/Kinect_DepthLessBkgndImage.h"
#include <vector>

class UsersTracker
{
public:
	UsersTracker();
	~UsersTracker();

public:
	void update();

public:
	void refreshBackgroundNeeded();
	void render();
	void renderBlobs(const ofPoint& inTopLeft,
                     const ofPoint& inSize);
	void renderUsers(const ofPoint& inTopLeft,
                     const ofPoint& inSize);

public:
    ofPoint getRoomSize();
    void getUserPosInRoom(ofPoint** outUsers, int* outNumUsers);
    int getNumActiveUser();

public:
	void setImgThreshold(float inThreshold);
	float getImgThreshold();
	void setImgBlur(float inBlur);
	float getImgBlur();

private:
    std::vector<Kinect*> mKinects;

private:
    DepthImageMultiKinectRotated* mDepthImageMultiKinect;
    DepthLessBkgndImage* mDepthLessBkgnd;

private:
    ofxCvContourFinder mContourFinder;

private:
	typedef std::vector<ofPoint> Users;
	typedef Users::iterator UsersIt;
    static const int NUM_USERS = 10;
	Users mUsers;
    int mNumActiveUser;

private:
	ofPoint mSafeZone;

};
