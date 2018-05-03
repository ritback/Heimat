#include "EyeController.h"

EyeController::EyeController(float inX, float inY, float inWidth, float inHeight)
    : mEye(inX, inY, inWidth, inHeight)
    , mNextBlinkTime(ofGetElapsedTimeMillis() + 100)
    , mNextLookElsewhereTime(ofGetElapsedTimeMillis() +  100)
{
    
}

EyeController::~EyeController()
{
    
}

// -----------------------------------------------------------------------------
void EyeController::render()
{
    mEye.render();
}

void EyeController::update()
{
    if (mNextBlinkTime < ofGetElapsedTimeMillis())
    {
        float mBlinkTime = ofRandom(150, 300);
        mEye.launchBlink(mBlinkTime);

        if (ofRandom(0, 10) < 3) // chance of double blink
        {
            mNextBlinkTime = ofGetElapsedTimeMillis() + mBlinkTime + ofRandom(10, 200);
        }
        else
        {
            mNextBlinkTime = ofGetElapsedTimeMillis() + ofRandom(10000, 40000);
        }
    }
    if (mNextLookElsewhereTime < ofGetElapsedTimeMillis())
    {
        mEye.launchLookingElsewhere();
        mNextLookElsewhereTime = ofGetElapsedTimeMillis() + ofRandom(20, 60) * 1000;
    }

    mEye.update();
}

// -----------------------------------------------------------------------------
void EyeController::stareAt(float inToX, float inToY)
{
    if (!mEye.isLookingElsewhere())
    {
        mEye.stareAt(inToX, inToY);
    }
}

// -----------------------------------------------------------------------------
void EyeController::setPos(const ofPoint& inPos)
{
    mEye.setPos(inPos);
}

void EyeController::setSize(const ofPoint& inSize)
{
    mEye.setSize(inSize);
}

const ofPoint& EyeController::getPos()
{
    return mEye.getPos();
}

const ofPoint& EyeController::getSize()
{
    return mEye.getSize();
}
