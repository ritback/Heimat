#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp
{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    void randomizeCameraDrawingPos();

private:
    ofVideoGrabber mVidGrabber;
    ofPixels mVideoPixels;
    ofTexture mVideoTexture;
    int mCamWidth;
    int mCamHeight;
    int mWindowWidth;
    int mWindowHeight;

    typedef std::vector<ofPoint*>::iterator PosArrayIt;
    typedef std::vector<ofPoint*>::iterator PosArrayIt;
    std::vector<ofPoint*> mCameraDrawingPos;
};
