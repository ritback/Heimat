#include "Flake.h"


Flake::Flake(const ofPoint& inPos, int inNumImageIndex)
: HEMassParticle(inPos)
, mFlakeImgIndex((int)ofRandom(0, inNumImageIndex + 0.999))
, mColor(ofRandom(255), ofRandom(255), ofRandom(255))
, mAimedColor(mColor)
, mWidth(ofRandom(0, 10) < 35 ? ofRandom(5, 30) : ofRandom(20, 30))
, mHeight(mWidth)
{
    
}

Flake::~Flake()
{
    
}

// -----------------------------------------------------------------------------
inline int signum(int i, int u)
{
    if(i < u) return +1;
    if(i == u) return 0;
    return -1;
}

void Flake::update()
{
    if(mColor != mAimedColor)
    {
        int sign = signum(mColor.r, mAimedColor.r);
        mColor.r += sign;

        sign = signum(mColor.g, mAimedColor.g);
        mColor.g += sign;

        sign = signum(mColor.b, mAimedColor.b);
        mColor.b += sign;
    }
}
