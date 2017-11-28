#include "OscMsgHandler.h"

#include "ofApp.h"

OscMsgHandler::OscMsgHandler(ofApp* inApp)
    : mApp(inApp)
{
    mOSCReceiver.setup(PORT);
}

OscMsgHandler::~OscMsgHandler()
{

}

//------------------------------------------------------------------------------
void OscMsgHandler::update()
{
    while(mOSCReceiver.hasWaitingMessages())
    {
        ofxOscMessage message;
        mOSCReceiver.getNextMessage(message);
        
        std::vector<std::string> adressToken;
        parseMsgAdress(message.getAddress().c_str(), adressToken);
        
        if (adressToken.size() > 0)
        {
            if (adressToken[0] == "Blobs")
            {
                handleMsgBlobs(adressToken[1], message.getArgAsFloat(0));
            }
            else if (adressToken[0] == "Sand")
            {
                handleMsgSand(adressToken[1], message.getArgAsFloat(0));
            }
            else if (adressToken[0] == "Blinking")
            {
                handleMsgBlinkingColor(adressToken[1], message.getArgAsFloat(0));
            }
            else if (adressToken[0] == "Flakes")
            {
                if (adressToken[1] == "Back")
                    handleMsgFlakes(adressToken[2], message.getArgAsFloat(0), true);
                else if (adressToken[1] == "Front")
                    handleMsgFlakes(adressToken[2], message.getArgAsFloat(0), false);
            }
            else if (adressToken[0] == "Spirits")
            {
                handleMsgSpirits(adressToken[1], message.getArgAsFloat(0));
            }
            
            
            else {/*Default: Do nothing*/}
        }
    }
}


//------------------------------------------------------------------------------
void OscMsgHandler::parseMsgAdress(const char *inMsg,
                                   std::vector<std::string>& outAdressToken,
                                   char inSeparator)
{
    while (*inMsg++ != 0)
    {
        const char *begin = inMsg;
        
        while(*inMsg != inSeparator && *inMsg)
            inMsg++;
        
        outAdressToken.push_back(string(begin, inMsg));
    }
}
 
 
 //------------------------------------------------------------------------------
void OscMsgHandler::handleMsgBlobs(string& inAdress, float inValue)
{
    BlobsParameters p;
    if(inAdress == "BPM")
    {
        p.mBpm = inValue;
    }
    else if(inAdress == "BpmAmplitude")
    {
        p.mBpmAmplitude = inValue;
    }
    else if(inAdress == "DistortionAmount")
    {
        p.mDistortionAmount = inValue;
    }
    else if(inAdress == "DistortionSpeed")
    {
        p.mDistortionSpeed = inValue;
    }
    else if(inAdress == "MvtSpeed")
    {
        p.mMvtSpeed = inValue;
    }
    else if(inAdress == "MvtRange")
    {
        p.mMvtRange = inValue;
    }
    
    (mApp->getVisuals())->updateParameters(p);
}

void OscMsgHandler::handleMsgSand(string& inAdress, float inValue)
{
    SandParameters p;
    if(inAdress == "SandSpeed")
    {
        p.mSandSpeed = inValue;
    }
    else if(inAdress == "SandAmount")
    {
        p.mSandAmount = inValue;
    }
    else if(inAdress == "Red")
    {
        p.mUpdateColor = true;
        p.mSandColor[0] = inValue;
    }
    else if(inAdress == "Green")
    {
        p.mUpdateColor = true;
        p.mSandColor[1] = inValue;
    }
    else if(inAdress == "Blue")
    {
        p.mUpdateColor = true;
        p.mSandColor[2] = inValue;
    }
    
    (mApp->getVisuals())->updateParameters(p);
}

void OscMsgHandler::handleMsgBlinkingColor(string& inAdress, float inValue)
{
    BlinkingColorParameters p;
    if(inAdress == "Display")
    {
        p.mUpdateDisplay = true;
        p.mDisplay = inValue == 0 ? false : true;
    }
    else if(inAdress == "ColorChangeSpeed")
    {
        p.mColorChangeSpeed = inValue;
    }
    else if(inAdress == "Brightness")
    {
        p.mBrightness = inValue;
    }
    else if(inAdress == "ColorAmount")
    {
        p.mColorAmount = inValue;
    }
    else if(inAdress == "Alpha")
    {
        p.mAlpha = inValue;
    }
    
    (mApp->getVisuals())->updateParameters(p);
}

//------------------------------------------------------------------------------
void OscMsgHandler::handleMsgFlakes(string& inAdress, float inValue, bool isBack)
{
    FlakesParameters p;
    if(inAdress == "NumFlakes")
    {
        p.mNumFlakes = (int)inValue;
    }
    else if(inAdress == "ForceFieldMag")
    {
        p.mForceFieldMag = inValue;
    }
    else if(inAdress == "WorldViscosity")
    {
        p.mWorldViscosity = inValue;
    }
    else if(inAdress == "Mass")
    {
        p.mMass = inValue;
    }
    
    (mApp->getVisuals())->updateParameters(p, isBack);
}

//------------------------------------------------------------------------------
void OscMsgHandler::handleMsgSpirits(string& inAdress, float inValue)
{
    SpiritsParameters p;
    if(inAdress == "NumSpirits")
    {
        p.mNumSpirits = (int)inValue;
    }
    else if(inAdress == "ForceFieldMag")
    {
        p.mForceFieldMag = inValue;
    }
    else if(inAdress == "HeadMass")
    {
        p.mHeadMass = inValue;
    }
    else if(inAdress == "Length")
    {
        p.mLength = inValue;
    }
    
    (mApp->getVisuals())->updateParameters(p);
}



