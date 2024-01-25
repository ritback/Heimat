#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "UsersTracker.h"
#include <vector>

#define HOST "localhost"
#define PORT 12345


class ofApp : public ofBaseApp
{
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
    int mResendWindowSize;
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    UsersTracker mUsersTracker;

private:
    ofxOscSender mOSCSender;

private: // GUI
    void initGui();
    void launchGui();
    void removeGui();
    void renderGui();

    bool mDisplayGui;

    ofxPanel mUTPanel;
    ofxFloatSlider mUTImgThresold;
    ofxFloatSlider mUTImgBlur;
    ofxButton mUTBgdRefresh;
    void UTRefreshBgd();
    void UTSetThreshold(float & inThreshold);
    void UTSetBlur(float & inBlur);

private:
    uint64_t mFirstTimeRefreshBackGround;
};
