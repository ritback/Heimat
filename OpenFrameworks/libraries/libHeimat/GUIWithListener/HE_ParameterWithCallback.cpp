#include "HE_ParameterWithCallback.h"


// -----------------------------------------------------------------------------
HEFloatParameterWithCallback::HEFloatParameterWithCallback(const char* inName,
                                                           float inMin,
                                                           float inMax,
                                                           float inVal)
    : HEParameterWithCallback<float>()
{
    set(inName, inVal, inMin, inMax);
}

HEFloatParameterWithCallback::~HEFloatParameterWithCallback()
{
    
}

//------------------------------------------------------------------------------
HEBoolParameterWithCallback::HEBoolParameterWithCallback(const char* inName,
                                                         bool inValue)
    : HEParameterWithCallback<bool>()
{
    set(inName, inValue);
}

HEBoolParameterWithCallback::~HEBoolParameterWithCallback()
{
    
}

