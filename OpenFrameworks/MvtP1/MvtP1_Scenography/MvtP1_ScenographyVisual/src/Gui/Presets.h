#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Mvt1GuiApp;

class Presets
{
public:
    Presets(Mvt1GuiApp* inGuiApp);
    virtual ~Presets();

public:
    void init();
    void update();
    void draw();

public:
    void guiEventPresets(ofAbstractParameter& e);
    void saveNewPreset();
    void loadPreset(string& e);

private:
    void loadPresetsListFromFolder();

private:
    typedef std::vector<ofParameter<float>*> Buttons;
    typedef Buttons::iterator ButtonsIt;

public:
    Mvt1GuiApp* mGuiApp;

public:
    ofxPanel mPresetsPanel;

private:
    ofParameter<float> mSaveButton;
    Buttons mButtons;
    ofParameterGroup mPresetsList;

    ofParameterGroup mAllParameters;
    ofXml mXMLSettings;
};
