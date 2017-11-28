#include "HE_Flock.h"

template<class BoidType, class WorldType>
HEFlock<BoidType, WorldType>::HEFlock(int inNumBoid)
    : mNumActiveBoids(inNumBoid)
{
    for(int i = 0; i < inNumBoid; ++i)
    {
        mBoids.push_back(new BoidType(ofPoint(ofRandom(-300, 300),
                                              ofRandom(-300, 300))));
    }
}

template<class BoidType, class WorldType>
HEFlock<BoidType, WorldType>::~HEFlock()
{
    for (BoidsIt it = mBoids.begin();
         it != mBoids.end();
         ++it)
    {
        delete (*it);
    }
}

// -----------------------------------------------------------------------------
template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::update()
{
    int index = 0;
    for (BoidsIt it = mBoids.begin(); it != mBoids.end(); ++it, ++index)
    {
        if (index > mNumActiveBoids) break;
        
        int index2 = index + 1;
        for (BoidsIt otherIt = it + 1; otherIt != mBoids.end(); ++otherIt, ++index2)
        {
            if (index2 >= mNumActiveBoids) break;
            
            float sqrDist = ((*it)->getPos()).squareDistance((*otherIt)->getPos());
            
            if (sqrDist > 0)
            {
                (*it)->otherBoidFlockingForce((*otherIt), sqrDist);
                (*otherIt)->otherBoidFlockingForce((*it), sqrDist);
            }
        }
        
        (*it)->applyFlockingForces();
        
        // World force
        applyWorldForce((*it));
        
        // other force
        (*it)->applyForce(mResultingExternalForce);
        mResultingExternalForce = ofPoint(0, 0);
        
        // Other updates
        (*it)->update();
    }

}

template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::render()
{
    int index = 0;
    for (BoidsIt it = mBoids.begin(); it != mBoids.end(); ++it, ++index)
    {
        if (index > mNumActiveBoids) break;
        
        (*it)->render();
    }
}

// -----------------------------------------------------------------------------
template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::addBoid(const ofPoint &inPos)
{
    mBoids.push_back(new BoidType(inPos));
}

template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::addBoid(BoidType* inBoid)
{
    mBoids.push_back(inBoid);
}

// -----------------------------------------------------------------------------
template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::renderWorld()
{
    mWorld.render();
}

// -----------------------------------------------------------------------------

template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::applyForceToBoids(const ofPoint& inForce)
{
    mResultingExternalForce += inForce;
}

template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::applyForceToBoidsFromPosition(const ofPoint& inFromPosition,
                                                                 float inMag,
                                                                 float inRange,
                                                                 float inViscosity)
{
    int index = 0;
    for(BoidsIt it = mBoids.begin(); it != mBoids.end(); ++it, ++index)
    {
        if(index > mNumActiveBoids) break;

        (*it)->applyForceFromPosition(inFromPosition,
                                      inMag,
                                      inRange,
                                      inViscosity);
    }
}

template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::applyLinearForceToBoidsFromPosition(const ofPoint& inFromPosition,
                                                                 float inMag,
                                                                 float inRange)
{
    int index = 0;
    for(BoidsIt it = mBoids.begin(); it != mBoids.end(); ++it, ++index)
    {
        if(index > mNumActiveBoids) break;

        (*it)->applyLinearForceFromPosition(inFromPosition,
                                      inMag,
                                      inRange);
    }
}

template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::applyInverselyProportionalToDistanceForceToBoidsFromPosition(const ofPoint& inFromPosition,
                                                                 float inMag,
                                                                 float inRange)
{
    int index = 0;
    for(BoidsIt it = mBoids.begin(); it != mBoids.end(); ++it, ++index)
    {
        if(index > mNumActiveBoids) break;

        (*it)->applyInverselyProportionalToDistanceForceFromPosition(inFromPosition,
                                      inMag,
                                      inRange);
    }
}

template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::applyExternalFlockForcesToBoids(ofPoint* inFromPosition,
                                                                 ofPoint* inVelocity,
                                                                 const int& inNumExternalBoid,
                                                                 const HEFlockRules& inRulesWeight,
                                                                 const float& inRange)
{
    int index = 0;
    for (BoidsIt it = mBoids.begin(); it != mBoids.end(); ++it, ++index)
    {
        if (index > mNumActiveBoids) break;
        
        for (int i = 0; i < inNumExternalBoid; i++)
        {
            float sqrDist = (inFromPosition[i]).squareDistance((*it)->getPos());
            if (sqrDist < inRange*inRange)
            {
                ofPoint forceDir = (inFromPosition[i]) - (*it)->getPos();
                forceDir.normalize();
                ofPoint alignementForce = (inVelocity[i]);
                alignementForce.normalize();
                
                
                (*it)->applyForce(forceDir * inRulesWeight.mCohesion);
                (*it)->applyForce(forceDir * inRulesWeight.mSeparation);
                (*it)->applyForce(alignementForce * inRulesWeight.mAlignement);
                
            }
        }
    }
}


// -----------------------------------------------------------------------------
template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::setFlockRules(const HEFlockRules& inValue)
{
    for (BoidsIt it = mBoids.begin();
         it != mBoids.end();
         ++it)
    {
        (*it)->setRulesWeight(inValue);
    }
}

template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::setFlockMass(const float& inValue)
{
    for (BoidsIt it = mBoids.begin();
         it != mBoids.end();
         ++it)
    {
        (*it)->setMass(inValue);
    }
}

// -----------------------------------------------------------------------------
template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::setNumActiveBoids(const int& inNumBoid)
{
    mNumActiveBoids = inNumBoid;
}

// -----------------------------------------------------------------------------
template<class BoidType, class WorldType>
WorldType* HEFlock<BoidType, WorldType>::getWorld()
{
    return &mWorld;
}

// -----------------------------------------------------------------------------

template<class BoidType, class WorldType>
void HEFlock<BoidType, WorldType>::applyWorldForce(BoidType* inBoid)
{
    mWorld.applyWorldForce(inBoid);
}

