#include "HE_MassParticle.h"

HEMassParticle::HEMassParticle()
: mMass(1.0)
, mPos(0, 0, 0)
, mVel(0, 0, 0)
, mAcc(0, 0, 0)
{
    
}

HEMassParticle::HEMassParticle(const ofPoint& inPos, const ofPoint& inVel, const ofPoint& inAcc)
    : mMass(1.0)
    , mPos(inPos)
    , mVel(inVel)
    , mAcc(inAcc)
{

}

HEMassParticle::HEMassParticle(float inMass, const ofPoint& inPos, const ofPoint& inVel, const ofPoint& inAcc)
    : mMass(inMass)
    , mPos(inPos)
    , mVel(inVel)
    , mAcc(inAcc)
{

}

HEMassParticle::~HEMassParticle()
{
    
}

// -----------------------------------------------------------------------------
void HEMassParticle::applyForce(const ofPoint& inForce)
{
    mAcc += inForce / mMass;
}

// -----------------------------------------------------------------------------
void HEMassParticle::incrementPos()
{
    mVel += mAcc;
    mPos += mVel;
    
    mAcc = ofPoint(0, 0);
}

