#include "ofMain.h"
#include "ofApp.h"

//------------------------------------------------------------------------------

int main()
{
    
    ofGLFWWindowSettings mainWindowSettings;
    mainWindowSettings.setGLVersion(3,2);
    mainWindowSettings.setSize(1024, 768);
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(mainWindowSettings);
    shared_ptr<ofApp> mainApp(new ofApp());
    ofRunApp(mainWindow, mainApp);

    ofGLFWWindowSettings guiWindowSettings;
    guiWindowSettings.setGLVersion(3, 2);
    guiWindowSettings.setSize(2500, 800);
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(guiWindowSettings);
    shared_ptr<Mvt1GuiApp> guiApp(new Mvt1GuiApp(mainApp));
    ofRunApp(guiWindow, guiApp);



    ofRunMainLoop();


    /*
    ofGLFWWindowSettings settings;
    
    settings.setGLVersion(3,2);
    settings.setSize(1024, 768);
    settings.setPosition(glm::vec2(100, 100));
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

    settings.setPosition(glm::vec2(100, 100+768));
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

    shared_ptr<ofApp> mainApp(new ofApp());
    shared_ptr<Mvt1GuiApp> guiApp(new Mvt1GuiApp(mainApp));

    ofRunApp(mainWindow, mainApp);
    ofRunApp(guiWindow, guiApp);

    ofRunMainLoop();
    */










}
