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


    ofParameterGroup skeletons;
    skeletons.setName("Skeletons");
    skeletons.add(mSkeletonsJointsHasMoveDistance.set("Has Move Distance", 75, 0, 200));
    skeletons.add(mSkeletonsJointsAttractionInc.set("Attraction Inc", 0.25, 0, 2));
    skeletons.add(mSkeletonsJointsAttractionMin.set("Attraction Min", -20, -20, 20));
    skeletons.add(mSkeletonsJointsAttractionMax.set("Attraction Max", 20, -20, 20));
    mPanel.add(skeletons);

}

void KinectParametersGui::launchGui()
{
    /*
    mFlockWorldLimitMinX.addListener(this, &FlockParametersGui::resizeFlockWorld);
    mFlockWorldLimitMinY.addListener(this, &FlockParametersGui::resizeFlockWorld);
    */

    mSkeletonsJointsHasMoveDistance.addListener(this, &KinectParametersGui::setJointsHasMoveDistance);
    mSkeletonsJointsAttractionInc.addListener(this, &KinectParametersGui::setJointsHasMoveDistance);
    mSkeletonsJointsAttractionMin.addListener(this, &KinectParametersGui::setJointsHasMoveDistance);
    mSkeletonsJointsAttractionMax.addListener(this, &KinectParametersGui::setJointsHasMoveDistance);

}

void KinectParametersGui::removeGui()
{
    /*
    mFlockWorldLimitMinX.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    mFlockWorldLimitMinY.removeListener(this, &FlockParametersGui::resizeFlockWorld);
    */

    mSkeletonsJointsHasMoveDistance.removeListener(this, &KinectParametersGui::setJointsHasMoveDistance);
    mSkeletonsJointsAttractionInc.removeListener(this, &KinectParametersGui::setJointsHasMoveDistance);
    mSkeletonsJointsAttractionMin.removeListener(this, &KinectParametersGui::setJointsHasMoveDistance);
    mSkeletonsJointsAttractionMax.removeListener(this, &KinectParametersGui::setJointsHasMoveDistance);
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




//------------------------------------------------------------------------------
void KinectParametersGui::setJointsHasMoveDistance(float& inValue)
{

}

void KinectParametersGui::setJointsAttractionInc(float& inValue)
{

}

void KinectParametersGui::setJointsAttractionMin(float& inValue)
{

}

void KinectParametersGui::setJointsAttractionMax(float& inValue)
{

}
