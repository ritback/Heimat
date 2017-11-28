#include "Bird.h"

#include "Feather.h"

Bird::Bird(const ofPoint& inPos)
: HEBoid(inPos)
, maxHeight(50)
, shape(ofPath())
, shape2(ofPath())
, shape3(ofPath())
, mNumPointsInTail(10)
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
    
}

// -----------------------------------------------------------------------------
void Bird::update()
{
    // may add new feathers if the accelration is too strong
    mayAddNewFeather();
    
    HEBoid::update();
    
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
void Bird::mayAddNewFeather()
{
    bool probability = false;
    
    float i = ofRandom (0,100);
    if (i<0.01)  // probability that a fether drop
        probability = true;
    
    // ADD feather at the end of the tail
    if (mAcc.lengthSquared() > 500/*0.030*/ || probability)
    {
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



