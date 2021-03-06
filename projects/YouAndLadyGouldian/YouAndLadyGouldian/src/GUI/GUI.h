#pragma once

#include "ofMain.h"

#include "FlockParametersGui.h"

#include "UseKinect.h"
#if USE_KINECT
#include "KinectParametersGui.h"
#endif

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
#if USE_KINECT
    KinectParametersGui mKinectParametersGui;
#endif
    
private:
    ofApp* mApp;
    
};








