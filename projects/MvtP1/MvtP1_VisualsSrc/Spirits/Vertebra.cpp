#include "Vertebra.h"

#include <algorithm>

Vertebra::Vertebra(const ofPoint& inPos,
                   Vertebra* inFrontVertebra, Vertebra* inBackVertebra)
    : HEMassParticle(inPos)
    , mFrontVertebra(inFrontVertebra)
    , mBackVertebra(inBackVertebra)
    , mRelativePosToFront(ofPoint(0, 0))
    , mSpringLenght(30)
    , mSpringStrength(0.8)
    , mSpringDamping(0.7)
{
    if (mFrontVertebra)
    {
        mFrontVertebra->mBackVertebra = this;
    }
}

Vertebra::~Vertebra()
{
    
}


// -----------------------------------------------------------------------------
void Vertebra::applySpineForces()
{
    if (mFrontVertebra) // apply spring force on front and self.
    {
        {
            float k = mSpringStrength;
            float c = mSpringDamping; // damping
            
            ofPoint springForceDir = -mRelativePosToFront;
            float springCurrentLenght = springForceDir.length();
            springForceDir /= springCurrentLenght;
            
            float stretching = (springCurrentLenght - mSpringLenght);
            
            // spring force
            float spineForceMag = -k*stretching ;
            ofPoint springForce = spineForceMag * springForceDir;
            
            // spring friction force
            float projectedVelocity = springForceDir.dot(mVel);
            ofPoint frictionForce = - c * projectedVelocity * springForceDir;
            springForce += frictionForce;
            
            applyForce(springForce);
        }
        
        
        if (mFrontVertebra->mFrontVertebra) // restriction on cone.
        {
            ofPoint frontVertebraDir = mFrontVertebra->mRelativePosToFront;
            frontVertebraDir.normalize();
            
            ofPoint normalToFrontDir = frontVertebraDir.getCrossed(ofPoint(0, 0, 1));
            
            float distanceToFrontVelDir = mRelativePosToFront.dot(normalToFrontDir);
            if (abs(distanceToFrontVelDir) > 30)
            {
                ofPoint spineForce = distanceToFrontVelDir*normalToFrontDir / 10;
            
                float projectedVelocity = normalToFrontDir.dot(mVel);
                ofPoint frictionForce = - 0.3 * projectedVelocity * normalToFrontDir;
                
                spineForce += frictionForce;

                applyForce(spineForce);
                
            }
        }
    }
}


void Vertebra::updatePos()
{
    HEMassParticle::updatePos();
    
    if (mFrontVertebra)
    {
        // restrict Position from being waaaaaaaaayyy too far
        ofPoint relativePos = mFrontVertebra->mPos - mPos;
        if (relativePos.lengthSquared() > 100000)
        {
            relativePos.normalize();
            mPos = mFrontVertebra->mPos + 100 * relativePos;
        }
        
        // update relative pos
        mRelativePosToFront = mFrontVertebra->mPos - mPos;
        
    }
}

// -----------------------------------------------------------------------------
void Vertebra::connectFrontTo(Vertebra* inVertebra)
{
    mFrontVertebra = inVertebra;
}

void Vertebra::connectBackTo(Vertebra* inVertebra)
{
    mBackVertebra = inVertebra;
}

void Vertebra::disconnectBackVertebra()
{
    mBackVertebra = 0;
}

void Vertebra::disconnectFrontVertebra()
{
    mFrontVertebra = 0;
}
