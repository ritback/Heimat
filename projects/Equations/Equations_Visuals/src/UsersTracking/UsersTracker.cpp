#include "UsersTracker.h"

#include "HE_FlockingWorld.h"
#include "Actor.h"
#include "HE_Flock.h"

UsersTracker::UsersTracker(HEFlock<Actor, StreetWorld> *inFlock)
	: mSafeZone(ofPoint(-10000, -10000))
    , mRoomRect((inFlock->getWorld())->getWorldLimit())
    , mActualRoomSize(mRoomRect.getWidth(), mRoomRect.getHeight())
	, mFlock(inFlock)
    , mUsersCohesionInfluence(0)
    , mUsersSeparationInfluence(0)
    , mUsersAlignmentInfluence(0)
    , mUsersCohesionInfluenceMaxValue(2.5)
    , mUsersSeparationInfluenceMaxValue(2.5)
    , mUsersAlignmentInfluenceMaxValue(2.5)
    , mDetectedUsersPos()
    , mDetectedUsersVel()
    , mNumDetectedUsers(0)
{
	for (int i = 0; i < NUM_USERS; ++i)
	{
        mDetectedUsersPos[i] = ofPoint(0, 0, 0);
        mDetectedUsersVel[i] = ofPoint(0, 0, 0);
		User* newUser = new User(mSafeZone);
		mUsers.push_back(newUser);
		inFlock->addBoid(newUser);
	}

    mOSCReceiver.setup(PORT);
}

UsersTracker::~UsersTracker()
{

}

