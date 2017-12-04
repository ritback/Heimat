#include "TreeForest.h"

Tree::Tree()
    : mIsVisible(false)
    , mRandomPos(ofRandom(0, ofGetWindowHeight()), ofRandom(0, ofGetWindowWidth()))
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

    mTreeShader.setUniform4f("uPosition", mRandomPos.x, mRandomPos.y, 0, 0);
    mRandomPos.x += 0.000001;
    mRandomPos.y += 0.000001;
    
    //float pOnScreenPos[3] = {mPos.x, mPos.y, mPos.z};
    //mTreeShader.setUniform3fv("uOnScreenPos", pOnScreenPos);
    
    
    
    ofDrawRectangle(0, 0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    


    mTreeShader.end();
}

//------------------------------------------------------------------------------
void Tree::activate(const ofPoint& inPos)
{
    mIsVisible = true;

    mRandomPos = inPos;

    mActivationTime = ofGetElapsedTimef();
    mActivationDuration = ofRandom(1, 2) * 60;
}

//------------------------------------------------------------------------------
void Tree::updateAlpha()
{
    // 2 phases:
    // First alpha increase: during 1 % of the total phase.
    float maxAlphaTime = 5;//mActivationDuration;
    float currentTime = ofGetElapsedTimef() - mActivationTime;
    float coef = 1;
    if (currentTime > mActivationTime + mActivationDuration)
    {
        mIsVisible = false;
        return;
    }
    else if (currentTime <= maxAlphaTime)
    {
        coef = 0.2;
    }
    else if (currentTime >= maxAlphaTime)
    {
        coef = 0.00025;
    }

    mAlpha = 1;
    mAlpha /= coef * std::pow(currentTime - maxAlphaTime, 2) + 1;

}
