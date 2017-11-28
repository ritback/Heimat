#pragma once

#include "ofMain.h"

#include "FlockParametersGui.h"

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

public:
    ofxPanel mGeneralPanel;
    ofParameter<bool> mRenderSkeletons;
    
private:
    ofApp* mApp;
    
    
};








