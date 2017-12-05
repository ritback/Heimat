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

    //numBirds = 10 + 2 * mNumSeed + 20 * numTree;



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
        mShouldUpdateNumBirds = true;
    }
}

