#include "EyesStareAtController.h"


EyesStareAtController::EyesStareAtController()
: mClosestHeadPosition(ofGetWindowWidth()/2, ofGetWindowHeight()/2)
{
    
}

EyesStareAtController::~EyesStareAtController()
{
    
}

//------------------------------------------------------------------------------
void EyesStareAtController::update()
{
    if (mClosestHeadPosition != ofPoint(-1, -1, -1))
    {
        mEyes->stareAt(mClosestHeadPosition.x, mClosestHeadPosition.y);
    }
    else
    {
        mEyes->stareAt(mClosestHeadPosition.x, mClosestHeadPosition.y);
    }
    
    mClosestHeadPosition = ofPoint(-1, -1, -1);
}


//------------------------------------------------------------------------------
void EyesStareAtController::updateClosestHeadPosition(float inPosX, float inPosY)
{
    mClosestHeadPositionTarget.x = mStreamWindowSize.x - inPosX; // reversing coordinates because the screen is projected
    mClosestHeadPositionTarget.y = inPosY;
    mClosestHeadPositionTarget *= ofGetWindowSize() / mStreamWindowSize;
    
    if (mClosestHeadPosition != mClosestHeadPositionTarget)
    {
        ofPoint dir = mClosestHeadPositionTarget- mClosestHeadPosition;
        mClosestHeadPosition += dir * 0.1;
    }
}



void EyesStareAtController::updateStreamWindowSize(float inWidth,
                                                   float inHeigth)
{
    mStreamWindowSize.x = inWidth;
    mStreamWindowSize.y = inHeigth;
}
