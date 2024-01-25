#pragma once

#include "HE_ParameterOscSenders.h"

// -----------------------------------------------------------------------------
template<typename Type>
HEParameterOscSender<Type>::HEParameterOscSender(ofxOscSender* inOscSender,
                                                 const char* inMsgAdress)
: ofParameter<Type>()
, mOscSender(inOscSender)
, mMsgAdress(inMsgAdress)
{
    
}

template<typename Type>
HEParameterOscSender<Type>::~HEParameterOscSender()
{
    
}

//------------------------------------------------------------------------------
template<typename Type>
void HEParameterOscSender<Type>::activateOsc()
{
    this->addListener(this, &HEParameterOscSender<Type>::sendValueAsMsg);
}

template<typename Type>
void HEParameterOscSender<Type>::deactivateOsc()
{
    this->removeListener(this, &HEParameterOscSender<Type>::sendValueAsMsg);
}
