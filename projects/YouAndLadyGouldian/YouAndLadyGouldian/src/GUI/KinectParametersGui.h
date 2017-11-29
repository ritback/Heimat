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
    void setJointsHasMoveDistance(float& inValue);
    void setJointsAttractionInc(float& inValue);
    void setJointsAttractionMin(float& inValue);
    void setJointsAttractionMax(float& inValue);

public:
    ofxPanel mPanel;

    ofParameter<bool> mSilhouetteRenderNormal;
    ofParameter<bool> mSilhouetteRenderBackground;

    ofParameter<float> mSkeletonsJointsHasMoveDistance;
    ofParameter<float> mSkeletonsJointsAttractionInc;
    ofParameter<float> mSkeletonsJointsAttractionMin;
    ofParameter<float> mSkeletonsJointsAttractionMax;


private:
    ofApp* mApp;


};








