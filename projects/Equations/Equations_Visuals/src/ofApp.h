#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "Actor.h"
#include "HE_FlockingWorld.h"
#include "HE_Flock.h"
#include "UsersTracker.h"


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
	void mouseMoved(int x, int y);
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
	ofEasyCam mCam;

    HEFlock<Actor, HEStreetWorld> mFlock;

	UsersTracker mUsersTracker;

};
