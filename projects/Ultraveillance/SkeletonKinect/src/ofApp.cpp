#include "ofApp.h"
#include "Kinect\HE_Kinect.h"
#include "Kinect\HE_KinectDepthImage.h"
#include "Kinect\HE_Skeleton.h"
#include "Kinect\HE_SkeletonsTracker.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    mKinect = new HEKinect();

        mKinectImage = new HEKinectDepthImage(mKinect,
                                    ofPoint(0, 0),
                                    ofPoint(ofGetWindowWidth(), ofGetWindowHeight()));

        mSkeletonsTracker = new HESkeletonsTracker<HESkeleton>(mKinect);

        mSkeletonsHeadsCount = 0;

        // open an outgoing connection to HOST:PORT
        mOSCSender.setup(HOST, PORT);

        ofxOscMessage message;
        message.setAddress("/windowSize");
        message.addFloatArg(ofGetWindowWidth());
        message.addFloatArg(ofGetWindowHeight());
        mOSCSender.sendMessage(message, false);
   
}

void ofApp::exit()
{
    delete mSkeletonsTracker;
    delete mKinectImage;
    delete mKinect;
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    if (!mKinect->isAvailable())
    {
        return;
    }

    mKinectImage->update();
    mSkeletonsTracker->update();

    mSkeletonsTracker->getHeadsJoints(mSkeletonsHeads, &mSkeletonsHeadsCount);

    int indexOfClosestHead = -1; // default value, no heads.
    float mClosestZ = 1000000000;
    for (int i = 0; i < mSkeletonsHeadsCount; ++i)
    {
        if (mSkeletonsHeads[i].mTrackingState == NUI_SKELETON_POSITION_TRACKED)
        {
            if (mSkeletonsHeads[i].mPoint.z < mClosestZ)
            {
                indexOfClosestHead = i;
                mClosestZ = mSkeletonsHeads[i].mPoint.z;
            }
        }
    }

    if (indexOfClosestHead != -1)
    {
        ofxOscMessage message;
        message.setAddress("/closestHeadPosition");
        message.addFloatArg(mSkeletonsHeads[indexOfClosestHead].mPoint.x);
        message.addFloatArg(mSkeletonsHeads[indexOfClosestHead].mPoint.y);
        mOSCSender.sendMessage(message, false);
    }

    ofxOscMessage message;
    message.setAddress("/windowSize");
    message.addFloatArg(ofGetWindowWidth());
    message.addFloatArg(ofGetWindowHeight());
    mOSCSender.sendMessage(message, false);
}

void ofApp::draw()
{
    if (!mKinect->isAvailable())
    {
        ofBackground(255, 0, 0);
        ofSetColor(0);
        for (int i = 0; i < ofGetWindowWidth()/100; ++i)
            for (int j = 0; j < ofGetWindowHeight() / 50; ++j)
                ofDrawBitmapString("NO KINECT!", i*100, j*50);
        return;
    }
    
    mKinectImage->render();
    mSkeletonsTracker->render();

    ofPushStyle();
    for (int i = 0; i < mSkeletonsHeadsCount; ++i)
    {
        if (mSkeletonsHeads[i].mTrackingState != NUI_SKELETON_POSITION_NOT_TRACKED)
        {
            if (mSkeletonsHeads[i].mTrackingState == NUI_SKELETON_POSITION_INFERRED)
            {
                ofSetColor(255, 0, 0);
            }
            else if (mSkeletonsHeads[i].mTrackingState == NUI_SKELETON_POSITION_TRACKED)
            {
                ofSetColor(255);
            }
            ofDrawSphere(ofPoint(mSkeletonsHeads[i].mPoint.x, mSkeletonsHeads[i].mPoint.y), 50);
        }
    }
    ofPopStyle();
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    
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
    message.setAddress("/windowSize");
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
