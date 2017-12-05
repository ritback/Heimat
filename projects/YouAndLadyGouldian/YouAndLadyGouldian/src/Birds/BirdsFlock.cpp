#include "BirdsFlock.h"

BirdsFlock::BirdsFlock()
: HEFlock<Bird, HEBoxWorld>(300)
{
    setFlockMasses(2.2);

    mNumActiveBoids = 150;
}

BirdsFlock::~BirdsFlock()
{
    
}

// -----------------------------------------------------------------------------
void BirdsFlock::reduceSpeedOfBirdsInDistance(const ofPoint& inFromPosition,
                                              float inReduceSpeedFactor,
                                              float inRange)
{
    int index = 0;
    for (BoidsIt it = mBoids.begin(); it != mBoids.end(); ++it, ++index)
    {
        if (index >= mNumActiveBoids) break;

        (*it)->reduceSpeedInDistance(inFromPosition, inReduceSpeedFactor, inRange);
    }
}


