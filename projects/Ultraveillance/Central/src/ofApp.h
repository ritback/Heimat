#pragma once

#define WEBCAM

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    ofShader mShader;
    ofTexture mVideoStream;
    ofVideoGrabber mCamera;
    ofFbo mFbo;

private:
    int mCamWidth;
    int mCamHeight;

private:
    static const int NUM_LOGOS = 2;
    ofImage mLogos[NUM_LOGOS];

};
