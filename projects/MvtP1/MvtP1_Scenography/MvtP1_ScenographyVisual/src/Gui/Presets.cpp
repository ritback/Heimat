#include "Presets.h"

#include "Mvt1GuiApp.h"

Presets::Presets(Mvt1GuiApp* inGuiApp)
    : mGuiApp(inGuiApp)
{
    mSaveButton.set("Save as Preset", false);

    mPresetsList.setName("Settings Presets");
    mPresetsList.add(mSaveButton);

    loadPresetsListFromFolder();

    ofAddListener(mPresetsList.parameterChangedE(), this, &Presets::guiEventPresets);

    mPresetsPanel.setName("Presets");
    mPresetsPanel.setup(mPresetsList);

}

Presets::~Presets()
{
    for(ButtonsIt it = mButtons.begin();
        it != mButtons.end(); it++)
    {
        delete (*it);
    }
}

void Presets::init()
{
    mAllParameters.add(mGuiApp->mBlobsParameters);
    mAllParameters.add(mGuiApp->mSandParameters);
    mAllParameters.add(mGuiApp->mBlinkingColorParameters);
    mAllParameters.add(mGuiApp->mFlakesParameters);
    mAllParameters.add(mGuiApp->mSpiritsParameters);

    loadPresetsListFromFolder();
}

// -----------------------------------------------------------------------------
void Presets::update()
{

}

void Presets::draw()
{
    mPresetsPanel.draw();
}

// ----------------------------------------------------------------------------
void Presets::guiEventPresets(ofAbstractParameter& e)
{
    string name = e.getName();
    if(name == "Save as Preset")
    {
        saveNewPreset();
    }
    else
    {
        loadPreset(name);

    }
}

void Presets::saveNewPreset()
{
    int iPresetIndex = mButtons.size()+1;
    std::ostringstream newPresetPath;
    newPresetPath << "/Settings/Preset_" << iPresetIndex << ".xml";
    std::string presetPath = newPresetPath.str();

    ofSerialize(mXMLSettings, mAllParameters);
    mXMLSettings.save(presetPath);
    loadPresetsListFromFolder();

    mSaveButton.set(0);
}

void Presets::loadPreset(string& path)
{
    mXMLSettings.load(path);
    ofDeserialize(mXMLSettings, mAllParameters);

    for(ButtonsIt it = mButtons.begin(); it != mButtons.end(); it++)
    {
        (*it)->disableEvents();
        (*it)->set(0);
        (*it)->enableEvents();
    }

}

// -----------------------------------------------------------------------------

void Presets::loadPresetsListFromFolder()
{
    //some path, may be absolute or relative to bin/data
    string path = "Settings";
    ofDirectory dir(path);
    //only show xml files
    dir.allowExt("xml");
    //populate the directory object
    dir.listDir();

    //go through and print out all the paths
    for(int i = 0; i < dir.size(); i++)
    {
        string dirPath = dir.getPath(i);
        bool found = false;
        for(ButtonsIt it = mButtons.begin(); it != mButtons.end(); it++)
        {
            if((*it)->getName() == dirPath)
            {
                found = true;
            }
        }
        if(found == false)
        {
            ofParameter<float>* newButton = new ofParameter<float>();
            newButton->setName(dirPath);
            newButton->set(dirPath, 0);
            mButtons.push_back(newButton);
            mPresetsList.add(*newButton);

            mPresetsPanel.setup(mPresetsList);
        }
    }
    mGuiApp->windowResized(ofGetWindowWidth(), ofGetWindowHeight());
}

