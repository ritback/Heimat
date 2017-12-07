#include "ColonyManager.h"

#include "BirdsFlock.h"
#include "Forest.h"

ColonyManager::ColonyManager(BirdsFlock* inFlock, Forest * inForest)
    : mFlock(inFlock)
    , mForest(inForest)
    , mNumSeed(0)
    , mSmoothNumBirds(0)
    , mNextUpdateTime(0)
    , mUpdateNumBirdsWithWeb(true)
{
    ofRegisterURLNotification(this);
}

ColonyManager::~ColonyManager()
{
    ofUnregisterURLNotification(this);
}

//------------------------------------------------------------------------------
void ColonyManager::update()
{
    if(mNextUpdateTime < ofGetElapsedTimef())
    {
        updateURL();
        mNextUpdateTime = ofGetElapsedTimef() + 0.5;
    }
    
    if(mUpdateNumBirdsWithWeb)
    {
        setNumBirds();
    }
    else
    {
        mSmoothNumBirds = mFlock->getNumActiveBoids();
    }
}

//------------------------------------------------------------------------------
void ColonyManager::setNumBirds()
{
    int numBirds = mFlock->getNumActiveBoids();

    int aimedNumBirds = 3
                        + 2 * mNumSeed
                        + 20 * mForest->getNumTree();

    if(numBirds <= aimedNumBirds)
    {
        numBirds = aimedNumBirds;
        mSmoothNumBirds = numBirds;
    }
    else
    {
        mSmoothNumBirds -= 2.0 / 30.0; // at 30 frame per sec it'll take 2 seconds for 1 bird to disapear.
        numBirds = std::ceil(mSmoothNumBirds);
    }


    mFlock->setNumActiveBoids(numBirds);

}

//------------------------------------------------------------------------------

void ColonyManager::updateURL()
{
    // get food
    ofLoadURLAsync("https://youandladygouldian.com/birdparams/food", "GetNumSeed");

    // push number of birds
    std::stringstream sendNumBirds;
    sendNumBirds << "https://youandladygouldian.com/birdparams/birds/";
    sendNumBirds << mFlock->getNumActiveBoids();

    string str(sendNumBirds.str());

    ofLoadURLAsync(str, "PushNumBirds");
}

void ColonyManager::urlResponse(ofHttpResponse& inResponse)
{
    if(inResponse.status == 200 && inResponse.request.name == "GetNumSeed")
    {
        mNumSeed = atoi(inResponse.data.getData());
    }
}

//------------------------------------------------------------------------------
void ColonyManager::updateFlockWithWeb(bool inValue)
{
    mUpdateNumBirdsWithWeb = inValue;
}

bool ColonyManager::isFlockUpdatedWithWeb()
{
    return mUpdateNumBirdsWithWeb;
}