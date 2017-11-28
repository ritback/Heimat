#include "ofApp.h"

#include "Flock/DrawnPerson.h"
#include "Flock/Flock_FlockingWorld.h"
#include "Flock/Flock_Flock.h"
#include "Users/UsersTracker.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
	mFlock = new Flock<DrawnPerson, StreetWorld>(200); // 200

	mUsersTracker = new UsersTracker(mFlock);

	mCam.setDistance(650);
	//ofToggleFullscreen();

	initGui();
    launchGui();

    mGuiPanel.loadFromFile("Settings.xml");
    removeGui();
}

void ofApp::exit()
{
	removeGui();

	delete mUsersTracker;
	delete mFlock;
}

void ofApp::update()
{
	mFlock->update();
	mUsersTracker->update();
}

void ofApp::draw()
{
	ofBackground(255);

	ofPushMatrix();
	ofPushStyle();

	mCam.begin();
	ofRotate(-15, 1, 0, 0);
	ofTranslate(0, ofGetWindowHeight()/12);

	ofEnableAlphaBlending();
	ofEnableDepthTest();

	mFlock->render();

	ofDisableDepthTest();
	ofDisableAlphaBlending();

	if (mDisplayGui)
	{
		if (mFlockRenderWorld)
		{
			mFlock->renderWorld();
		}
        if(mRenderUsersRoom)
        {
            mUsersTracker->renderRoom();
        }
        if(mRenderUsers)
        {
            mUsersTracker->renderUsers();
        }
	}
	mCam.end();
	

	ofPopMatrix();
	ofPopStyle();

	if (mDisplayGui)
	{

		renderGui();
		// finally, a report
		ofSetColor(0);
		stringstream reportStr;
		reportStr << "fps: " << ofGetFrameRate() << std::endl;
		reportStr << "Cam Position:" << std::endl;
		reportStr << "Disatance: "<< mCam.getDistance() << std::endl;
		ofPoint camPos = mCam.getGlobalPosition();
		reportStr << "Position: " << std::endl;
		reportStr << " x: " << camPos.x;
		reportStr << " y: " << camPos.y;
		reportStr << " z: " << camPos.z;
		reportStr << std::endl;

		ofDrawBitmapString(reportStr.str(), 20, 600);
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
		case 'd': case 'D':
			if (mDisplayGui)
			{
				removeGui();
			}
			else
			{
				launchGui();
			}
			break;
        case 'f': case 'F':
            ofToggleFullscreen();
            break;

		case 's': case 'S':
			mGuiPanel.saveToFile("Settings.xml");
			break;
            
        case 'l': case 'L':
            mGuiPanel.loadFromFile("Settings.xml");
            break;
    }
}

void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

void ofApp::mouseDragged(int x, int y, int button)
{

}

void ofApp::mousePressed(int x, int y, int button)
{

}

void ofApp::mouseReleased(int x, int y, int button)
{

}

void ofApp::mouseEntered(int x, int y)
{

}

void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

void ofApp::gotMessage(ofMessage msg)
{

}

void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
