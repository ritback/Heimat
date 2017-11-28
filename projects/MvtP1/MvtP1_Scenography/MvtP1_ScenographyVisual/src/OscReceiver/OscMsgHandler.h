#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include <vector>

#define HOST "localhost"
#define PORT 12345

class ofApp;

class OscMsgHandler
{
public:
    OscMsgHandler(ofApp* inApp);
    ~OscMsgHandler();

public:
    void update();
    
private:
    void parseMsgAdress(const char *inMsg,
                        std::vector<std::string>& outAdressToken,
                        char inSeparator = '/');
    
private:
    void handleMsgBlobs(string& inAdress, float inValue);
    void handleMsgSand(string& inAdress, float inValue);
    void handleMsgBlinkingColor(string& inAdress, float inValue);
    
    void handleMsgFlakes(string& inAdress, float inValue, bool isBack);
    
    void handleMsgSpirits(string& inAdress, float inValue);
    
private:
    ofApp* mApp;
    ofxOscReceiver mOSCReceiver;
};




