#include "FlockParametersGui.h"

#include "ofApp.h"
#include "BirdsFlock.h"
#include "ColonyManager.h"
#include "HE_FlockingWorld.h"


FlockParametersGui::FlockParametersGui(ofApp* inApp)
: mApp(inApp)
{
    
}

FlockParametersGui::~FlockParametersGui()
{
    
}

//------------------------------------------------------------------------------
void FlockParametersGui::initGui()
{
    BirdsFlock* flock = mApp->getFlock();
    HEBoxWorld* boxWorld = flock->getWorld();
    bool updateFlockWithWeb = (mApp->getColonyManager())->isFlockUpdatedWithWeb();

    int flockNumBoids = flock->getNumActiveBoids();
    float flockMasses = flock->getFlockMasses();
    HEFlockRules flockRules = flock->getFlockRules();

    ofPoint worldLimitMin = boxWorld->getWorldLimitMin();
    ofPoint worldLimitMax = boxWorld->getWorldLimitMax();
    ofPoint worldLimitDistanceMin = boxWorld->getWorldLimitDistanceMin();
    ofPoint worldLimitDistanceMax = boxWorld->getWorldLimitDistanceMax();

    float repulsion = boxWorld->getWorldRepulsionMag();


    
    mPanel.setup("Flock Panel");

    mPanel.add(mUpdateNumFlockWithWeb.set("Update Flock With Web", updateFlockWithWeb));
    mPanel.add(mNumBoids.set("NumBoids", flockNumBoids, 0, 300));
    mPanel.add(mBoidsMasses.set("Masses", flockMasses, 0, 5));

    ofParameterGroup flockRulesParam;
    flockRulesParam.setName("Flock Rules");
    flockRulesParam.add(mFlockRulesCohesion.set("Cohesion", flockRules.mCohesion, 0, 10));
    flockRulesParam.add(mFlockRulesSeparation.set("Separation", flockRules.mSeparation, 0, 10));
    flockRulesParam.add(mFlockRulesAlignement.set("Alignement", flockRules.mAlignement, 0, 10));
    mPanel.add(flockRulesParam);


    mPanel.add(mRenderWorld.set("Render World Limits", false));

    mPanel.add(mWorldLimitRepuslion.set("Repulsion", repulsion, 0, 20));

    ofParameterGroup worldLimit;
    worldLimit.setName("World Limit");
    worldLimit.add(mWorldLimitMinX.set("Min X", worldLimitMin.x, -1200, 0));
    worldLimit.add(mWorldLimitMinY.set("Min Y", worldLimitMin.y, -1200, 0));
    worldLimit.add(mWorldLimitMaxX.set("Max X", worldLimitMax.x, 0, 1200));
    worldLimit.add(mWorldLimitMaxY.set("Max Y", worldLimitMax.y, 0, 1200));
    mPanel.add(worldLimit);
    
    ofParameterGroup worldLimitDistance;
    worldLimitDistance.setName("World Limit Distance");
    worldLimitDistance.add(mWorldLimitDistanceMinX.set("Min X", worldLimitDistanceMin.x, -1200, 0));
    worldLimitDistance.add(mWorldLimitDistanceMinY.set("Min Y", worldLimitDistanceMin.y, -1200, 0));
    worldLimitDistance.add(mWorldLimitDistanceMaxX.set("Max X", worldLimitDistanceMax.x, 0, 1200));
    worldLimitDistance.add(mWorldLimitDistanceMaxY.set("Max Y", worldLimitDistanceMax.y, 0, 1200));
    mPanel.add(worldLimitDistance);

}

void FlockParametersGui::launchGui()
{

    BirdsFlock* flock = mApp->getFlock();
    HEBoxWorld* boxWorld = flock->getWorld();
    bool updateFlockWithWeb = (mApp->getColonyManager())->isFlockUpdatedWithWeb();

    mNumBoids = flock->getNumActiveBoids();
    mBoidsMasses = flock->getFlockMasses();

    mWorldLimitRepuslion = boxWorld->getWorldRepulsionMag();

    ofPoint worldLimitMin = boxWorld->getWorldLimitMin();
    ofPoint worldLimitMax = boxWorld->getWorldLimitMax();
    ofPoint worldLimitDistanceMin = boxWorld->getWorldLimitDistanceMin();
    ofPoint worldLimitDistanceMax = boxWorld->getWorldLimitDistanceMax();

    mWorldLimitMinX = worldLimitMin.x;
    mWorldLimitMinY = worldLimitMin.y;
    mWorldLimitMaxX = worldLimitMax.x;
    mWorldLimitMaxY = worldLimitMax.y;

    mWorldLimitDistanceMinX = worldLimitDistanceMin.x;
    mWorldLimitDistanceMinY = worldLimitDistanceMin.y;
    mWorldLimitDistanceMaxX = worldLimitDistanceMax.x;
    mWorldLimitDistanceMaxY = worldLimitDistanceMax.y;


    mUpdateNumFlockWithWeb.addListener(this, &FlockParametersGui::setUpdateFlockWithWeb);
    mNumBoids.addListener(this, &FlockParametersGui::setFlockNumBoids);
    mBoidsMasses.addListener(this, &FlockParametersGui::setFlockMasses);

    mFlockRulesCohesion.addListener(this, &FlockParametersGui::setFlockRules);
    mFlockRulesSeparation.addListener(this, &FlockParametersGui::setFlockRules);
    mFlockRulesAlignement.addListener(this, &FlockParametersGui::setFlockRules);

    mWorldLimitRepuslion.addListener(this, &FlockParametersGui::setWorldLimitRepulsion);

    mWorldLimitMinX.addListener(this, &FlockParametersGui::resizeFlockWorld);
    mWorldLimitMinY.addListener(this, &FlockParametersGui::resizeFlockWorld);
    mWorldLimitMaxX.addListener(this, &FlockParametersGui::resizeFlockWorld);
    mWorldLimitMaxY.addListener(this, &FlockParametersGui::resizeFlockWorld);

    mWorldLimitDistanceMinX.addListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mWorldLimitDistanceMinY.addListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mWorldLimitDistanceMaxX.addListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mWorldLimitDistanceMaxY.addListener(this, &FlockParametersGui::resizeFlockWorldDistance);


}

