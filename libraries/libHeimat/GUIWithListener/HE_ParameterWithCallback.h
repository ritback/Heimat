#pragma once

#include "ofMain.h"

// -----------------------------------------------------------------------------
template<typename Type>
class HEParameterWithCallback : public ofParameter<Type>
{
public:
    HEParameterWithCallback();
    virtual ~HEParameterWithCallback();
    
public:
    void activateListener();
    void deactivateListener();
    
public:
    typedef void (*ValueChange)(Type&);
    void setValueChangeCallback(ValueChange inCallback);
    void setValueChangeCallbackOwner(void* inCallback);
    
public:
    void callback(Type& inValue);
    
private:
    ValueChange mValueChange;
    void* mCaller;
    
};

#include "HE_ParameterWithCallback.hpp"


// -----------------------------------------------------------------------------
class HEFloatParameterWithCallback : public HEParameterWithCallback<float>
{
public:
    HEFloatParameterWithCallback(const char* inName,
                                 float inMin, float inMax, float inVal);
    virtual ~HEFloatParameterWithCallback();
};

// -----------------------------------------------------------------------------
class HEBoolParameterWithCallback : public HEParameterWithCallback<bool>
{
public:
    HEBoolParameterWithCallback(const char* inName,
                                bool inValue);
    virtual ~HEBoolParameterWithCallback();
};



