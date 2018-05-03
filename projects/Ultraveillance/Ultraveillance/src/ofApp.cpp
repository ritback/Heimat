#include "ofApp.h"
#include "FaceTracking.h"
#include "EyesContainer.h"
#include "EyesStareAtController.h"

//------------------------------------------------------------------------------
ofApp::ofApp()
: mCaptureWith(320)
, mCaptureHeight(240)
, mFaceTracking(mCaptureWidth, mCaptureHeight)
, mEyes()
, mEyesStareAtController(&mEyes)
{
    
}

ofApp::~ofApp()
{
    
}

//------------------------------------------------------------------------------
void ofApp::setup()
{

    mOSCReceiver.setup(PORT);
    mClosestHeadPosition = ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2); // if no heads around, look right in front of the scene.

    initGUI();

    /* TO UNCOMMENT AT INSTALL*/
    
    ofToggleFullscreen();
    launchGUI();
    mGUIPanel.loadFromFile("settings.xml");
    removeGUI();
    

}

void ofApp::exit()
{
    delete mFaceTracking;
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    mFaceTracking->update();

    mClosestHeadPositionTarget.x = ofGetWindowWidth() / 2;
    mClosestHeadPositionTarget.y = ofGetWindowHeight() / 2;
    while (mOSCReceiver.hasWaitingMessages())
    {
        ofxOscMessage message;
        mOSCReceiver.getNextMessage(message);

        if (message.getAddress() == "/windowSize")
        {
            mEyesStareAtController.updateStreamWindowSize(message.getArgAsFloat(0),
                                                          message.getArgAsFloat(1));
        }
        if (message.getAddress() == "/closestHeadPosition")
        {
            mEyesStareAtController.updateClosestHeadPosition(message.getArgAsFloat(0),
                                      message.getArgAsFloat(1));
        }
    }


    
    mEyesStareAtController.update();
    
    if (!mEyesFollowMouse)
    {
        mEyes->stareAt(mClosestHeadPosition.x, mClosestHeadPosition.y);
    }
    
    
    mEyes->update();
}

void ofApp::draw()
{
    ofBackground(0);

    if (mRenderImgs)
        mFaceTracking->drawImgs();
    if (mRenderFacesRecognition)
        mFaceTracking->drawFacesRecognition();
    if (mRenderROIs)
        mFaceTracking->drawROIs();
    if (mRenderCameras)
        mFaceTracking->drawCameras();
    if (mRenderEyes)
    {
        mEyes->render();
    }
    if (mRenderClosestHead)
    {
        ofPushStyle();
        ofSetColor(255, 255, 0);
        ofDrawSphere(mClosestHeadPosition, 50);
        ofPopStyle();
    }


    renderGUI();

    
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
        case 'D':
        case 'd':
            if (mDisplayGUI)
            {
                removeGUI();
            }
            else
            {
                launchGUI();
            }
            break;

        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;


        case 'S':
        case 's':
            mGUIPanel.saveToFile("settings.xml");
            break;
        case 'L':
        case 'l':
            mGUIPanel.loadFromFile("settings.xml");
            break;

        case 'R':
        case 'r':
            mFaceTracking->needUpdateCamsDevices();
            break;

    }
}

void ofApp::keyReleased(int key){
    
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    if (mEyesFollowMouse)
    {
        mEyes->stareAt(x, y);
    }
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
    
}

void ofApp::gotMessage(ofMessage msg)
{
    
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}

