#pragma once

#include "ofMain.h"
#include "BirdsFlock.h"
#include "JungleBackgound.h"
#include "GUI.h"
#include "Forest.h"
#include "ColonyManager.h"

#include "UseKinect.h"
#if USE_KINECT
#include "Kinect.h"
#endif

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
    void drawFlock();
    
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
    
public:
    BirdsFlock* getFlock();
#if USE_KINECT
    Kinect* getKinect();
#endif
    ColonyManager* getColonyManager();

public:
    BirdsFlock mFlock;

public:
    Forest mForest;
    
public:
    JungleBackgound mJungleBackgound;
    
public:
    ColonyManager mColonyManager;

#if USE_KINECT
public:
    Kinect mKinect;
#endif


private:
    AppGui mGui;
};
