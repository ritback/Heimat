#include "KinectParametersGui.h"

#if USE_KINECT

#include "ofApp.h"

#include "Kinect.h"
#include "ScarecrowsTracker.h"

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
    Kinect* kinect = mApp->getKinect();
    float hasMoove = (kinect->mScarecrowsTracker).getJointsHasMoveDistance();
    float attractionInc = (kinect->mScarecrowsTracker).getJointsAttractionInc();
    float attractionMin = (kinect->mScarecrowsTracker).getJointsAttractionMin();
    float attractionMax = (kinect->mScarecrowsTracker).getJointsAttractionMax();

    float treeCreationTime = (kinect->mScarecrowsTracker).getTreeCreationTime();

    mPanel.setup("Kinect Panel");
    
    mPanel.add(mRenderSkeletons.set("Render skeleton", false));

    ofParameterGroup silhouette;
    silhouette.setName("Silhouette");
    silhouette.add(mSilhouetteRenderNormal.set("Silhouette", true));
    silhouette.add(mSilhouetteRenderStream.set("Stream", false));
    silhouette.add(mSilhouetteRenderBackground.set("Background", false));
    silhouette.add(mSilhouetteRenderDepthLessBackground.set("Depth Background", false));
    mPanel.add(silhouette);


    ofParameterGroup skeletons;
    skeletons.setName("Skeletons");
    skeletons.add(mSkeletonsTreeCreationTime.set("Tree creation Time", treeCreationTime, 0, 200));
    skeletons.add(mSkeletonsJointsHasMoveDistance.set("Has Move Distance", hasMoove, 0, 200));
    skeletons.add(mSkeletonsJointsAttractionInc.set("Attraction Inc", attractionInc, 0, 2));
    skeletons.add(mSkeletonsJointsAttractionMin.set("Attraction Min", attractionMin, -20, 20));
    skeletons.add(mSkeletonsJointsAttractionMax.set("Attraction Max", attractionMax, -20, 20));
    mPanel.add(skeletons);

}

void KinectParametersGui::launchGui()
{
    mSilhouetteRenderNormal.addListener(this, &KinectParametersGui::setSilhouetteRenderNormal);
    mSilhouetteRenderStream.addListener(this, &KinectParametersGui::setSilhouetteRenderStream);
    mSilhouetteRenderBackground.addListener(this, &KinectParametersGui::setSilhouetteRenderBackground);
    mSilhouetteRenderDepthLessBackground.addListener(this, &KinectParametersGui::setSilhouetteRenderDepthLessBackground);

    mSkeletonsTreeCreationTime.addListener(this, &KinectParametersGui::setTreeCreationTime);
    mSkeletonsJointsHasMoveDistance.addListener(this, &KinectParametersGui::setJointsHasMoveDistance);
    mSkeletonsJointsAttractionInc.addListener(this, &KinectParametersGui::setJointsAttractionInc);
    mSkeletonsJointsAttractionMin.addListener(this, &KinectParametersGui::setJointsAttractionMin);
    mSkeletonsJointsAttractionMax.addListener(this, &KinectParametersGui::setJointsAttractionMax);
}

void KinectParametersGui::removeGui()
{
    mSilhouetteRenderNormal.removeListener(this, &KinectParametersGui::setSilhouetteRenderNormal);
    mSilhouetteRenderStream.removeListener(this, &KinectParametersGui::setSilhouetteRenderStream);
    mSilhouetteRenderBackground.removeListener(this, &KinectParametersGui::setSilhouetteRenderBackground);
    mSilhouetteRenderDepthLessBackground.removeListener(this, &KinectParametersGui::setSilhouetteRenderDepthLessBackground);

    mSkeletonsTreeCreationTime.addListener(this, &KinectParametersGui::setTreeCreationTime);
    mSkeletonsJointsHasMoveDistance.removeListener(this, &KinectParametersGui::setJointsHasMoveDistance);
    mSkeletonsJointsAttractionInc.removeListener(this, &KinectParametersGui::setJointsAttractionInc);
    mSkeletonsJointsAttractionMin.removeListener(this, &KinectParametersGui::setJointsAttractionMin);
    mSkeletonsJointsAttractionMax.removeListener(this, &KinectParametersGui::setJointsAttractionMax);
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
void KinectParametersGui::setSilhouetteRenderNormal(bool& inValue)
{
    if(inValue == true)
    {
        mSilhouetteRenderStream = false;
        mSilhouetteRenderBackground = false;
        mSilhouetteRenderDepthLessBackground = false;
    }
}

void KinectParametersGui::setSilhouetteRenderStream(bool& inValue)
{
    if(inValue == true)
    {
        mSilhouetteRenderNormal = false;
        mSilhouetteRenderBackground = false;
        mSilhouetteRenderDepthLessBackground = false;
    }
}

void KinectParametersGui::setSilhouetteRenderBackground(bool& inValue)
{
    if(inValue == true)
    {
        mSilhouetteRenderNormal = false;
        mSilhouetteRenderStream = false;
        mSilhouetteRenderDepthLessBackground = false;
    }
}

void KinectParametersGui::setSilhouetteRenderDepthLessBackground(bool& inValue)
{
    if(inValue == true)
    {
        mSilhouetteRenderNormal = false;
        mSilhouetteRenderStream = false;
        mSilhouetteRenderBackground = false;
    }
}


//------------------------------------------------------------------------------
void KinectParametersGui::setTreeCreationTime(float& inValue)
{
    Kinect* kinect = mApp->getKinect();
    (kinect->mScarecrowsTracker).setTreeCreationTime(inValue);
}

void KinectParametersGui::setJointsHasMoveDistance(float& inValue)
{
    Kinect* kinect = mApp->getKinect();
    (kinect->mScarecrowsTracker).setJointsHasMoveDistance(inValue);
}

void KinectParametersGui::setJointsAttractionInc(float& inValue)
{
    Kinect* kinect = mApp->getKinect();
    (kinect->mScarecrowsTracker).setJointsAttractionInc(inValue);
}

void KinectParametersGui::setJointsAttractionMin(float& inValue)
{
    Kinect* kinect = mApp->getKinect();
    (kinect->mScarecrowsTracker).setJointsAttractionMin(inValue);
}

void KinectParametersGui::setJointsAttractionMax(float& inValue)
{
    Kinect* kinect = mApp->getKinect();
    (kinect->mScarecrowsTracker).setJointsAttractionMax(inValue);
}

#endif
