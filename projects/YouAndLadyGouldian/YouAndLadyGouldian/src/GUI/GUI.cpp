#include "GUI.h"

#include "ofApp.h"
#include "BirdsFlock.h"
#include "HE_FlockingWorld.h"


AppGui::AppGui(ofApp* inApp)
: mApp(inApp)
, mFlockParametersGui(inApp)
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
}

void AppGui::launchGui()
{
    mDisplayGui = true;
    mFlockParametersGui.launchGui();
}

void AppGui::removeGui()
{
    mDisplayGui = false;
    mFlockParametersGui.removeGui();
}

//------------------------------------------------------------------------------
void AppGui::renderGui()
{

    if (!mDisplayGui) return;


    mGeneralPanel.setPosition(5, 5);
    mFlockParametersGui.mPanel.setPosition(220, 5);


    
    mGeneralPanel.draw();

    mFlockParametersGui.renderGui();



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

