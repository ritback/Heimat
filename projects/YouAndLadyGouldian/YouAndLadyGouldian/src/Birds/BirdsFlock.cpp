#include "BirdsFlock.h"

BirdsFlock::BirdsFlock()
: HEFlock<Bird, HEBoxWorld>(50)
{
    setFlockMass(2);
}

BirdsFlock::~BirdsFlock()
{
    
}
