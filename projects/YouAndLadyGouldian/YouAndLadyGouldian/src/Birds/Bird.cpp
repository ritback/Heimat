#include "Bird.h"

#include "Feather.h"

Bird::Bird(const ofPoint& inPos)
: HEBoid(inPos)
, maxHeight(75)
, shape(ofPath())
, shape2(ofPath())
, shape3(ofPath())
, mNumPointsInTail(10)
, mReduceSpeedFactor(0)
{
    // tail
    for (int i = 0; i < mNumPointsInTail; i++)
    {
        HEMassParticle * newTailPart = new HEMassParticle(mPos);
        mTail.push_back(newTailPart);
    }
    
    for (int i = 0; i < 5; i++)
    {
        Feather * newFeather = new Feather();
        mFeathers.push_back(newFeather);
    }
    
    // shapes and rendering
    bodyHeight = ofRandom(maxHeight/2, maxHeight);
    bodyWidth = ofRandom(bodyHeight*3/16, bodyHeight/4);
    createShape();
    
    colorFish = ofColor (ofRandom(200,255), ofRandom(60,255), ofRandom(80,120));
    currentColor = ofColor(colorFish);
    colorPhase = 0;
    colorPhaseInc = ofRandom(0.5);
    colorPhaseAmp = 50;
}

Bird::~Bird()
{
    for (FeathersIt it = mFeathers.begin(); it < mFeathers.end(); ++it)
    {
        delete (*it);
    }

    for (TailIt it = mTail.begin(); it < mTail.end(); ++it)
    {
        delete (*it);
    }
}

// -----------------------------------------------------------------------------
void Bird::update()
{
    // may add new feathers if the accelration is too strong
    mayAddNewFeather();
    
    // handle speedReduction
    //HEBoid::update();
    mVel += mAcc;
    mVel *= 1 - mReduceSpeedFactor;
    mPos += mVel;

    mAcc = ofPoint(0, 0);
    mReduceSpeedFactor = 0;
    // end speed reduction


    updateTail();
    
    for (FeathersIt it = mFeathers.begin(); it < mFeathers.end(); ++it)
    {
        (*it)->update();
    }
    
}

void Bird::render()
{
    renderBird();
    
    for (FeathersIt it = mFeathers.begin(); it < mFeathers.end(); ++it)
    {
        (*it)->render();
    }
}

// -----------------------------------------------------------------------------
void Bird::reduceSpeedInDistance(const ofPoint& inFromPosition,
                                             float inReduceSpeedFactor,
                                             float inRange)
{
    float sqrDist = inFromPosition.squareDistance(mPos);
    if (sqrDist < inRange*inRange)
    {
        mReduceSpeedFactor = inReduceSpeedFactor;
    }
}

// -----------------------------------------------------------------------------
void Bird::mayAddNewFeather()
{
    float probability = 0.01; // probability that a fether drop
    if(mAcc.lengthSquared() > 150)
    {
        probability = 5;
    }

    float random = ofRandom(0, 100);
    
    if (random < probability)
    {
        // ADD feather at the end of the tail
        FeathersIt it = mFeathers.begin();
        while(it != mFeathers.end())
        {
            if (!(*it)->mIsVisible)
            {
                (*it)->activate((mTail.back())->getPos(),
                                mVel);
                break;
            }
            ++it;
        }
    }
    
    
}

// -----------------------------------------------------------------------------
void Bird::updateTail()
{
    ofPoint previousLocation = (mTail.front())->getPos();
    if (mPos.squareDistance(previousLocation) > 10)
    {
        (mTail.back())->setPos(mPos); // set new data
        mTail.push_front(mTail.back()); // place the back to the top
        mTail.pop_back(); // pop the back
    }
}



