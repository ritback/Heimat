#include "HE_ParameterOscSenders.h"


// -----------------------------------------------------------------------------
HEFloatParameterOscSender::HEFloatParameterOscSender(ofxOscSender* inOscSender,
                                                     const char* inMsgAdress,
                                                     const char* inName,
                                                     float inMin, float inMax,
                                                     float inVal)
    : HEParameterOscSender<float>(inOscSender, inMsgAdress)
{
    set(inName, inVal, inMin, inMax);
}

HEFloatParameterOscSender::~HEFloatParameterOscSender()
{
    
}

//------------------------------------------------------------------------------
void HEFloatParameterOscSender::sendValueAsMsg(float& inValue)
{
    if (mOscSender)
    {
        ofxOscMessage m;
        std::string messageAdress;
        messageAdress.assign(mMsgAdress);
        m.setAddress(messageAdress.c_str());
        
        m.addFloatArg(inValue);
        
        mOscSender->sendMessage(m, false);
    }
}