void FlockParametersGui::removeGui()
{

    mUpdateNumFlockWithWeb.removeListener(this, &FlockParametersGui::setUpdateFlockWithWeb);
    mNumBoids.removeListener(this, &FlockParametersGui::setFlockNumBoids);
    mBoidsMasses.removeListener(this, &FlockParametersGui::setFlockMasses);

    mFlockRulesCohesion.removeListener(this, &FlockParametersGui::setFlockRules);
    mFlockRulesSeparation.removeListener(this, &FlockParametersGui::setFlockRules);
    mFlockRulesAlignement.removeListener(this, &FlockParametersGui::setFlockRules);

    mWorldLimitRepuslion.removeListener(this, &FlockParametersGui::setWorldLimitRepulsion);

    mWorldLimitMinX.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    mWorldLimitMinY.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    mWorldLimitMaxX.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    mWorldLimitMaxY.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    
    mWorldLimitDistanceMinX.removeListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mWorldLimitDistanceMinY.removeListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mWorldLimitDistanceMaxX.removeListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mWorldLimitDistanceMaxY.removeListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    
    
}

//------------------------------------------------------------------------------
void FlockParametersGui::renderGui()
{
    mPanel.draw();
}

//------------------------------------------------------------------------------
void FlockParametersGui::saveParameters()
{
    mPanel.saveToFile("FlockSettings.xml");
}

void FlockParametersGui::loadParameters()
{
    mPanel.loadFromFile("FlockSettings.xml");
}


//------------------------------------------------------------------------------
void FlockParametersGui::setUpdateFlockWithWeb(bool & inValue)
{
    (mApp->getColonyManager())->updateFlockWithWeb(inValue);
}

void FlockParametersGui::setFlockNumBoids(float & inValue)
{
    BirdsFlock* flock = mApp->getFlock();
    int value = (int) inValue;
    if (mNumBoids != mNumBoids)
        mNumBoids = value;
    else
        flock->setNumActiveBoids(value);
}

void FlockParametersGui::setFlockMasses(float & inValue)
{
    BirdsFlock* flock = mApp->getFlock();
    flock->setFlockMasses(mBoidsMasses);
}

void FlockParametersGui::setFlockRules(float & inValue)
{
    BirdsFlock* flock = mApp->getFlock();
    HEFlockRules flockRules = flock->getFlockRules();
    flockRules.mCohesion = mFlockRulesCohesion;
    flockRules.mSeparation = mFlockRulesSeparation;
    flockRules.mAlignement = mFlockRulesAlignement;

    flock->setFlockRules(flockRules);
}

//------------------------------------------------------------------------------
void FlockParametersGui::setWorldLimitRepulsion(float & inLimit)
{
    BirdsFlock* flock = mApp->getFlock();
    HEBoxWorld* boxWorld = flock->getWorld();

    boxWorld->setWorldRepulsionMag(inLimit);
}

void FlockParametersGui::resizeFlockWorld(float & inLimit)
{
    ofPoint worldLimitMin(mWorldLimitMinX, mWorldLimitMinY);
    ofPoint worldLimitMax(mWorldLimitMaxX, mWorldLimitMaxY);
    
    BirdsFlock* flock = mApp->getFlock();
    HEBoxWorld* boxWorld = flock->getWorld();
    
    boxWorld->setWorldLimitMin(worldLimitMin);
    boxWorld->setWorldLimitMax(worldLimitMax);
}

void FlockParametersGui::resizeFlockWorldDistance(float & inLimit)
{
    ofPoint worldLimitMin(mWorldLimitDistanceMinX, mWorldLimitDistanceMinY);
    ofPoint worldLimitMax(mWorldLimitDistanceMaxX, mWorldLimitDistanceMaxY);
    
    BirdsFlock* flock = mApp->getFlock();
    HEBoxWorld* boxWorld = flock->getWorld();
    
    boxWorld->setWorldLimitDistanceMin(worldLimitMin);
    boxWorld->setWorldLimitDistanceMax(worldLimitMax);
}


