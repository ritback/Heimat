#pragma once

#include "ofMain.h"

#include "ofxOsc.h"


// -----------------------------------------------------------------------------
template<typename Type>
class HEParameterOscSender : public ofParameter<Type>
{
public:
    HEParameterOscSender(ofxOscSender* inOscSender, const char* inMsgAdress);
    virtual ~HEParameterOscSender();
    
public:
    void activateOsc();
    void deactivateOsc();
    
public:
    virtual void sendValueAsMsg(Type& inValue) = 0;
    
public:
    ofxOscSender* mOscSender;
    std::string mMsgAdress;
};

#include "HE_ParameterOscSenders.hpp"


// -----------------------------------------------------------------------------
class HEFloatParameterOscSender : public HEParameterOscSender<float>
{
public:
    HEFloatParameterOscSender(ofxOscSender* inOscSender,
                              const char* inMsgAdress,
                              const char* inName,
                              float inMin, float inMax, float inVal);
    virtual ~HEFloatParameterOscSender();
    
public:
    virtual void sendValueAsMsg(float& inValue) override;
    
};