//--------------------------------------------------------------
inline float remap(float value, float istart, float istop, float ostart, float ostop)
{
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void UsersTracker::update()
{
    ofPoint roomSize = ofPoint(mRoomRect.getWidth(), mRoomRect.getHeight());
    ofPoint streamToRoomRatio = roomSize / mActualRoomSize;
    ofPoint streamToRoomOffset = mRoomRect.getTopLeft();
    
    float newUsersCohesionInfluence = -1;
    float newUsersSeparationInfluence = -1;
    float newUsersAlignmentInfluence = -1;

    while(mOSCReceiver.hasWaitingMessages())
    {
        ofxOscMessage message;
        mOSCReceiver.getNextMessage(message);

        if(message.getAddress() == "/roomSize")
        {
            mActualRoomSize.y = message.getArgAsFloat(0);
            mActualRoomSize.x = message.getArgAsFloat(1); // reversin y and x
        }
        if(message.getAddress() == "/points")
        {
            mNumDetectedUsers = message.getArgAsInt(0);
            for(int i = 0; i < mNumDetectedUsers; ++i)
            {
                
                mDetectedUsersPos[i].y = (float)message.getArgAsFloat(3 * i + 1);
                mDetectedUsersPos[i].x = (float)message.getArgAsFloat(3 * i + 2); // reversin y and x
                mDetectedUsersPos[i].z = (float)message.getArgAsFloat(3 * i + 3);
                mDetectedUsersPos[i].x = -mDetectedUsersPos[i].x + mActualRoomSize.x; // scaling user pos if the camera is reversed...
                                                                                  /*
                mDetectedUsersPos[i].x = (float)message.getArgAsFloat(3 * i + 1);
                mDetectedUsersPos[i].y = (float)message.getArgAsFloat(3 * i + 2); // reversin y and x
                mDetectedUsersPos[i].z = (float)message.getArgAsFloat(3 * i + 3);
                mDetectedUsersPos[i].y = -mDetectedUsersPos[i].y + mActualRoomSize.y; // scaling user pos if the camera is reversed...
                */
                mDetectedUsersPos[i] *= streamToRoomRatio;
                mDetectedUsersPos[i] += streamToRoomOffset;
                
            }
        }
        if(message.getAddress() == "/Cohesion")
        {
            mUsersCohesionInfluence = (float)message.getArgAsInt(0);
            mUsersCohesionInfluence = remap(mUsersCohesionInfluence, 0, 1023, 0, mUsersCohesionInfluenceMaxValue);
        }
        if(message.getAddress() == "/Separation")
        {
            mUsersSeparationInfluence = (float)message.getArgAsInt(0);
            mUsersSeparationInfluence = remap(mUsersSeparationInfluence, 0, 1023, 0, mUsersSeparationInfluenceMaxValue);
        }
        if(message.getAddress() == "/Alignment")
        {
            mUsersAlignmentInfluence = (float)message.getArgAsInt(0);
            mUsersAlignmentInfluence = remap(mUsersAlignmentInfluence, 0, 1023, 0, mUsersAlignmentInfluenceMaxValue);
        }
    }

    for(int i = 0; i < NUM_USERS; ++i)
    {
        if (i >= mNumDetectedUsers)
        {
            mDetectedUsersPos[i] = mSafeZone;
        }
        mUsers[i]->updatePositionAndVelocity(mDetectedUsersPos[i]);
        mDetectedUsersVel[i] = mUsers[i]->getVel();
    }

    for(int i = 0; i < mNumDetectedUsers; ++i)
    {
        
        mFlock->applyExternalFlockForcesToBoids(mDetectedUsersPos,
                                                mDetectedUsersVel,
                                                mNumDetectedUsers,
                                                mUsersCohesionInfluence,
                                                -mUsersSeparationInfluence,
                                                mUsersAlignmentInfluence,
                                                200);
        
    }
    
}

//--------------------------------------------------------------
void UsersTracker::renderUsers()
{
	ofPushStyle();
	ofSetColor(0, 255, 0);
	for (UsersIt it = mUsers.begin();
		 it != mUsers.end();
		 ++it)
	{
		ofDrawSphere((*it)->getPos(), 20);
	}
	ofPopStyle();
}

// -----------------------------------------------------------------------------
void UsersTracker::renderRoom()
{
    ofPushStyle();
    ofNoFill();
    ofSetColor(0, 255, 0);
    ofDrawRectangle(mRoomRect);
    ofPopStyle();
}

void UsersTracker::setRoomLimitMin(ofPoint& inRoomLimit)
{
    mRoomRect.set(inRoomLimit, mRoomRect.getBottomRight());
}

ofPoint UsersTracker::getRoomLimitMin()
{
    return mRoomRect.getTopLeft();
}

void UsersTracker::setRoomLimitMax(ofPoint& inRoomLimit)
{
    mRoomRect.set(mRoomRect.getTopLeft(), inRoomLimit);
}

ofPoint UsersTracker::getRoomLimitMax()
{
    return mRoomRect.getBottomRight();
}

void UsersTracker::setRoomLimit(const ofRectangle& inRoomLimit)
{
    mRoomRect = inRoomLimit;
}

ofRectangle UsersTracker::getRoomLimit()
{
    return mRoomRect;
}

//------------------------------------------------------------------------------
void UsersTracker::changeUsersInfluenceCohesion(float & inValue)
{
    mUsersCohesionInfluence = inValue;
}

void UsersTracker::changeUsersInfluenceAlignement(float & inValue)
{
    mUsersAlignmentInfluence = inValue;
}

void UsersTracker::changeUsersInfluenceSeparation(float & inValue)
{
    mUsersSeparationInfluence = inValue;
}

//------------------------------------------------------------------------------

float UsersTracker::getUsersInfluenceCohesion()
{
    return mUsersCohesionInfluence;
}

float UsersTracker::getUsersInfluenceAlignement()
{
    return mUsersAlignmentInfluence;
}

float UsersTracker::getUsersInfluenceSeparation()
{
    return mUsersSeparationInfluence;
}

//------------------------------------------------------------------------------
float UsersTracker::getUsersInfluenceCohesionMaxValue()
{
    return mUsersCohesionInfluenceMaxValue;
}

float UsersTracker::getUsersInfluenceAlignementMaxValue()
{
    return mUsersAlignmentInfluenceMaxValue;
}

float UsersTracker::getUsersInfluenceSeparationMaxValue()
{
    return mUsersSeparationInfluenceMaxValue;
}