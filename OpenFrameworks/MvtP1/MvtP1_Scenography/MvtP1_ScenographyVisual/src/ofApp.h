#pragma once

#include "ofMain.h"

#include <vector>

#include "Mvt1Visuals.h"
//#include "OscMsgHandler.h"
#include "Mvt1GuiApp.h"

class ofApp : public ofBaseApp
{
public:
    ofApp();
    virtual ~ofApp();
    
public:
    void setup();
    void exit();

public:
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
    void dragEvent(ofDragInfo dragInfo);
    
public:
    void windowResized(int w, int h);
    void gotMessage(ofMessage msg);
    
public:
    Mvt1Visuals* getVisuals();
    
private:
    Mvt1Visuals mVisuals;
    //OscMsgHandler mOscHandler;
    Mvt1GuiApp* mGui;

private:
    bool mDisplayFramerate;
    
};
