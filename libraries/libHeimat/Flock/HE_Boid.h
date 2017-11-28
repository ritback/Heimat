#pragma once

#include "ofMain.h"
#include "HE_MassParticle.h"
#include "HE_FlockRules.h"


class HEBoid: public HEMassParticle
{
public:
    HEBoid(const ofPoint& inPos);
    virtual ~HEBoid();
    
public:
    virtual void update();
    virtual void render();
    
public: // called by the flock
    void otherBoidFlockingForce(HEBoid* inBoid,
                                float inBoidSqrDistance);
    void applyFlockingForces();
    
public: // external force to a boid
    void applyForceFromPosition(const ofPoint& inFromPosition,
                                float inMag,
                                float inRange,
                                float inViscosity = 0);
    void applyLinearForceFromPosition(const ofPoint& inFromPosition,
                                      float inMag,
                                      float inRange);
    void applyInverselyProportionalToDistanceForceFromPosition(
        const ofPoint& inFromPosition,
        float inMag,
        float inRange);
    
public:
    void setInfluenceWeight(const HEFlockRules& inValue);
    HEFlockRules getInfluenceWeight();
    void setRulesWeight(const HEFlockRules& inValue);
    HEFlockRules getRulesWeight();
    
protected:
    virtual void otherFlockingInteraction(HEBoid* inBoid,
                                          float inBoidSqrDistance); // want to set another force from the boids...
    virtual void applyOtherFlockingInteraction(); // want to set another stacking force and apply it at last ?
    
protected:
    float mMaxSteering;
    HEFlockRules mInfluenceWeight; // how much do I influence the others
    HEFlockRules mRulesSqrDistance; // how far do I receive influence from the others
    HEFlockRules mRulesWeight; // how much do I get influence by the others
 
private: // use for forces computations!
    HEFlockRules mWeightNeighborsInRange = HEFlockRules();
    ofPoint mResultingCohesionForce = ofPoint(0, 0, 0);
    ofPoint mResultingSeparationForce = ofPoint(0, 0, 0);
    ofPoint mResultingAlignmentForce = ofPoint(0, 0, 0);
};

