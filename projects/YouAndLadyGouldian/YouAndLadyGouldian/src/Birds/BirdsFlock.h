#pragma once

#include "ofMain.h"
#include "Flock/HE_Flock.h"
#include "Flock/HE_FlockingWorld.h"
#include "Bird.h"

class BirdsFlock: public HEFlock<Bird, HEBoxWorld>
{
public:
    BirdsFlock();
    virtual ~BirdsFlock();

};
