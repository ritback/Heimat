#include "ColonyManager.h"

ColonyManager::ColonyManager(BirdsFlock* inFlock)
    : mFlock(inFlock)
    , mNextUpdateTime(0)
    , mNumSeed(0)
    , mShouldUpdateNumBirds(true)
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
        mNextUpdateTime = ofGetElapsedTimef() + 1;
    }
    
    if(mShouldUpdateNumBirds)
    {
        //setNumBirds();
        mShouldUpdateNumBirds = false;
    }
}

//------------------------------------------------------------------------------
void ColonyManager::setNumBirds()
{
    int numBirds = 0;





    mFlock->setNumActiveBoids(numBirds);

}

//------------------------------------------------------------------------------

void ColonyManager::updateURL()
{
    // get food
    ofLoadURLAsync("https://youandladygouldian.com/birdparams/food", "GET");

    // push number of birds
    std::stringstream sendNumBirds;
    sendNumBirds << "https://youandladygouldian.com/birdparams/birds/";
    sendNumBirds << mFlock->getNumActiveBoids();

    ofLoadURLAsync(sendNumBirds.str(), "PUT");
}

void ColonyManager::urlResponse(ofHttpResponse& inResponse)
{
    if(inResponse.status == 200 && inResponse.request.name == "GET")
    {
        mNumSeed = atoi(inResponse.data.getData());
        mShouldUpdateNumBirds = true;
    }
}

