#include "Flake.h"


Flake::Flake(const ofPoint& inPos, int inNumImageIndex)
: HEMassParticle(inPos)
, mFlakeImgIndex((int)ofRandom(0, inNumImageIndex + 0.999))
, mColor(ofRandom(255), ofRandom(255), ofRandom(255))
, mWidth(ofRandom(0, 10) < 35 ? ofRandom(5, 30) : ofRandom(20, 30))
, mHeight(mWidth)
{
    
}

Flake::~Flake()
{
    
}

// -----------------------------------------------------------------------------
void Flake::update()
{
    
}
