#include "FlockParametersGui.h"

#include "ofApp.h"
#include "BirdsFlock.h"
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
    
    ofPoint worldLimitMin = boxWorld->getWorldLimitMin();
    ofPoint worldLimitMax = boxWorld->getWorldLimitMax();
    ofPoint worldLimitDistanceMin = boxWorld->getWorldLimitDistanceMin();
    ofPoint worldLimitDistanceMax = boxWorld->getWorldLimitDistanceMax();
    
    mPanel.setup("Flock Panel");
    
    mPanel.add(mFlockRenderWorld.set("Render World Limits", false));
    
    ofParameterGroup worldLimit;
    worldLimit.setName("World Limit");
    worldLimit.add(mFlockWorldLimitMinX.set("Min X", worldLimitMin.x, -1200, 0));
    worldLimit.add(mFlockWorldLimitMinY.set("Min Y", worldLimitMin.y, -1200, 0));
    worldLimit.add(mFlockWorldLimitMaxX.set("Max X", worldLimitMax.x, 0, 1200));
    worldLimit.add(mFlockWorldLimitMaxY.set("Max Y", worldLimitMax.y, 0, 1200));
    mPanel.add(worldLimit);
    
    ofParameterGroup worldLimitDistance;
    worldLimitDistance.setName("World Limit Distance");
    worldLimitDistance.add(mFlockWorldLimitDistanceMinX.set("Min X", worldLimitDistanceMin.x, -1200, 0));
    worldLimitDistance.add(mFlockWorldLimitDistanceMinY.set("Min Y", worldLimitDistanceMin.y, -1200, 0));
    worldLimitDistance.add(mFlockWorldLimitDistanceMaxX.set("Max X", worldLimitDistanceMax.x, 0, 1200));
    worldLimitDistance.add(mFlockWorldLimitDistanceMaxY.set("Max Y", worldLimitDistanceMax.y, 0, 1200));
    mPanel.add(worldLimitDistance);
    
}

void FlockParametersGui::launchGui()
{
    mFlockWorldLimitMinX.addListener(this, &FlockParametersGui::resizeFlockWorld);
    mFlockWorldLimitMinY.addListener(this, &FlockParametersGui::resizeFlockWorld);
    mFlockWorldLimitMaxX.addListener(this, &FlockParametersGui::resizeFlockWorld);
    mFlockWorldLimitMaxY.addListener(this, &FlockParametersGui::resizeFlockWorld);
    
    mFlockWorldLimitDistanceMinX.addListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mFlockWorldLimitDistanceMinY.addListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mFlockWorldLimitDistanceMaxX.addListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mFlockWorldLimitDistanceMaxY.addListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    
}

void FlockParametersGui::removeGui()
{
    mFlockWorldLimitMinX.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    mFlockWorldLimitMinY.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    mFlockWorldLimitMaxX.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    mFlockWorldLimitMaxY.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    
    
    mFlockWorldLimitDistanceMinX.removeListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mFlockWorldLimitDistanceMinY.removeListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mFlockWorldLimitDistanceMaxX.removeListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    mFlockWorldLimitDistanceMaxY.removeListener(this, &FlockParametersGui::resizeFlockWorldDistance);
    
    
}

//------------------------------------------------------------------------------
void FlockParametersGui::renderGui()
{
    mPanel.draw();
}


//------------------------------------------------------------------------------
void FlockParametersGui::resizeFlockWorld(float & inLimit)
{
    ofPoint worldLimitMin(mFlockWorldLimitMinX, mFlockWorldLimitMinY);
    ofPoint worldLimitMax(mFlockWorldLimitMaxX, mFlockWorldLimitMaxY);
    
    BirdsFlock* flock = mApp->getFlock();
    HEBoxWorld* boxWorld = flock->getWorld();
    
    boxWorld->setWorldLimitMin(worldLimitMin);
    boxWorld->setWorldLimitMax(worldLimitMax);
}

//------------------------------------------------------------------------------
void FlockParametersGui::resizeFlockWorldDistance(float & inLimit)
{
    ofPoint worldLimitMin(mFlockWorldLimitDistanceMinX, mFlockWorldLimitDistanceMinY);
    ofPoint worldLimitMax(mFlockWorldLimitDistanceMaxX, mFlockWorldLimitDistanceMaxY);
    
    BirdsFlock* flock = mApp->getFlock();
    HEBoxWorld* boxWorld = flock->getWorld();
    
    boxWorld->setWorldLimitDistanceMin(worldLimitMin);
    boxWorld->setWorldLimitDistanceMax(worldLimitMax);
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



