#include "HE_Boid.h"
#include "HEHelpers_Maths.h"

const float rulesDistance = 50;


HEBoid::HEBoid(const ofPoint& inPos)
    : HEMassParticle(inPos)
    , mMaxSteering(100000.0)
    , mInfluenceWeight(1, 1, 1)
    , mRulesSqrDistance(rulesDistance*rulesDistance,
                        rulesDistance*rulesDistance * 4/5,
                        rulesDistance*rulesDistance)
    , mRulesWeight(0.7, 3.14, 7.3)
{

}

HEBoid::~HEBoid()
{
    
}

// -----------------------------------------------------------------------------
void HEBoid::update()
{
    incrementPos();
}

void HEBoid::render()
{
    ofPushStyle();
    
    ofPushMatrix();
    ofTranslate(mPos.x, mPos.y);
    
    ofSetColor(255, 0, 0);
    ofDrawCircle(0, 0, 5);
    
    float alpha = 50;
    ofNoFill();
    ofSetColor(255, 0, 0, alpha);
    ofDrawCircle(0, 0, sqrt(mRulesSqrDistance.mCohesion));
    ofSetColor(0, 255, 0, alpha);
    ofDrawCircle(0, 0, sqrt(mRulesSqrDistance.mSeparation));
    ofSetColor(0, 0, 255, alpha);
    ofDrawCircle(0, 0, sqrt(mRulesSqrDistance.mAlignement));
    
    
    ofRotate(heading2D(mVel));
    ofSetColor(0, 0, 0);
    ofDrawLine(0, 0, 10, 0);
    
    
    ofPopMatrix();
    ofPopStyle();
}

// -----------------------------------------------------------------------------
void HEBoid::otherBoidFlockingForce(HEBoid* inBoid,
                                    float inBoidSqrDistance)
{
    if(inBoidSqrDistance < mRulesSqrDistance.mCohesion ||
       inBoidSqrDistance < mRulesSqrDistance.mSeparation ||
       inBoidSqrDistance < mRulesSqrDistance.mAlignement)
    {
        ofPoint dir = (inBoid->getPos() - mPos).normalize();
        float dist = sqrt(inBoidSqrDistance);
        
        if(inBoidSqrDistance < mRulesSqrDistance.mCohesion)
        {
            float weight = (sqrt(mRulesSqrDistance.mCohesion) / dist - 1) * inBoid->mInfluenceWeight.mCohesion;
            ofPoint force = dir * weight;
            
            mWeightNeighborsInRange.mCohesion += weight;
            mResultingCohesionForce += force;
        }
        
        if(inBoidSqrDistance < mRulesSqrDistance.mSeparation)
        {
            float weight = (sqrt(mRulesSqrDistance.mSeparation) / dist - 1) * inBoid->mInfluenceWeight.mSeparation;
            ofPoint force = -dir * weight;
            
            mWeightNeighborsInRange.mSeparation += weight;
            mResultingSeparationForce += force;
        }
        
        if(inBoidSqrDistance < mRulesSqrDistance.mAlignement)
        {
            ofPoint vel = inBoid->getVel();
            vel.normalize();
            float weight = (sqrt(mRulesSqrDistance.mAlignement) / dist - 1) * inBoid->mInfluenceWeight.mAlignement;
            vel *= weight;
            
            mWeightNeighborsInRange.mAlignement += weight;
            mResultingAlignmentForce += vel;
        }
    }
    
    otherFlockingInteraction(inBoid, inBoidSqrDistance);
}

