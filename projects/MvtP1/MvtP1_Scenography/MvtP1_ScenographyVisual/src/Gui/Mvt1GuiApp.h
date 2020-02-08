#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <vector>

class ofApp;

class Mvt1GuiApp : public ofBaseApp
{
public:
    Mvt1GuiApp(shared_ptr<ofApp> inApp);
    virtual ~Mvt1GuiApp();

public:
    void update();
    void draw();

public:
    void keyPressed(int key);
    void keyReleased(int key);

public:
    void windowResized(int w, int h);

public:
    void guiEventBlobs(ofAbstractParameter& e);
    void guiEventSand(ofAbstractParameter& e);
    void guiEventBlinkingColor(ofAbstractParameter& e);
    void guiEventFrontFlakes(ofAbstractParameter& e);
    void guiEventBackFlakes(ofAbstractParameter& e);
    void guiEventSpirits(ofAbstractParameter& e);
    
private:
    void setActivPanelColor();

private:
    shared_ptr<ofApp> mApp;

private:
    typedef enum
    {
        BLOBS = 0,
        SAND,
        BLINK,
        FLAKES_BACK,
        FLAKES_FRONT,
        SPIRIT,
        NUM_MODE
    } ParametersCurrentlyEdited;
    ParametersCurrentlyEdited eActivParameters;

private:
    // ------------------------------------------
    ofxPanel mBlobsPanel;
    ofParameterGroup mBlobsParameters;
    bool mBlobsParametersChanged;
    ofParameter<float> mBlobsBpm;
    ofParameter<float> mBlobsBpmAmplitude;
    ofParameter<float> mBlobsDistortionAmount;
    ofParameter<float> mBlobsDistortionSpeed;
    ofParameter<float> mBlobsMvtSpeed;
    ofParameter<float> mBlobsMvtRange;

    // ------------------------------------------
    ofxPanel mSandPanel;
    ofParameterGroup mSandParameters;
    bool mSandParametersChanged;
    ofParameter<float> mSandSpeed;
    ofParameter<float> mSandAmount;
    ofParameter<ofColor> mSandColor;

    // ------------------------------------------
    ofxPanel mBlinkingColorPanel;
    ofParameterGroup mBlinkingColorParameters;
    bool mBlinkingColorParametersChanged;
    ofParameter<bool> mBlinkingColorDisplay;
    ofParameter<float> mBlinkingColorSpeed;
    ofParameter<float> mBlinkingColorBrightness;
    ofParameter<float> mBlinkingColorColorAmount;
    ofParameter<float> mBlinkingColorAlpha;

    // ------------------------------------------
    ofxPanel mFrontFlakesPanel;
    ofParameterGroup mFrontFlakesParameters;
    bool mFrontFlakesParametersChanged;
    ofParameter<float> mFrontFlakesNumFlakes;
    ofParameter<float> mFrontFlakesForceFieldMag;
    ofParameter<float> mFrontFlakesWorldViscosity;
    ofParameter<float> mFrontFlakesMass;
    ofParameter<ofColor> mFrontFlakesMinColor;
    ofParameter<ofColor> mFrontFlakesMaxColor;

    ofxPanel mBackFlakesPanel;
    ofParameterGroup mBackFlakesParameters;
    bool mBackFlakesParametersChanged;
    ofParameter<float> mBackFlakesNumFlakes;
    ofParameter<float> mBackFlakesForceFieldMag;
    ofParameter<float> mBackFlakesWorldViscosity;
    ofParameter<float> mBackFlakesMass;
    ofParameter<ofColor> mBackFlakesMinColor;
    ofParameter<ofColor> mBackFlakesMaxColor;

    // ------------------------------------------
    ofxPanel mSpiritsPanel;
    ofParameterGroup mSpiritsParameters;
    bool mSpiritsParametersChanged;
    ofParameter<float> mSpiritsNumSpirits;
    ofParameter<float> mSpiritsForceFieldMag;
    ofParameter<float> mSpiritsMass;
    ofParameter<float> mSpiritsLength;

private:
    void handleKeyPressedBlobs(int key);
    void handleKeyPressedSand(int key);
    void handleKeyPressedBlinkingColor(int key);
    void handleKeyPressedFrontFlakes(int key);
    void handleKeyPressedBackFlakes(int key);
    void handleKeyPressedSpirit(int key);


};

