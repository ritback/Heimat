#include "BirdsFlock.h"

BirdsFlock::BirdsFlock()
: HEFlock<Bird, HEBoxWorld>(200)
{
    setFlockMasses(2.2);

    mNumActiveBoids = 150;
}

BirdsFlock::~BirdsFlock()
{
    
}
