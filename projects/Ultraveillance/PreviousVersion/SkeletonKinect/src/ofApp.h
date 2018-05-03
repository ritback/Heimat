#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Kinect\HE_SkeletonJoint.h"

#define HOST "localhost"
#define PORT 12345

class HEKinect;
class HEKinectDepthImage;
class HESkeleton;
template<class SkeletonType>
class HESkeletonsTracker;

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
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
public:
    HEKinect* mKinect;
    HEKinectDepthImage* mKinectImage;
    HESkeletonsTracker<HESkeleton>* mSkeletonsTracker;
    static const int NUM_HEADS = 10;
    int mSkeletonsHeadsCount;
    HESkeletonJoint mSkeletonsHeads[NUM_HEADS];

public:
    ofxOscSender mOSCSender;
};
