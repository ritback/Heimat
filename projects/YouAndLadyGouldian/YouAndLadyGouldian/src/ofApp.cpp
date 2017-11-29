#include "ofApp.h"

ofApp::ofApp()
    : ofBaseApp()
    , mFlock()
    , mKinect(&mFlock)
    , mGui(this)
{
    
}

ofApp::~ofApp()
{

}

//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
    mGui.initGui();
    mGui.launchGui();
}

void ofApp::exit()
{

}

//------------------------------------------------------------------------------
void ofApp::update()
{
    mKinect.updateSilhoutte();
    //mKinect.updateScarecrows();
    mFlock.update();
}

void ofApp::draw()
{   
    ofBackground(0);

    mKinect.renderSilhouette();

    //if(mGui.mRenderSkeletons)
    //    mKinect.renderScarecrows();
    
    drawFlock();

    mGui.renderGui();

}

void ofApp::drawFlock()
{
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

    mFlock.render();

    if(mGui.mFlockParametersGui.mRenderWorld)
        mFlock.renderWorld();

    ofPopMatrix();
}



//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch(key)
    {
        case 'f': case 'F':
            ofToggleFullscreen();
            break;
        case 'd': case 'D':
            mGui.mDisplayGui = !mGui.mDisplayGui;
            if(mGui.mDisplayGui)
                mGui.launchGui();
            else
                mGui.removeGui();

        case 'S':
        case 's':
            mGui.saveParameters();
            break;
        case 'L':
        case 'l':
            mGui.loadParameters();
            break;
            break;
    }
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

}

void ofApp::gotMessage(ofMessage msg)
{
    
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}

//------------------------------------------------------------------------------
BirdsFlock* ofApp::getFlock()
{
    return &mFlock;
}
