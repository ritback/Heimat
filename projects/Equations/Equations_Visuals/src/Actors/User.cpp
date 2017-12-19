#include "User.h"

User::User(ofPoint inPoint)
	: Actor(inPoint)
{
    //mCohesionInfluenceFactor = 0;
    //mSeparationInfluenceFactor = 0;
    //mAlignmentInfluenceFactor = 0;
    
}

User::~User()
{

}

//--------------------------------------------------------------
void User::update()
{
    Actor::update();
    if (mVel.lengthSquared() > 20)
    {
        //mHeading = heading2D(mVel);
    }
    else
    {
        //mHeading = -90;
    }

}


void User::render()
{
	//DrawnPerson::render();
    ofColor userColor(200);
	Actor::drawCharacter(userColor);
	
	/*
    ofPushStyle();
	ofSetColor(0, 255, 0, 100);
	ofDrawSphere(mPos, 10);
	ofPopStyle();
    */
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
