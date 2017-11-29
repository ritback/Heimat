#include "GUI.h"

#include "ofApp.h"
#include "BirdsFlock.h"
#include "HE_FlockingWorld.h"


AppGui::AppGui(ofApp* inApp)
: mApp(inApp)
, mFlockParametersGui(inApp)
, mKinectParametersGui(inApp)
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
    mKinectParametersGui.initGui();
}

void AppGui::launchGui()
{
    mDisplayGui = true;
    mFlockParametersGui.launchGui();
    mKinectParametersGui.launchGui();

    mGeneralPanel.setPosition(5, 5);
    mFlockParametersGui.mPanel.setPosition(220, 5);
    mKinectParametersGui.mPanel.setPosition(435, 5);


}

void AppGui::removeGui()
{
    mDisplayGui = false;
    mFlockParametersGui.removeGui();
    mKinectParametersGui.removeGui();
}

//------------------------------------------------------------------------------
void AppGui::renderGui()
{

    if (!mDisplayGui) return;



    
    mGeneralPanel.draw();

    mFlockParametersGui.renderGui();
    mKinectParametersGui.renderGui();



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
}

void AppGui::loadParameters()
{
    mGeneralPanel.loadFromFile("GeneralSettings.xml");
    mFlockParametersGui.loadParameters();

}

