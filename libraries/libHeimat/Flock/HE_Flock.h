#pragma once

#include <vector>
#include "ofMain.h"

#include "HE_FlockRules.h"

template<class BoidType, class WorldType>
class HEFlock
{
public:
    HEFlock(int inNumBoid = 100);
    ~HEFlock();
    
public:
    void update();
    void render();
    
    void renderWorld();
    
public:
    void addBoid(const ofPoint &inPos);
	void addBoid(BoidType* inBoid);

public:
    void applyForceToBoids(const ofPoint& inForce);
    void applyForceToBoidsFromPosition(const ofPoint& inFromPosition,
                                       float inMag,
                                       float inRange,
                                       float inViscosity = 0);
    void applyLinearForceToBoidsFromPosition(const ofPoint& inFromPosition,
                                             float inMag,
                                             float inRange);
    void applyInverselyProportionalToDistanceForceToBoidsFromPosition(
        const ofPoint& inFromPosition,
        float inMag,
        float inRange);
    void applyExternalFlockForcesToBoids(ofPoint* inFromPosition,
                                         ofPoint* inVelocity,
                                         const int& inNumExternalBoid,
                                         const HEFlockRules& inRulesWeight,
                                         const float& inRange);

public:
    void setNumActiveBoids(const int& inNumBoid); // max is the number of boids created first
    int getNumActiveBoids(); 

public:
    void setFlockRules(const HEFlockRules& inValue);
    HEFlockRules getFlockRules();
    void setFlockMasses(const float& inValue);
    float getFlockMasses();
    
    
public:
    WorldType* getWorld();
    
private:
    void applyWorldForce(BoidType* inBoid);
    
protected:
    typedef std::vector<BoidType*> Boids;
    typedef typename Boids::iterator BoidsIt;
    Boids mBoids;
    
protected:
    WorldType mWorld;
    
protected:
    ofPoint mResultingExternalForce;
    
protected:
    int mNumActiveBoids;
    
  
};

#include "HE_Flock.hpp"


/* TO DO if highly motivated
* => a pool for external force inversely proportional to distance
protected:
struct
{
ofPoint mFromPos;
float mRange;
bool bValid;
} InverseDistanceForce;

typedef std::vector<InverseDistanceForce> InverseDistanceForces;
typedef typename InverseDistanceForces::iterator InverseDistanceForcesIt;

InverseDistanceForces mInverseDistanceForces;
*/

