#pragma once

#include "ofMain.h"

class HEMassParticle
{
public:
    HEMassParticle();
    HEMassParticle(const ofPoint& inPos,
                   const ofPoint& inVel = ofPoint(0, 0, 0),
                   const ofPoint& inAcc = ofPoint(0, 0, 0));
    HEMassParticle(float inMass,
                   const ofPoint& inPos = ofPoint(0, 0, 0),
                   const ofPoint& inVel = ofPoint(0, 0, 0),
                   const ofPoint& inAcc = ofPoint(0, 0, 0));
    virtual ~HEMassParticle();
    
public:
    void applyForce(const ofPoint& inForce);
    
public:
    virtual void incrementPos(); // update position upon the forces aquired, reset accell

public:
    void setMass(const float& inMass) { mMass = inMass; };
    void setPos(const ofPoint& inPos) { mPos = inPos; };

public:
    float getMass() const { return mMass; };
    ofPoint getPos() const { return mPos; };
    ofPoint getVel() const { return mVel; };
    ofPoint getAcc() const { return mAcc; };

protected:
    float mMass;
    ofPoint mPos;
    ofPoint mVel;
    ofPoint mAcc;
};



