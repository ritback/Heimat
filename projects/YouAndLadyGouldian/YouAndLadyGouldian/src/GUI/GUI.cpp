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
    
    mGeneralPanel.setup("Misc Panel");
    mGeneralPanel.add(mRenderSkeletons.set("Render Flock or Kinect", true));

    mFlockParametersGui.initGui();
#if USE_KINECT
    mKinectParametersGui.initGui();
#endif
}

void AppGui::launchGui()
{
    mDisplayGui = true;
    mGeneralPanel.setPosition(5, 5);
    mFlockParametersGui.launchGui();
    mFlockParametersGui.mPanel.setPosition(220, 5);
#if USE_KINECT
    mKinectParametersGui.launchGui();
    mKinectParametersGui.mPanel.setPosition(435, 5);
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



    
    mGeneralPanel.draw();

    mFlockParametersGui.renderGui();
#if USE_KINECT
    mKinectParametersGui.renderGui();
#endif


    std::stringstream frameRate;
    frameRate << "Framerate ";
    frameRate << ofGetFrameRate();
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofDrawBitmapString(frameRate.str(), 20, ofGetWindowHeight() - 20);
    ofPopStyle();
}


//------------------------------------------------------------------------------
void AppGui::saveParameters()
{
    mGeneralPanel.saveToFile("GeneralSettings.xml");
    mFlockParametersGui.saveParameters();
#if USE_KINECT
    mKinectParametersGui.saveParameters();
#endif
}

void AppGui::loadParameters()
{
    mGeneralPanel.loadFromFile("GeneralSettings.xml");
    mFlockParametersGui.loadParameters();

#if USE_KINECT
    mKinectParametersGui.loadParameters();
#endif

}

