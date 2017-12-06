#include "TreeForest.h"

Tree::Tree()
    : mIsVisible(false)
    , mPos(ofRandom(0, ofGetWindowHeight()), ofRandom(0, ofGetWindowWidth()))
    , mSize(ofGetWindowHeight() / 4, ofGetWindowWidth() / 4)
    , mTreeShader("TreeForest")
    , mGlobalTime(0)
    , mAlpha(0)
    , mActivationTime(0)
    , mActivationDuration(0)
{

}

Tree::~Tree()
{

}

//------------------------------------------------------------------------------
void Tree::update()
{
    if (!mIsVisible) return;

    updateAlpha();

}

void Tree::render()
{
    if (!mIsVisible) return;
    mTreeShader.begin();


    mGlobalTime += ofGetLastFrameTime();

    mTreeShader.setUniform1f("uGlobalTime", mGlobalTime);
    mTreeShader.setUniform3f("uResolution", ofGetWindowWidth(), ofGetWindowHeight(), 4.0f);

    mTreeShader.setUniform1f("uAlpha", mAlpha);

    mTreeShader.setUniform4f("uPosition", mPos.x, mPos.y, 0, 0);
    


    mSize.x = ofGetWindowWidth() / 2;
    mSize.y = ofGetWindowHeight() * 2 / 3;
    ofDrawRectangle(mPos.x - mSize.x / 2, ofGetWindowHeight() - mSize.y, mSize.x, mSize.y);

    mTreeShader.end();

    /*
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofNoFill();

    ofDrawRectangle(mPos.x - mSize.x / 2, ofGetWindowHeight() - mSize.y, mSize.x, mSize.y);
    ofPopStyle();
    */
}

//------------------------------------------------------------------------------
void Tree::activate(const ofPoint& inPos)
{
    mIsVisible = true;

    mPos = inPos;

    mActivationTime = ofGetElapsedTimef();
    mActivationDuration = ofRandom(0.5, 1.5) * 60;
}

//------------------------------------------------------------------------------
void Tree::updateAlpha()
{
    // 2 phases:
    // First alpha increase: during 1 % of the total phase.
    float maxAlphaTime = 5;//mActivationDuration;
    float currentTime = ofGetElapsedTimef() - mActivationTime;
    
    if (currentTime > mActivationDuration)
    {
        mIsVisible = false;
        return;
    }

    float coef = 1;
    if (currentTime <= maxAlphaTime)
    {
        coef = 0.2;
    }
    else if (currentTime >= maxAlphaTime)
    {
        coef = 0.00025;
    }

    mAlpha = 0.9;
    mAlpha /= coef * std::pow(currentTime - maxAlphaTime, 2) + 1;

}
