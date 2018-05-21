#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "ScreensPanel.h"

#define PORT 12345


class ofApp : public ofBaseApp
{
public:
    ofApp();
    virtual ~ofApp();
    
public:
    void setup();
    void exit();
    void update();
    void draw();
    
public:
    void keyPressed(int key);
    void keyReleased(int key);
    
public:
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    
public:
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    
private:
    const int mCaptureWidth;
    const int mCaptureHeight;
    ScreensPanel mPanel;

private: // GUI
    void initGUI();
    void launchGUI();
    void removeGUI();
    void renderGUI();

private:
    bool mDisplayGUI;

private:
    ofxPanel mGUIPanel;
    ofxButton mRefreshCamsDevices;
    ofxToggle mRenderImgs;
    ofxToggle mRenderAnalysisResults;
    ofxToggle mRenderExtractedROIs;
    ofxToggle mRenderCameras;
    
    ofxFloatSlider mDrawingsWidth;
    ofxFloatSlider mDrawingsHeight;
    ofxFloatSlider mDrawingsColumnsPos1;
    ofxFloatSlider mDrawingsColumnsPos2;
    ofxFloatSlider mDrawingsColumnsPos3;
    ofxFloatSlider mDrawingsLinesPos1;
    ofxFloatSlider mDrawingsLinesPos2;
    ofxFloatSlider mDrawingsLinesPos3;

    ofxIntSlider mImgsRenderWidth;
    ofxIntSlider mImgsRenderHeight;

    void refreshCamsDevices();

    void setDrawingsWidth(float& inDimension);
    void setDrawingsHeight(float& inDimension);
    void setDrawingsColumnsPos(float& inDimension);
    void setDrawingsLinesPos(float& inDimension);

};

