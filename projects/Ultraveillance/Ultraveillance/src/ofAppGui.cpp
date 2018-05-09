#include "ofApp.h"

//------------------------------------------------------------------------------
void ofApp::initGUI()
{
    mDisplayGUI = false;

    mGUIPanel.setup("Flock control Panel");
    mGUIPanel.add(mRefreshCamsDevices.setup("Refresh Cameras Devices"));
    mGUIPanel.add(mRenderImgs.setup("Render Imgs", true));
    mGUIPanel.add(mRenderFacesRecognition.setup("Render Face Recognition", true));
    mGUIPanel.add(mRenderROIs.setup("Render ROIs", true));
    mGUIPanel.add(mRenderCameras.setup("Render Cameras", false));


    mGUIPanel.add(mSimultaneousFaceTracking.setup("Simultaneous tracking",
                                                  mPanel.getNumSimultaneousFaceTracking(), 0, 8));
    mGUIPanel.add(mDrawingsWidth.setup("Drawings Width",
                                       mPanel.getDrawingsWidth(), 0, ofGetWindowWidth()));
    mGUIPanel.add(mDrawingsHeight.setup("Drawings Height",
                                        mPanel.getDrawingsHeight(), 0, ofGetWindowHeight()));
    
    float* columnsPos = mPanel.getDrawingsColumnsPos();
    mGUIPanel.add(mDrawingsColumnsPos1.setup("Columns X 1",
                                             columnsPos[0], 0, ofGetScreenWidth()));
    mGUIPanel.add(mDrawingsColumnsPos2.setup("Columns X 2",
                                             columnsPos[1], 0, ofGetScreenWidth()));
    mGUIPanel.add(mDrawingsColumnsPos3.setup("Columns X 3",
                                             columnsPos[2], 0, ofGetScreenWidth()));
    
    float* linesPos = mPanel.getDrawingsLinesPos();
    mGUIPanel.add(mDrawingsLinesPos1.setup("Lines Y 1",
                                             linesPos[0], 0, ofGetScreenHeight()));
    mGUIPanel.add(mDrawingsLinesPos2.setup("Lines Y 2",
                                             linesPos[1], 0, ofGetScreenHeight()));
    mGUIPanel.add(mDrawingsLinesPos3.setup("Lines Y 3",
                                             linesPos[2], 0, ofGetScreenHeight()));

    

}

void ofApp::launchGUI()
{
    mDisplayGUI = true;

    mRefreshCamsDevices.addListener(this, &ofApp::refreshCamsDevices);
    mSimultaneousFaceTracking.addListener(this, &ofApp::setSimultaneousFaceTracking);

    mDrawingsWidth.addListener(this, &ofApp::setDrawingsWidth);
    mDrawingsHeight.addListener(this, &ofApp::setDrawingsHeight);

    mDrawingsColumnsPos1.addListener(this, &ofApp::setDrawingsColumnsPos);
    mDrawingsColumnsPos2.addListener(this, &ofApp::setDrawingsColumnsPos);
    mDrawingsColumnsPos3.addListener(this, &ofApp::setDrawingsColumnsPos);

    mDrawingsLinesPos1.addListener(this, &ofApp::setDrawingsLinesPos);
    mDrawingsLinesPos2.addListener(this, &ofApp::setDrawingsLinesPos);
    mDrawingsLinesPos3.addListener(this, &ofApp::setDrawingsLinesPos);

}

void ofApp::removeGUI()
{
    mDisplayGUI = false;

    mRefreshCamsDevices.removeListener(this, &ofApp::refreshCamsDevices);
    mSimultaneousFaceTracking.removeListener(this, &ofApp::setSimultaneousFaceTracking);

    mDrawingsColumnsPos1.removeListener(this, &ofApp::setDrawingsColumnsPos);
    mDrawingsColumnsPos2.removeListener(this, &ofApp::setDrawingsColumnsPos);
    mDrawingsColumnsPos3.removeListener(this, &ofApp::setDrawingsColumnsPos);
   
    mDrawingsLinesPos1.removeListener(this, &ofApp::setDrawingsLinesPos);
    mDrawingsLinesPos2.removeListener(this, &ofApp::setDrawingsLinesPos);
    mDrawingsLinesPos3.removeListener(this, &ofApp::setDrawingsLinesPos);
}

//------------------------------------------------------------------------------
void ofApp::renderGUI()
{
    if(mDisplayGUI)
    {
        mGUIPanel.draw();

        ofSetColor(255, 0, 0);
        stringstream reportStr;
        reportStr << "fps: " << ofGetFrameRate() << std::endl;
        ofDrawBitmapString(reportStr.str(), 10, 10);
    }
}

//------------------------------------------------------------------------------
void ofApp::refreshCamsDevices()
{
    mPanel.needUpdateCamsDevices();
}

void ofApp::setSimultaneousFaceTracking(int& inNum)
{
    mPanel.setNumSimultaneousFaceTracking(inNum);
}

void ofApp::setDrawingsWidth(float& inDimension)
{
    mPanel.setDrawingsWidth(inDimension);
}

void ofApp::setDrawingsHeight(float& inDimension)
{
    mPanel.setDrawingsHeight(inDimension);
}

void ofApp::setDrawingsColumnsPos(float& inDimension)
{
    float dimensionPos[3];
    dimensionPos[0] = mDrawingsColumnsPos1;
    dimensionPos[1] = mDrawingsColumnsPos2;
    dimensionPos[2] = mDrawingsColumnsPos3;
    mPanel.setDrawingsColumnsPos(dimensionPos);
}

void ofApp::setDrawingsLinesPos(float& inDimension)
{
    float dimensionPos[3];
    dimensionPos[0] = mDrawingsLinesPos1;
    dimensionPos[1] = mDrawingsLinesPos2;
    dimensionPos[2] = mDrawingsLinesPos3;
    mPanel.setDrawingsLinesPos(dimensionPos);
}


