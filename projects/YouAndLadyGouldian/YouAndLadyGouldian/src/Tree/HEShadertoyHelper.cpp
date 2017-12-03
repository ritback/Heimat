#include "HEShadertoyHelper.h"

HEShadertoyHelper::HEShadertoyHelper()
: ofxShadertoy()
{
    
}

HEShadertoyHelper::~HEShadertoyHelper()
{
    
}

//------------------------------------------------------------------------------

void HEShadertoyHelper::setUniform1f(const char* inName, float inValue)
{
    
    shader.setUniform1f(inName, inValue);
}

void HEShadertoyHelper::setUniform3fv(const char* inName,
                                     float inValue1,
                                     float inValue2,
                                     float inValue3)
{
    
    float pValue[3] = {inValue1, inValue2, inValue3};
    shader.setUniform3fv(inName, pValue, 1);
}

void HEShadertoyHelper::setUniform3fv(const char* inName, float* inValue)
{
    shader.setUniform3fv(inName, inValue, 1);
}






