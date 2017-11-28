#include "ofApp.h"
#include "FaceTracking\FaceTracking.h"
#include "Eyes\EyesContainer.h"

//------------------------------------------------------------------------------
void ofApp::setup()
{
    mStreamWindowSize = ofPoint(1, 1);
    int captureWidth = 320;
    int captureHeight = 240;

    mFaceTracking = new FaceTracking(captureWidth, captureHeight);

    mEyes = new EyesContainer();

    mOSCReceiver.setup(PORT);
    mClosestHeadPosition = ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2); // if no heads around, look right in front of the scene.

    initGUI();

    /* TO UNCOMMENT AT INSTALL*/
    /*
    ofToggleFullscreen();
    launchGUI();
    mGUIPanel.loadFromFile("settings.xml");
    removeGUI();
    */

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
            mStreamWindowSize.x = message.getArgAsFloat(0);
            mStreamWindowSize.y = message.getArgAsFloat(1);
        }
        if (message.getAddress() == "/closestHeadPosition")
        {
            mClosestHeadPositionTarget.x = mStreamWindowSize.x - message.getArgAsFloat(0); // reversing coordinates because the screen is porojected
            mClosestHeadPositionTarget.y = message.getArgAsFloat(1);
            mClosestHeadPositionTarget *= ofGetWindowSize() / mStreamWindowSize;
        }
    }

    updateClosestHeadPosition();

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

//------------------------------------------------------------------------------
void ofApp::updateClosestHeadPosition()
{
    if (mClosestHeadPosition != mClosestHeadPositionTarget)
    {
        ofPoint dir = mClosestHeadPositionTarget- mClosestHeadPosition;
        mClosestHeadPosition += dir / 10;
    }
}