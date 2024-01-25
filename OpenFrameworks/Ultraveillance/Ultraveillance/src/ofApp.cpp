#include "ofApp.h"

//------------------------------------------------------------------------------
ofApp::ofApp()
: mCaptureWidth(320)
, mCaptureHeight(240)
, mPanel(mCaptureWidth, mCaptureHeight)
{
    
}

ofApp::~ofApp()
{
    
}

//------------------------------------------------------------------------------
void ofApp::setup()
{

    initGUI();

    
    // -----------------
    //ofToggleFullscreen();
    launchGUI();
    mGUIPanel.loadFromFile("settings.xml");
    removeGUI();
    
}

void ofApp::exit()
{
    
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    mPanel.update();
}

void ofApp::draw()
{
    ofBackground(0);

    if(mRenderImgs && mRenderAnalysisResults && mRenderExtractedROIs)
    {
        mPanel.draw();
    }
    else
    {
        if(mRenderImgs)
            mPanel.drawImgs();
        if(mRenderAnalysisResults)
            mPanel.drawAnalysisResults();
        if(mRenderExtractedROIs)
            mPanel.drawExtractedROIs();
        if(mRenderCameras)
            mPanel.drawCameras();
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
            mPanel.needUpdateCamsDevices();
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

void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}

