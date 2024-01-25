#include "GUI.h"

#include "ofApp.h"
#include "BirdsFlock.h"
#include "HE_FlockingWorld.h"


AppGui::AppGui(ofApp* inApp)
: mApp(inApp)
, mFlockParametersGui(inApp)
#if USE_KINECT
, mKinectParametersGui(inApp)
#endif
{

}

AppGui::~AppGui()
{
    
}

//------------------------------------------------------------------------------
void AppGui::initGui()
{
    mDisplayGui = true;
    
    mFlockParametersGui.initGui();
#if USE_KINECT
    mKinectParametersGui.initGui();
#endif
}

void AppGui::launchGui()
{
    mDisplayGui = true;
    mFlockParametersGui.launchGui();
    mFlockParametersGui.mPanel.setPosition(5, 5);
#if USE_KINECT
    mKinectParametersGui.launchGui();
    mKinectParametersGui.mPanel.setPosition(220, 5);
#endif

}

void AppGui::removeGui()
{
    mDisplayGui = false;
    mFlockParametersGui.removeGui();
#if USE_KINECT
    mKinectParametersGui.removeGui();
#endif
}

//------------------------------------------------------------------------------
void AppGui::renderGui()
{
    if (!mDisplayGui) return;

    mFlockParametersGui.renderGui();
#if USE_KINECT
    mKinectParametersGui.renderGui();
#endif

    std::stringstream frameRate;
    frameRate << "Framerate ";
    frameRate << ofGetFrameRate();
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofDrawBitmapString(frameRate.str(), ofGetWindowWidth() - 200, 20);
    ofPopStyle();
}


//------------------------------------------------------------------------------
void AppGui::saveParameters()
{
    mFlockParametersGui.saveParameters();
#if USE_KINECT
    mKinectParametersGui.saveParameters();
#endif
}

void AppGui::loadParameters()
{
    mFlockParametersGui.loadParameters();

#if USE_KINECT
    mKinectParametersGui.loadParameters();
#endif

}