// -----------------------------------------------------------------------------
void HEBoid::applyFlockingForces()
{
    if (mWeightNeighborsInRange.mCohesion > 0
        && mResultingCohesionForce != ofPoint(0, 0))
    {
        // Global Cohesion Force
        // steering to the barycenter of all Neighborss.
        mResultingCohesionForce /= mWeightNeighborsInRange.mCohesion;
        

        mResultingCohesionForce -= mVel;
        

        mResultingCohesionForce *= mRulesWeight.mCohesion;
        
        mResultingCohesionForce.limit(mMaxSteering);
        applyForce(mResultingCohesionForce);
    }
    
    if (mWeightNeighborsInRange.mSeparation > 0
        && mResultingSeparationForce != ofPoint(0, 0))
    {
        // Global Separation Force
        mResultingSeparationForce /= mWeightNeighborsInRange.mSeparation;
        

        mResultingCohesionForce -= mVel;



        mResultingSeparationForce *= mRulesWeight.mSeparation;
        
        mResultingSeparationForce.limit(mMaxSteering);
        applyForce(mResultingSeparationForce);
    }
    
    if (mWeightNeighborsInRange.mAlignement > 0
        && mResultingAlignmentForce != ofPoint(0, 0))
    {
        // Global Alignment Force
        mResultingAlignmentForce /= mWeightNeighborsInRange.mAlignement;
        
        //mResultingAlignmentForce -= mVel;
        mResultingAlignmentForce *= mRulesWeight.mAlignement;
        
        mResultingAlignmentForce.limit(mMaxSteering);
        applyForce(mResultingAlignmentForce);
    }
    
    applyOtherFlockingInteraction();
    
    // whatever happens, free the forces
    mWeightNeighborsInRange = HEFlockRules(0, 0, 0);
    mResultingCohesionForce = ofPoint(0, 0);
    mResultingSeparationForce = ofPoint(0, 0);
    mResultingAlignmentForce = ofPoint(0, 0);
    
    // limit speed thanks to viscosity
    if (mVel.lengthSquared() > 20)
    {
        applyForce(- 0.05 * mVel);
    }
}


// -----------------------------------------------------------------------------
void HEBoid::applyForceFromPosition(const ofPoint& inFromPosition,
                                    float inMag,
                                    float inRange,
                                    float inViscosity)
{
    float sqrDist = inFromPosition.squareDistance(mPos);
    if(sqrDist < inRange*inRange)
    {
        ofPoint force = inFromPosition - mPos;
        force.normalize();
        force *= inMag;
        applyForce(force);

        if(inViscosity > 0) // apply the optional viscosity
        {
            applyForce(-inViscosity * mVel);
        }
    }
}

void HEBoid::applyLinearForceFromPosition(const ofPoint& inFromPosition,
                                          float inMag,
                                          float inRange)
{
    float sqrDist = inFromPosition.squareDistance(mPos);
    if(sqrDist < inRange*inRange)
    {
        ofPoint force = inFromPosition - mPos;
        force.normalize();
        force *= (1 / inRange) * (inRange - sqrt(sqrDist));

        force *= inMag;
        applyForce(force);
    }
}

void HEBoid::applyInverselyProportionalToDistanceForceFromPosition(
    const ofPoint& inFromPosition,
    float inMag,
    float inRange)
{
    float sqrDist = inFromPosition.squareDistance(mPos);
    if(sqrDist < inRange*inRange)
    {
        ofPoint force = inFromPosition - mPos;
        force.normalize();
        force *= (inRange / sqrt(sqrDist) - 1);

        force *= inMag;
        applyForce(force);
    }
}

// -----------------------------------------------------------------------------

void HEBoid::setInfluenceWeight(const HEFlockRules& inValue)
{
    mInfluenceWeight = inValue;
}

HEFlockRules HEBoid::getInfluenceWeight()
{
    return mInfluenceWeight;
}

void HEBoid::setRulesWeight(const HEFlockRules& inValue)
{
    mRulesWeight = inValue;
}

HEFlockRules HEBoid::getRulesWeight()
{
    return mRulesWeight;
}

// -----------------------------------------------------------------------------
void HEBoid::otherFlockingInteraction(HEBoid* inBoid,
                                      float inBoidSqrDistance)
{
    
}

void HEBoid::applyOtherFlockingInteraction()
{
    
}
