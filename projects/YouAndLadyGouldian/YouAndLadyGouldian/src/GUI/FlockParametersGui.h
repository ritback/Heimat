#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp;

class FlockParametersGui
{
public:
    FlockParametersGui(ofApp* inApp);
    ~FlockParametersGui();

public: // GUIs
    void initGui();
    void launchGui();
    void removeGui();
    void renderGui();

public:
    void saveParameters();
    void loadParameters();

public:
    void resizeFlockWorld(float & inLimit);
    void resizeFlockWorldDistance(float & inLimit);

public:
    ofxPanel mPanel;

    ofParameter<bool> mFlockRenderWorld;

    ofParameter<float> mFlockWorldLimitMinX;
    ofParameter<float> mFlockWorldLimitMinY;
    ofParameter<float> mFlockWorldLimitMaxX;
    ofParameter<float> mFlockWorldLimitMaxY;

    ofParameter<float> mFlockWorldLimitDistanceMinX;
    ofParameter<float> mFlockWorldLimitDistanceMinY;
    ofParameter<float> mFlockWorldLimitDistanceMaxX;
    ofParameter<float> mFlockWorldLimitDistanceMaxY;

private:
    ofApp* mApp;


};








