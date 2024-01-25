#include "ofApp.h"

//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30); // framerate from Kinect.. needed for image transformation and sync.

    mResendWindowSize = 61;

    // open an outgoing connection to HOST:PORT
    mOSCSender.setup(HOST, PORT);

    ofxOscMessage message;
    mOSCSender.sendMessage(message, false);
   

    initGui();
    launchGui();


    mUsersTracker.refreshBackgroundNeeded();
    mFirstTimeRefreshBackGround = ofGetElapsedTimeMillis() + 2000;
}

void ofApp::exit()
{
    removeGui();
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    if(mFirstTimeRefreshBackGround < ofGetElapsedTimeMillis() && mFirstTimeRefreshBackGround != 0)
    {
        mUsersTracker.refreshBackgroundNeeded();
        mFirstTimeRefreshBackGround = 0;
    }


    mUsersTracker.update();

    ofPoint roomSize = mUsersTracker.getRoomSize();
    ofxOscMessage roomSizeMsg;
    roomSizeMsg.setAddress("/roomSize");
    roomSizeMsg.addFloatArg(roomSize.x);
    roomSizeMsg.addFloatArg(roomSize.y);
    mOSCSender.sendMessage(roomSizeMsg, false);

    ofPoint* users = 0;
    int numUsers = 0;
    mUsersTracker.getUserPosInRoom(&users, &numUsers);

    ofxOscMessage pointsMsg;
    pointsMsg.setAddress("/points");
    pointsMsg.addIntArg(numUsers);
    for(int i = 0; i < numUsers; ++i)
    {
        pointsMsg.addFloatArg(users[i].x);
        pointsMsg.addFloatArg(users[i].y);
        pointsMsg.addFloatArg(users[i].z);
    }
    mOSCSender.sendMessage(pointsMsg, false);
}

void ofApp::draw()
{
    mUsersTracker.render();

    renderGui();

    ofPushStyle();
    ofSetColor(0, 230, 240);
    stringstream reportStr;
    reportStr << "fps: " << ofGetFrameRate() << std::endl;
    reportStr << "num users:" << mUsersTracker.getNumActiveUser() << std::endl;
    reportStr << std::endl;

    ofDrawBitmapString(reportStr.str(), 20, ofGetWindowHeight() - 20);
    ofPopStyle();

}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    mUsersTracker.refreshBackgroundNeeded();
}

void ofApp::keyReleased(int key){
    
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
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

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    ofxOscMessage message;
    message.setAddress("/roomSize");
    message.addFloatArg(ofGetWindowWidth());
    message.addFloatArg(ofGetWindowHeight());
    mOSCSender.sendMessage(message, false);
}

void ofApp::gotMessage(ofMessage msg)
{
    
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
