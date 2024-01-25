#pragma once

#include "HE_ParameterOscSenders.h"

// -----------------------------------------------------------------------------
template<typename Type>
HEParameterWithCallback<Type>::HEParameterWithCallback()
: ofParameter<Type>()
, mValueChange(0)
{
    
}

template<typename Type>
HEParameterWithCallback<Type>::~HEParameterWithCallback()
{
    
}

//------------------------------------------------------------------------------
template<typename Type>
void HEParameterWithCallback<Type>::activateListener()
{
    this->addListener(this, &HEParameterWithCallback<Type>::callback);
}

template<typename Type>
void HEParameterWithCallback<Type>::deactivateListener()
{
    this->removeListener(this, &HEParameterWithCallback<Type>::callback);
}

//------------------------------------------------------------------------------
template<typename Type>
void HEParameterWithCallback<Type>::setValueChangeCallback(ValueChange inValue)
{
    *mValueChange = inValue;
}

template<typename Type>
void HEParameterWithCallback<Type>::setValueChangeCallbackOwner(void* inValue)
{
    mCaller = inValue;
}

//------------------------------------------------------------------------------
template<typename Type>
void HEParameterWithCallback<Type>::callback(Type& inValue)
{
    if (mValueChange)
        inValue->(*mValueChange)(inValue);
}
