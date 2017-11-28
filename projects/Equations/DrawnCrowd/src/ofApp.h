#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class DrawnPerson;
class StreetWorld;
class BoxWorld;
template<class BoidType, class WorldType>
class Flock;
class UsersTracker;

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

	Flock<DrawnPerson, StreetWorld>* mFlock;

	UsersTracker* mUsersTracker;

private: // GUIs
	void initGui();
	void launchGui();
	void removeGui();
	void renderGui();

	bool mDisplayGui;

public:
	void resizeFlockWorld(float & inLimit);
    void resizeUsersRoom(float & inLimit);

    void changeUsersInfluenceCohesion(float & inValue);
    void changeUsersInfluenceAlignement(float & inValue);
    void changeUsersInfluenceSeparation(float & inValue);

public:
	ofxPanel mGuiPanel;

	ofxToggle mFlockRenderWorld;
	ofxFloatSlider mFlockWorldLimitMinX;
	ofxFloatSlider mFlockWorldLimitMinY;
	ofxFloatSlider mFlockWorldLimitMaxX;
	ofxFloatSlider mFlockWorldLimitMaxY;

    ofxToggle mRenderUsers;
    ofxToggle mRenderUsersRoom;
    ofxFloatSlider mUsersRoomLimitMinX;
    ofxFloatSlider mUsersRoomLimitMinY;
    ofxFloatSlider mUsersRoomLimitMaxX;
    ofxFloatSlider mUsersRoomLimitMaxY;


    ofxFloatSlider mUsersInfluenceCohesion;
    ofxFloatSlider mUsersInfluenceAlignement;
    ofxFloatSlider mUsersInfluenceSeparation;
};
