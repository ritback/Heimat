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
