#include "ofApp.h"

#include "Mvt1Visuals.h"

ofApp::ofApp()
: mVisuals()
, mOscHandler(this)
, mDisplayFramerate(false)
{
    
}

ofApp::~ofApp()
{
}

// -----------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
}

void ofApp::exit()
{

}

// -----------------------------------------------------------------------------
void ofApp::update()
{
    mOscHandler.update();
    mVisuals.update();
}


void ofApp::draw()
{
    mVisuals.draw();
    
    
    // ------------------------------
    if (mDisplayFramerate)
    {
        ofPushStyle();
        
        ofSetColor(255, 0, 0);
        stringstream reportStr;
        reportStr << "fps: " << ofGetFrameRate() << std::endl;
        ofDrawBitmapString(reportStr.str(), 20, 600);
        
        ofPopStyle();
    }
}


// -----------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch(key)
    {
        case 'f': case 'F':
            ofToggleFullscreen();
            break;
        case 'd': case 'D':
            mDisplayFramerate = !mDisplayFramerate;;
            break;
    }
}

void ofApp::keyReleased(int key)
{
    
}

// -----------------------------------------------------------------------------

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

void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}

// -----------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    mVisuals.resize(w, h);
}

void ofApp::gotMessage(ofMessage msg)
{
    
}

// -----------------------------------------------------------------------------
Mvt1Visuals* ofApp::getVisuals()
{
    return &mVisuals;
}
