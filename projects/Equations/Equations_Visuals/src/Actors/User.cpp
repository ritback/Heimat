#include "User.h"

#include "HEHelpers_Maths.h"

User::User(ofPoint inPoint)
	: Actor(inPoint)
{

    
}

User::~User()
{

}

//--------------------------------------------------------------
void User::render()
{
    ofPushMatrix();
    ofTranslate(mPos);
    float heading = 0;

    if (mVel.lengthSquared() > 20)
    {
        heading = heading2D(mVel);
        if (heading < -90 || heading > 90)
        {
            ofScale(-1, 1, 1);
        }
    }
    else
    {
        heading = -90;
    }
    ofRotate(45, 1, 0, 0);


    ofColor charColor(200);
    drawCharacter(charColor, heading);

    ofPopMatrix();


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

