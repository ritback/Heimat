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
    void setUpdateFlockWithWeb(bool& inValue);
    void setFlockNumBoids(float& inValue);
    void setFlockRules(float & inValue);
    void setFlockMasses(float & inValue);

public:
    void setWorldLimitRepulsion(float & inLimit);
    void resizeFlockWorld(float & inLimit);
    void resizeFlockWorldDistance(float & inLimit);

public:
    ofxPanel mPanel;

    ofParameter<bool> mUpdateNumFlockWithWeb;
    ofParameter<float> mNumBoids;

    ofParameter<float> mBoidsMasses;

    ofParameter<float> mFlockRulesCohesion;
    ofParameter<float> mFlockRulesSeparation;
    ofParameter<float> mFlockRulesAlignement;

    ofParameter<bool> mRenderWorld;
    ofParameter<float> mWorldLimitRepuslion;

    ofParameter<float> mWorldLimitMinX;
    ofParameter<float> mWorldLimitMinY;
    ofParameter<float> mWorldLimitMaxX;
    ofParameter<float> mWorldLimitMaxY;

    ofParameter<float> mWorldLimitDistanceMinX;
    ofParameter<float> mWorldLimitDistanceMinY;
    ofParameter<float> mWorldLimitDistanceMaxX;
    ofParameter<float> mWorldLimitDistanceMaxY;



private:
    ofApp* mApp;


};








