#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <vector>


class HEGuiPanel : public ofxPanel
{
public:
    HEGuiPanel();
    virtual ~HEGuiPanel();
    
public:
    void activateListener();
    void deactivateListener();
    
    
private:
    typedef std::vector<void*> ParametersWithCallbacks;
    typedef ParametersWithCallbacks::iterator ParametersWithCallbacksIt;
    ParametersWithCallbacksIt mParameters;
    
};


