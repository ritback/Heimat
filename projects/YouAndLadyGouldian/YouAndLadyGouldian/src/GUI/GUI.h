#pragma once

#include "ofMain.h"

#include "FlockParametersGui.h"
#include "KinectParametersGui.h"

class ofApp;

class AppGui
{
public:
    AppGui(ofApp* inApp);
    ~AppGui();
    
public: // GUIs
    void initGui();
    void launchGui();
    void removeGui();
    void renderGui();

public:
    void saveParameters();
    void loadParameters();

public:
    bool mDisplayGui;
    
public:
    FlockParametersGui mFlockParametersGui;
    KinectParametersGui mKinectParametersGui;

public:
    ofxPanel mGeneralPanel;
    ofParameter<bool> mRenderSkeletons;
    
private:
    ofApp* mApp;
    
    
};








