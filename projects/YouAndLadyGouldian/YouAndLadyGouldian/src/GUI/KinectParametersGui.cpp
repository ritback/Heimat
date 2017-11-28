#include "KinectParametersGui.h"

#include "ofApp.h"

KinectParametersGui::KinectParametersGui(ofApp* inApp)
: mApp(inApp)
{
    
}

KinectParametersGui::~KinectParametersGui()
{
    
}

//------------------------------------------------------------------------------
void KinectParametersGui::initGui()
{
    BirdsFlock* flock = mApp->getFlock();
    HEBoxWorld* boxWorld = flock->getWorld();
    
    mPanel.setup("Kinect Panel");
    
    
    ofParameterGroup silhouette;
    silhouette.setName("Silhouette");
    silhouette.add(mSilhouetteRenderNormal.set("Min X", false));
    silhouette.add(mSilhouetteRenderBackground.set("Min Y", false));
    mPanel.add(silhouette);
    
}

void KinectParametersGui::launchGui()
{
    /*
    mFlockWorldLimitMinX.addListener(this, &FlockParametersGui::resizeFlockWorld);
    mFlockWorldLimitMinY.addListener(this, &FlockParametersGui::resizeFlockWorld);
    */
}

void KinectParametersGui::removeGui()
{
    /*
    mFlockWorldLimitMinX.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    mFlockWorldLimitMinY.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    */
}

//------------------------------------------------------------------------------
void KinectParametersGui::renderGui()
{
    mPanel.draw();
}

//------------------------------------------------------------------------------
void KinectParametersGui::saveParameters()
{
    mPanel.saveToFile("KinectSettings.xml");
}

void KinectParametersGui::loadParameters()
{
    mPanel.loadFromFile("KinectSettings.xml");
}



