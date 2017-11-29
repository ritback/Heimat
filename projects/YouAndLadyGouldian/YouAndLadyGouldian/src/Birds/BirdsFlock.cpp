#include "BirdsFlock.h"

BirdsFlock::BirdsFlock()
: HEFlock<Bird, HEBoxWorld>(200)
{
    setFlockMasses(2);

    mNumActiveBoids = 50;
}

BirdsFlock::~BirdsFlock()
{
    
}
