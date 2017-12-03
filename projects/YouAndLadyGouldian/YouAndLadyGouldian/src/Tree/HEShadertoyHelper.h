#pragma once

#include "ofMain.h"
#include "ofxShadertoy.h"

class HEShadertoyHelper: public ofxShadertoy
{
public:
    HEShadertoyHelper();
    virtual ~HEShadertoyHelper();
    
public:
    void setUniform1f(const char* inName, float inValue);
    void setUniform3fv(const char* inName, float inValue1, float inValue2, float inValue3);
    void setUniform3fv(const char* inName, float* inValue);
    
    
};
