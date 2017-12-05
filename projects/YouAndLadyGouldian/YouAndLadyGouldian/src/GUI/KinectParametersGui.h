#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "UseKinect.h"
#if USE_KINECT

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
    void setSilhouetteRenderNormal(bool& inValue);
    void setSilhouetteRenderStream(bool& inValue);
    void setSilhouetteRenderBackground(bool& inValue);
    void setSilhouetteRenderDepthLessBackground(bool& inValue);

public:
    void setTreeCreationTime(float& inValue);
    void setJointsHasMoveDistance(float& inValue);
    void setJointsAttractionInc(float& inValue);
    void setJointsAttractionMin(float& inValue);
    void setJointsAttractionMax(float& inValue);

public:
    ofxPanel mPanel;

    ofParameter<bool> mRenderSkeletons;

    ofParameter<bool> mSilhouetteRenderNormal;
    ofParameter<bool> mSilhouetteRenderStream;
    ofParameter<bool> mSilhouetteRenderBackground;
    ofParameter<bool> mSilhouetteRenderDepthLessBackground;


    ofParameter<float> mSkeletonsTreeCreationTime;
    ofParameter<float> mSkeletonsJointsHasMoveDistance;
    ofParameter<float> mSkeletonsJointsAttractionInc;
    ofParameter<float> mSkeletonsJointsAttractionMin;
    ofParameter<float> mSkeletonsJointsAttractionMax;

private:
    ofApp* mApp;


};

#endif







