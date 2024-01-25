#include "Mvt1GuiApp.h"

#include "ofApp.h"

Mvt1GuiApp::Mvt1GuiApp(shared_ptr<ofApp> inApp)
    : mApp(inApp)
    , mBlobsParametersChanged(true)
    , mSandParametersChanged(true)
    , mBlinkingColorParametersChanged(true)
    , mFrontFlakesParametersChanged(true)
    , mBackFlakesParametersChanged(true)
    , mSpiritsParametersChanged(true)
    , eActivParameters(BLOBS)
    , mPresets(this)
{

    // ----------------------------------------------------------------------
    mBlobsParameters.setName("Blobs parameters");
    mBlobsParameters.add(mBlobsBpm.set("Bpm", 90, 50, 200));
    mBlobsParameters.add(mBlobsBpmAmplitude.set("Bpm Amplitude", 1, 0, 50));
    mBlobsParameters.add(mBlobsDistortionAmount.set("Distortion Amount", 1, 0.1, 20));
    mBlobsParameters.add(mBlobsDistortionSpeed.set("Distortion Speed", 1, 0.1, 7));
    mBlobsParameters.add(mBlobsMvtSpeed.set("Mvt Speed", 1, 0.01, 12));
    mBlobsParameters.add(mBlobsMvtRange.set("Mvt Range", 1, 0.01, 4));
    ofAddListener(mBlobsParameters.parameterChangedE(), this, &Mvt1GuiApp::guiEventBlobs);
    mBlobsPanel.setup(mBlobsParameters);

    // ----------------------------------------------------------------------
    mSandParameters.setName("Sand parameters");
    mSandParameters.add(mSandSpeed.set("Speed", 0.03, 0, 1));
    mSandParameters.add(mSandAmount.set("Amount", 0.5, 0, 1));
    mSandParameters.add(mSandColor.set("Color", ofColor(254.5, 175.7, 50.3), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    ofAddListener(mSandParameters.parameterChangedE(), this, &Mvt1GuiApp::guiEventSand);
    mSandPanel.setup(mSandParameters);

    // ----------------------------------------------------------------------
    mBlinkingColorParameters.setName("Background Color parameters");
    mBlinkingColorParameters.add(mBlinkingColorDisplay.set("Display", false));
    mBlinkingColorParameters.add(mBlinkingColorSpeed.set("Blinking Speed", 0.1, 0, 2));
    mBlinkingColorParameters.add(mBlinkingColorBrightness.set("Color brightness", 0.8, 0, 1.0));
    mBlinkingColorParameters.add(mBlinkingColorColorAmount.set("Amount", 1, 0, 10));
    mBlinkingColorParameters.add(mBlinkingColorAlpha.set("Alpha", 1, 0, 1));
    ofAddListener(mBlinkingColorParameters.parameterChangedE(), this, &Mvt1GuiApp::guiEventBlinkingColor);
    mBlinkingColorPanel.setup(mBlinkingColorParameters);

    // ----------------------------------------------------------------------
    mFrontFlakesParameters.setName("FrontFlakes parameters");
    mFrontFlakesParameters.add(mFrontFlakesNumFlakes.set("Num Flake", 50, 0, 150));
    mFrontFlakesParameters.add(mFrontFlakesForceFieldMag.set("Force field magnitude", 5.1, 0, 10));
    mFrontFlakesParameters.add(mFrontFlakesWorldViscosity.set("World viscosity", 0.3, 0, 2));
    mFrontFlakesParameters.add(mFrontFlakesMass.set("Mass", 15, 1, 50));
    mFrontFlakesParameters.add(mFrontFlakesMinColor.set("Min Color", ofColor(0, 0, 0), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    mFrontFlakesParameters.add(mFrontFlakesMaxColor.set("Max Color", ofColor(255, 255, 255), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    ofAddListener(mFrontFlakesParameters.parameterChangedE(), this, &Mvt1GuiApp::guiEventFrontFlakes);
    
    mBackFlakesParameters.setName("BackFlakes parameters");
    mBackFlakesParameters.add(mBackFlakesNumFlakes.set("Num Flake", 0, 0, 150));
    mBackFlakesParameters.add(mBackFlakesForceFieldMag.set("Force field magnitude", 5.1, 0, 10));
    mBackFlakesParameters.add(mBackFlakesWorldViscosity.set("World viscosity", 0.3, 0, 2));
    mBackFlakesParameters.add(mBackFlakesMass.set("Mass", 15, 1, 50));
    mBackFlakesParameters.add(mBackFlakesMinColor.set("Min Color", ofColor(0, 0, 0), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    mBackFlakesParameters.add(mBackFlakesMaxColor.set("Max Color", ofColor(255, 255, 255), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    ofAddListener(mBackFlakesParameters.parameterChangedE(), this, &Mvt1GuiApp::guiEventBackFlakes);
    
    mSandParameters.setName("Flakes parameters");
    mFlakesParameters.add(mFrontFlakesParameters);
    mFlakesParameters.add(mBackFlakesParameters);
    mFlakesPanel.setup(mFlakesParameters);
    
    // ----------------------------------------------------------------------
    mSpiritsParameters.setName("spirits parameters");
    mSpiritsParameters.add(mSpiritsNumSpirits.set("Num Spirits", 10, 0, 15));
    mSpiritsParameters.add(mSpiritsForceFieldMag.set("Force field Magnitude", 5.1, 0, 10));
    mSpiritsParameters.add(mSpiritsMass.set("Mass", 5.0, 0, 10));
    mSpiritsParameters.add(mSpiritsLength.set("Length", 50, 0.5, 100));
    ofAddListener(mSpiritsParameters.parameterChangedE(), this, &Mvt1GuiApp::guiEventSpirits);
    mSpiritsPanel.setup(mSpiritsParameters);

    // ----------------------------------------------------------------------
    mPresets.init();

    // ----------------------------------------------------------------------
    ofxGuiSetFont("GOTHIC.TTF", 16);
    //ofxGuiSetDefaultHeight(10);
    //mFrontFlakesPanel.setDefaultHeight(80);
    windowResized(ofGetWindowWidth(), ofGetWindowHeight());

    ofBackground(0);
    ofSetVerticalSync(false);

    setActivPanelColor();
}

Mvt1GuiApp::~Mvt1GuiApp()
{

}

// -----------------------------------------------------------------------------

void Mvt1GuiApp::update()
{
    if(mBlobsParametersChanged)
    {
        BlobsParameters p;
        p.mBpm = mBlobsBpm;
        p.mBpmAmplitude = mBlobsBpmAmplitude;
        p.mDistortionAmount = mBlobsDistortionAmount;
        p.mDistortionSpeed = mBlobsDistortionSpeed;
        p.mMvtSpeed = mBlobsMvtSpeed;
        p.mMvtRange = mBlobsMvtRange;
        (mApp->getVisuals())->updateParameters(p);
        mBlobsParametersChanged = false;
    }

    if(mSandParametersChanged)
    {
        SandParameters p;
        p.mSandAmount = mSandAmount;
        p.mSandSpeed = mSandSpeed;
        p.mSandColor[0] = mSandColor->r;
        p.mSandColor[1] = mSandColor->g;
        p.mSandColor[2] = mSandColor->b;
        p.mUpdateColor = true;
        (mApp->getVisuals())->updateParameters(p);
        mSandParametersChanged = false;
    }

    if(mBlinkingColorParametersChanged)
    {
        BlinkingColorParameters p;
        p.mAlpha = mBlinkingColorAlpha;
        p.mBrightness = mBlinkingColorBrightness;
        p.mColorAmount = mBlinkingColorColorAmount;
        p.mColorChangeSpeed = mBlinkingColorSpeed;
        p.mDisplay = mBlinkingColorDisplay;
        p.mUpdateDisplay = true;
        (mApp->getVisuals())->updateParameters(p);
        mBlinkingColorParametersChanged = false;
    }
    if(mFrontFlakesParametersChanged)
    {
        FlakesParameters p;
        p.mNumFlakes = mFrontFlakesNumFlakes;
        p.mForceFieldMag = mFrontFlakesForceFieldMag;
        p.mMass = mFrontFlakesMass;
        p.mWorldViscosity = mFrontFlakesWorldViscosity;
        p.mMaxColor = mFrontFlakesMaxColor;
        p.mMinColor = mFrontFlakesMinColor;
        p.mUpdateColor = true;
        p.mWorldViscosity = mFrontFlakesWorldViscosity;
        (mApp->getVisuals())->updateParameters(p, false);
        mFrontFlakesParametersChanged = false;
    }
    if(mBackFlakesParametersChanged)
    {
        FlakesParameters p;
        p.mNumFlakes = mBackFlakesNumFlakes;
        p.mForceFieldMag = mBackFlakesForceFieldMag;
        p.mMass = mFrontFlakesMass;
        p.mMaxColor = mBackFlakesMaxColor;
        p.mMinColor = mBackFlakesMinColor;
        p.mUpdateColor = true;
        p.mWorldViscosity = mFrontFlakesWorldViscosity;
        (mApp->getVisuals())->updateParameters(p, true);
        mBackFlakesParametersChanged = false;
    }
    if(mSpiritsParametersChanged)
    {
        SpiritsParameters p;
        p.mNumSpirits = mSpiritsNumSpirits;
        p.mForceFieldMag = mSpiritsForceFieldMag;
        p.mHeadMass = mSpiritsMass;
        p.mLength = mSpiritsLength;
        (mApp->getVisuals())->updateParameters(p);
        mSpiritsParametersChanged = false;
    }

}

void Mvt1GuiApp::draw()
{
    ofPushStyle();
    ofPushMatrix();
    mBlobsPanel.draw();
    mSandPanel.draw();
    mBlinkingColorPanel.draw();
    mFlakesPanel.draw();
    mSpiritsPanel.draw();

    mPresets.draw();
    ofPopMatrix();
    ofPopStyle();
}



// -----------------------------------------------------------------------------
void Mvt1GuiApp::keyPressed(int key)
{
    switch(eActivParameters)
    {
    case BLOBS:
        handleKeyPressedBlobs(key);
    break;
    case SAND:
        handleKeyPressedSand(key);
    break;
    case BLINK:
        handleKeyPressedBlinkingColor(key);
    break;
    case FLAKES:
        handleKeyPressedFrontFlakes(key);
        handleKeyPressedBackFlakes(key);
    break;
    case SPIRIT:
        handleKeyPressedSpirit(key);
    break;
    default:
        break;
    }

    switch(key)
    {
    case OF_KEY_RIGHT:
        eActivParameters = (ParametersCurrentlyEdited)(eActivParameters+1);
        if(eActivParameters == NUM_MODE)
            eActivParameters = BLOBS;
        setActivPanelColor();
        break;

    case OF_KEY_LEFT:
        eActivParameters = (ParametersCurrentlyEdited)(eActivParameters-1);
        if(eActivParameters < BLOBS)
            eActivParameters = (ParametersCurrentlyEdited)(NUM_MODE-1);
        setActivPanelColor();
        break;

    default:
        break;
    }


}

void Mvt1GuiApp::keyReleased(int key)
{

}


//------------------------------------------------------------------------------
void Mvt1GuiApp::windowResized(int w, int h)
{
    int numPanel = 6; 
    float margin = 30;
    float panelWidth = (float)(w - margin*(numPanel+1))/(numPanel);
    

    mBlobsPanel.setPosition(margin, margin);
    mBlobsPanel.setSize(panelWidth, mBlobsPanel.getHeight());
    mBlobsPanel.setWidthElements(panelWidth);

    mSandPanel.setPosition(panelWidth + 2*margin, margin);
    mSandPanel.setSize(panelWidth, mSandPanel.getHeight());
    mSandPanel.setWidthElements(panelWidth);

    mBlinkingColorPanel.setPosition(2*panelWidth + 3*margin, margin);
    mBlinkingColorPanel.setSize(panelWidth, mBlinkingColorPanel.getHeight());
    mBlinkingColorPanel.setWidthElements(panelWidth);

    mFlakesPanel.setPosition(3*panelWidth + 4*margin, margin);
    mFlakesPanel.setSize(panelWidth, mFlakesPanel.getHeight());
    mFlakesPanel.setWidthElements(panelWidth);
    
    mSpiritsPanel.setPosition(4*panelWidth + 5*margin, margin);
    mSpiritsPanel.setSize(panelWidth, mSpiritsPanel.getHeight());
    mSpiritsPanel.setWidthElements(panelWidth);

    mPresets.mPresetsPanel.setPosition(5*panelWidth + 6*margin, margin);
    mPresets.mPresetsPanel.setSize(panelWidth, mSpiritsPanel.getHeight());
    mPresets.mPresetsPanel.setWidthElements(panelWidth);
}

//------------------------------------------------------------------------------

void Mvt1GuiApp::guiEventBlobs(ofAbstractParameter& e)
{
    mBlobsParametersChanged = true;
    eActivParameters = BLOBS;
    setActivPanelColor();
}
void Mvt1GuiApp::guiEventSand(ofAbstractParameter& e)
{
    mSandParametersChanged = true;
    eActivParameters = SAND; 
    setActivPanelColor();
}
void Mvt1GuiApp::guiEventBlinkingColor(ofAbstractParameter& e)
{
    mBlinkingColorParametersChanged = true;
    eActivParameters = BLINK;
    setActivPanelColor();
}
void Mvt1GuiApp::guiEventFrontFlakes(ofAbstractParameter& e)
{
    mFrontFlakesParametersChanged = true;
    eActivParameters = FLAKES;
    setActivPanelColor();
}
void Mvt1GuiApp::guiEventBackFlakes(ofAbstractParameter& e)
{
    mBackFlakesParametersChanged = true;
    eActivParameters = FLAKES;
    setActivPanelColor();
}
void Mvt1GuiApp::guiEventSpirits(ofAbstractParameter& e)
{
    mSpiritsParametersChanged = true;
    eActivParameters = SPIRIT;
    setActivPanelColor();

    /*
    if(e.type() == typeid(ofParatemer<int>).name()){
        ofParameter<int> p = e.cast<int>();
        ...
    }else if(e.type() == typeid(ofParameter<float>).name(){
        ofParameter<float> p = e.cast<float>();
        ...
    }else if(e.type() == typeid(ofParameter<ofVec3f>).name(){
        ofParameter<ofVec3f> p = e.cast<ofVec3f>();
        ...
    }
    */
}

//------------------------------------------------------------------------------

void Mvt1GuiApp::setActivPanelColor()
{
    mBlobsPanel.setBorderColor(ofColor(0));
    mSandPanel.setBorderColor(ofColor(0));
    mBlinkingColorPanel.setBorderColor(ofColor(0));
    mFlakesPanel.setBorderColor(ofColor(0));
    mSpiritsPanel.setBorderColor(ofColor(0));
    
    switch(eActivParameters)
    {
    case BLOBS:
        mBlobsPanel.setBorderColor(ofColor(200, 150, 50));
        break;
    case SAND:
        mSandPanel.setBorderColor(ofColor(200, 150, 50));
        break;
    case BLINK:
        mBlinkingColorPanel.setBorderColor(ofColor(200, 150, 50));
        break;
    case FLAKES:
        mFlakesPanel.setBorderColor(ofColor(200, 150, 50));
        break;
    case SPIRIT:
        mSpiritsPanel.setBorderColor(ofColor(200, 150, 50));
        break;
    default:
        break;
    }
}


//------------------------------------------------------------------------------

void Mvt1GuiApp::handleKeyPressedBlobs(int key)
{
    switch(key)
    {
    case 'A': case 'a':
        mBlobsBpm += 5;
        mBlobsParametersChanged = true;
        break;
    case 'Q': case 'q':
        mBlobsBpm -= 5;
        mBlobsParametersChanged = true;
        break;
    case 'Z': case 'z':
        mBlobsBpmAmplitude += 5;
        mBlobsParametersChanged = true;
        break;
    case 'S': case 's':
        mBlobsBpmAmplitude -= 5;
        mBlobsParametersChanged = true;
        break;
    case 'E': case 'e':
        mBlobsDistortionAmount += 2;
        mBlobsParametersChanged = true;
        break;
    case 'D': case 'd':
        mBlobsDistortionAmount -= 2;
        mBlobsParametersChanged = true;
        break;
    case 'R': case 'r':
        mBlobsDistortionSpeed += 0.5;
        mBlobsParametersChanged = true;
        break;
    case 'F': case 'f':
        mBlobsDistortionSpeed -= 0.5;
        mBlobsParametersChanged = true;
        break;
    case 'T': case 't':
        mBlobsMvtSpeed += 0.5;
        mBlobsParametersChanged = true;
        break;
    case 'G': case 'g':
        mBlobsMvtSpeed -= 0.5;
        mBlobsParametersChanged = true;
        break;
    case 'Y': case 'y':
        mBlobsMvtRange += 0.5;
        mBlobsParametersChanged = true;
        break;
    case 'H': case 'h':
        mBlobsMvtRange -= 0.5;
        mBlobsParametersChanged = true;
        break;

    default:
        break;
    }
}
void Mvt1GuiApp::handleKeyPressedSand(int key)
{
    switch(key)
    {
    case 'A': case 'a':
        mSandSpeed += 0.05;
        mSandParametersChanged = true;
        break;
    case 'Q': case 'q':
        mSandSpeed -= 0.05;
        mSandParametersChanged = true;
        break;
    case 'Z': case 'z':
        mSandAmount += 0.05;
        mSandParametersChanged = true;
        break;
    case 'S': case 's':
        mSandAmount -= 0.05;
        mSandParametersChanged = true;
        break;
    default:
        break;
    }
}
void Mvt1GuiApp::handleKeyPressedBlinkingColor(int key)
{
    switch(key)
    {
    case 'A': case 'a':
        mBlinkingColorSpeed += 0.1;
        mBlinkingColorParametersChanged = true;
        break;
    case 'Q': case 'q':
        mBlinkingColorSpeed -= 0.1;
        mBlinkingColorParametersChanged = true;
        break;
    case 'Z': case 'z':
        mBlinkingColorBrightness += 0.05;
        mBlinkingColorParametersChanged = true;
        break;
    case 'S': case 's':
        mBlinkingColorBrightness -= 0.05;
        mBlinkingColorParametersChanged = true;
        break;
    case 'E': case 'e':
        mBlinkingColorColorAmount += 0.5;
        mBlinkingColorParametersChanged = true;
        break;
    case 'D': case 'd':
        mBlinkingColorColorAmount -= 0.5;
        mBlinkingColorParametersChanged = true;
        break;
    case 'R': case 'r':
        mBlinkingColorAlpha += 0.1;
        mBlinkingColorParametersChanged = true;
        break;
    case 'F': case 'f':
        mBlinkingColorAlpha -= 0.1;
        mBlinkingColorParametersChanged = true;
        break;
    default:
        break;
    }
}
void Mvt1GuiApp::handleKeyPressedFrontFlakes(int key)
{
    switch(key)
    {
    case 'A': case 'a':
        mFrontFlakesNumFlakes += 5;
        mFrontFlakesParametersChanged = true;
        break;
    case 'Q': case 'q':
        mFrontFlakesNumFlakes -= 5;
        mFrontFlakesParametersChanged = true;
        break;
    case 'Z': case 'z':
        mFrontFlakesForceFieldMag += 0.5;
        mFrontFlakesParametersChanged = true;
        break;
    case 'S': case 's':
        mFrontFlakesForceFieldMag -= 0.5;
        mFrontFlakesParametersChanged = true;
        break;
    case 'E': case 'e':
        mFrontFlakesWorldViscosity += 0.1;
        mFrontFlakesParametersChanged = true;
        break;
    case 'D': case 'd':
        mFrontFlakesWorldViscosity -= 0.1;
        mFrontFlakesParametersChanged = true;
        break;
    case 'R': case 'r':
        mFrontFlakesMass += 5;
        mFrontFlakesParametersChanged = true;
        break;
    case 'F': case 'f':
        mFrontFlakesMass -= 5;
        mFrontFlakesParametersChanged = true;
        break;
    default:
        break;
    }
}
void Mvt1GuiApp::handleKeyPressedBackFlakes(int key)
{
    switch(key)
    {
    case 'A': case 'a':
        mBackFlakesNumFlakes += 5;
        mBackFlakesParametersChanged = true;
        break;
    case 'Q': case 'q':
        mBackFlakesNumFlakes -= 5;
        mBackFlakesParametersChanged = true;
        break;
    case 'Z': case 'z':
        mBackFlakesForceFieldMag += 0.5;
        mBackFlakesParametersChanged = true;
        break;
    case 'S': case 's':
        mBackFlakesForceFieldMag -= 0.5;
        mBackFlakesParametersChanged = true;
        break;
    case 'E': case 'e':
        mBackFlakesWorldViscosity += 0.1;
        mBackFlakesParametersChanged = true;
        break;
    case 'D': case 'd':
        mBackFlakesWorldViscosity -= 0.1;
        mBackFlakesParametersChanged = true;
        break;
    case 'R': case 'r':
        mBackFlakesMass += 5;
        mBackFlakesParametersChanged = true;
        break;
    case 'F': case 'f':
        mBackFlakesMass -= 5;
        mBackFlakesParametersChanged = true;
        break;
    default:
        break;
    }
}
void Mvt1GuiApp::handleKeyPressedSpirit(int key)
{
    switch(key)
    {
    case 'A': case 'a':
        mSpiritsNumSpirits += 1;
        mSpiritsParametersChanged = true;
        break;
    case 'Q': case 'q':
        mSpiritsNumSpirits -= 1;
        mSpiritsParametersChanged = true;
        break;
    case 'Z': case 'z':
        mSpiritsForceFieldMag += 0.5;
        mSpiritsParametersChanged = true;
        break;
    case 'S': case 's':
        mSpiritsForceFieldMag -= 0.5;
        mSpiritsParametersChanged = true;
        break;
    case 'E': case 'e':
        mSpiritsMass += 0.5;
        mSpiritsParametersChanged = true;
        break;
    case 'D': case 'd':
        mSpiritsMass -= 0.5;
        mSpiritsParametersChanged = true;
        break;
    case 'R': case 'r':
        mSpiritsLength += 0.5;
        mSpiritsParametersChanged = true;
        break;
    case 'F': case 'f':
        mSpiritsLength -= 0.5;
        mSpiritsParametersChanged = true;
        break;
    default:
        break;
    }
}
