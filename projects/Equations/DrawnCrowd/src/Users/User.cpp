#include "User.h"

User::User(ofPoint inPoint)
	: DrawnPerson(inPoint)
{
    mCohesionInfluenceFactor = 0;
    mSeparationInfluenceFactor = 0;
    mAlignmentInfluenceFactor = 0;
    
}

User::~User()
{

}

//--------------------------------------------------------------
void User::render()
{
	//DrawnPerson::render();
    ofColor userColor(200);
	DrawnPerson::drawCharacter(userColor);
	
	/*
    ofPushStyle();
	ofSetColor(0, 255, 0, 100);
	ofDrawSphere(mPos, 10);
	ofPopStyle();
    */
}

inline float heading2D(ofPoint v)
{
    v.normalize();
    float angle = (float) -v.angle(ofPoint(1,0,0));
    angle = v.y>0 ? -angle : angle;
    return angle;
}

void User::updatePosition()
{
    if(mVel.lengthSquared() > 20)
    {
        mHeading = heading2D(mVel);
    }
    else
    {
        mHeading = -90;
    }

    mAcc = ofPoint(0, 0);
}


//--------------------------------------------------------------
void User::updatePositionAndVelocity(ofPoint inPos)
{
    mVel = inPos - mPos;
	mPos = inPos;
}


ofPoint User::getPos()
{
	return mPos;
}
