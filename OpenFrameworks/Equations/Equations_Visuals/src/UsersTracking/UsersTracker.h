#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include <vector>

#define PORT 12345

#include "User.h"

class Actor;
class HEStreetWorld;
class HEBoxWorld;
template<class BoidType, class WorldType>
class HEFlock;

class UsersTracker
{
public:
    UsersTracker(HEFlock<Actor, HEStreetWorld> *mFlock);
	~UsersTracker();

public:
	void update();
	void renderUsers();

public:
    void renderRoom();

    void setRoomLimitMin(ofPoint& inRoomLimit);
    ofPoint getRoomLimitMin();
    void setRoomLimitMax(ofPoint& inRoomLimit);
    ofPoint getRoomLimitMax();
    void setRoomLimit(const ofRectangle& inRoomLimit);
    ofRectangle getRoomLimit();

public:
    void changeUsersInfluenceCohesion(float & inValue);
    void changeUsersInfluenceSeparation(float & inValue);
    void changeUsersInfluenceAlignement(float & inValue);

public:
    float getUsersInfluenceCohesion();
    float getUsersInfluenceSeparation();
    float getUsersInfluenceAlignement();

    /*
    float getUsersInfluenceCohesionMaxValue();
    float getUsersInfluenceAlignementMaxValue();
    float getUsersInfluenceSeparationMaxValue();
    */

private:
	typedef std::vector<User*> Users;
	typedef Users::iterator UsersIt;
    static const int NUM_USERS = 10;
	Users mUsers;
    int mNumDetectedUsers;
    ofPoint mDetectedUsersPos[NUM_USERS];
    ofPoint mDetectedUsersVel[NUM_USERS];
    

private:
	ofPoint mSafeZone;
    ofRectangle mRoomRect;
    ofPoint mActualRoomSize;

private:
    ofxOscReceiver mOSCReceiver;

private:
    HEFlock<Actor, HEStreetWorld>* mFlock;
    
private:
    HEFlockRules mUsersInfluence;
    //float mUsersCohesionInfluenceMaxValue;
    //float mUsersSeparationInfluenceMaxValue;
    //float mUsersAlignmentInfluenceMaxValue;
};
