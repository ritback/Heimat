#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp;

class KinectParametersGui
{
public:
    KinectParametersGui(ofApp* inApp);
    ~KinectParametersGui();

public: // GUIs
    void initGui();
    void launchGui();
    void removeGui();
    void renderGui();

public:
    void saveParameters();
    void loadParameters();

public:
    ofxPanel mPanel;

    ofParameter<bool> mSilhouetteRenderNormal;
    ofParameter<bool> mSilhouetteRenderBackground;


private:
    ofApp* mApp;


};








