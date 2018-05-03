#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define PORT 12345

class FaceTracking;
class EyesContainer;
class EyesStareAtController;

/*
 https://pjreddie.com/darknet/yolo/
 https://www.youtube.com/watch?v=4eIBisqx9_g
 https://www.iotforall.com/objects-recognition-live-stream-yolo-model/
 https://github.com/mrzl/ofxDarknet
 
 */


class ofApp : public ofBaseApp
{
public:
    ofApp();
    virtual ~ofApp();
    
public:
    void setup();
    void exit();
    void update();
    void draw();
    
public:
    void keyPressed(int key);
    void keyReleased(int key);
    
public:
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    
public:
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    ofxOscReceiver mOSCReceiver;
    
private:
    const int mCaptureWidth
    const int mCaptureHeight;
    FaceTracking mFaceTracking;
    EyesContainer mEyes;
    EyesStareAtController mEyesStareAtController;


private: // GUI
    void initGUI();
    void launchGUI();
    void removeGUI();
    void renderGUI();

private:
    bool mDisplayGUI;

private:
    ofxPanel mGUIPanel;
    ofxButton mRefreshCamsDevices;
    ofxToggle mRenderImgs;
    ofxToggle mRenderFacesRecognition;
    ofxToggle mRenderROIs;
    ofxToggle mRenderCameras;
    ofxToggle mRenderEyes;
    ofxToggle mRenderClosestHead;
    ofxToggle mEyesFollowMouse;
    ofxIntSlider mSimultaneousFaceTracking;
    ofxFloatSlider mDrawingsWidth;
    ofxFloatSlider mDrawingsHeight;
    ofxFloatSlider mDrawingsEyesWidthPercentage;
    ofxFloatSlider mDrawingsEyesHeightPercentage;
    ofxFloatSlider mDrawingsColumnsPos1;
    ofxFloatSlider mDrawingsColumnsPos2;
    ofxFloatSlider mDrawingsColumnsPos3;
    ofxFloatSlider mDrawingsLinesPos1;
    ofxFloatSlider mDrawingsLinesPos2;
    ofxFloatSlider mDrawingsLinesPos3;

    ofxIntSlider mImgsRenderWidth;
    ofxIntSlider mImgsRenderHeight;

    void refreshCamsDevices();
    void setSimultaneousFaceTracking(int& inNum);

    void setDrawingsWidth(float& inDimension);
    void setDrawingsHeight(float& inDimension);
    void setDrawingsColumnsPos(float& inDimension);
    void setDrawingsLinesPos(float& inDimension);



};

