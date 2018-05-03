#include "EyeWithAnimations.h"

EyeWithAnimations::EyeWithAnimations(float inX, float inY, float inWidth, float inHeight)
: Eye(inX, inY, inWidth, inHeight)
, mBlinkAnimationIsRunning(false)
, mIsLookingElsewhere(false)
{
    setupEyelidAnimation();
    createEyelidShape();
}

EyeWithAnimations::~EyeWithAnimations()
{

}

// -----------------------------------------------------------------------------
void EyeWithAnimations::render()
{
    Eye::render();

    ofPushMatrix();
    ofTranslate(mPos);
    ofScale(mSize);
    drawEyelid();
    ofPopMatrix();

}

void EyeWithAnimations::update()
{
    Eye::update();

    if (mBlinkAnimationIsRunning)
    {
        updateEyelid();
    }
    
    if(mIsLookingElsewhere)
    {
        updateLookingElsewhere();
    }
}

// -----------------------------------------------------------------------------
void EyeWithAnimations::launchBlink(double inBlinkTime)
{
    mBlinkAnimationIsRunning = true;
    mBlinkBeginTime = (float)ofGetElapsedTimeMillis();
    mBlinkTime = inBlinkTime;
    setupEyelidAnimation();
}


// -----------------------------------------------------------------------------
void EyeWithAnimations::launchLookingElsewhere()
{
    mIsLookingElsewhere = true;
    mLookingElsewhereBeginTimeOnPoint = (float)ofGetElapsedTimeMillis();
    mLookingElsewhereTimeOnPoint = ofRandom(500, 1000);
    mNumLookingElsewherePoints = floor(ofRandom(1, 5.9999));
    mCurrentLookingElsewherePoint = 0;
    
    float worldWidth = ofGetWindowWidth();
    float worldHeight = ofGetWindowHeight();
    ofPoint lookAround = ofPoint(ofRandom(0, worldWidth),
                                 ofRandom(0, worldHeight));
    
    for (int i = 0; i < 5; ++i)
    {
        mLookingElsewherePoints[i].x = lookAround.x + ofRandom(-worldWidth / 8, worldWidth / 8);
        mLookingElsewherePoints[i].y = lookAround.y + ofRandom(-worldHeight / 8, worldHeight / 8);
    }
}

bool EyeWithAnimations::isLookingElsewhere()
{
    return mIsLookingElsewhere;
}

// -----------------------------------------------------------------------------
void EyeWithAnimations::updateEyelid()
{
    float t = (float)ofGetElapsedTimeMillis() - mBlinkBeginTime;
    float factor = 0.0;
    
    if (t > mBlinkTime)
    {
        mBlinkAnimationIsRunning = false;
        setupEyelidAnimation();
    }
    else if (t < (float)mBlinkTime/2)
    {
        factor = (float)2/((float)mBlinkTime) * t;
    }
    else
    {
        factor = -(float)2/((float)mBlinkTime) * t + 2;
    }
    
    cpCurrentCornerLeft.x = mAnimCoefLeftA.x * factor + mAnimCoefLeftB.x;
    cpCurrentCornerLeft.y = mAnimCoefLeftA.y * factor + mAnimCoefLeftB.y;
    cpCurrentCornerRight.x = mAnimCoefRightA.x * factor + mAnimCoefRightB.x;
    cpCurrentCornerRight.y = mAnimCoefRightA.y * factor + mAnimCoefRightB.y;
    
    createEyelidShape();
}


// -----------------------------------------------------------------------------
void EyeWithAnimations::updateLookingElsewhere()
{
    float t = (float)ofGetElapsedTimeMillis() - mLookingElsewhereBeginTimeOnPoint;
    float factor = 0.0;
    
    if (t > mLookingElsewhereTimeOnPoint)
    {
        if (mCurrentLookingElsewherePoint > mNumLookingElsewherePoints)
        {
            mIsLookingElsewhere = false;
            return;
        }
        else
        {
            ++mCurrentLookingElsewherePoint;
            mLookingElsewhereTimeOnPoint = ofRandom(100, 1000);
            mLookingElsewhereBeginTimeOnPoint = (float)ofGetElapsedTimeMillis();
        }
    }
    
    stareAt(mLookingElsewherePoints[mCurrentLookingElsewherePoint].x,
            mLookingElsewherePoints[mCurrentLookingElsewherePoint].y);
    
}

// -----------------------------------------------------------------------------
void EyeWithAnimations::setupEyelidAnimation()
{

    // position of eyelid is normalized between 0 and 1, 0 being the top
    cpCurrentCornerRight = cpCornerUpRight;
    cpCurrentCornerLeft = cpCornerUpLeft;

    // linear operation for animation: current point = PointA * t + PointB;
    mAnimCoefLeftA = ofPoint(cpCornerDownLeft.x - cpCornerUpLeft.x,
                             cpCornerDownLeft.y - cpCornerUpLeft.y);
    mAnimCoefLeftB = ofPoint(cpCornerUpLeft.x, cpCornerUpLeft.y);

    mAnimCoefRightA = ofPoint(cpCornerDownRight.x - cpCornerUpRight.x,
                              cpCornerDownRight.y - cpCornerUpRight.y);
    mAnimCoefRightB = ofPoint(cpCornerUpRight.x, cpCornerUpRight.y);
}


void EyeWithAnimations::createEyelidShape()
{
    mEyelid.clear();

    mEyeCornerLeft = ofPoint(-0.5f, 0);
    mEyeCornerRight = ofPoint(0.5f, 0);

    // Eye contour up
    mEyelid.moveTo(mEyeCornerLeft); // begin left
    mEyelid.bezierTo(cpCornerUpLeft, cpCornerUpRight, mEyeCornerRight);

    // Eye contour down
    mEyelid.bezierTo(cpCurrentCornerRight, cpCurrentCornerLeft, mEyeCornerLeft);

    mEyelid.close();

    mEyelid.setFillColor(ofColor(0));

}


void EyeWithAnimations::drawEyelid()
{
    mEyelid.draw();
}
