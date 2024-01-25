#include "Tree.h"

bool Tree::mShouldActivateTreeGrowth = false;
int Tree::mActivationCounter = 0;

Tree::Tree()
    : mRandomPos(ofRandom(0, ofGetWindowHeight()), ofRandom(0, ofGetWindowWidth()))
    , mTreeShader("Tree")
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
    if (mActivationCounter == 0) return;

    if (mShouldActivateTreeGrowth)
    {
        growthActivation();
        mShouldActivateTreeGrowth = false;
    }


    updateAlpha();

}

void Tree::render()
{
    if (mActivationCounter == 0) return;


    mTreeShader.begin();

    mGlobalTime += ofGetLastFrameTime();

    mTreeShader.setUniform1f("uGlobalTime", mGlobalTime);
    mTreeShader.setUniform3f("uResolution", ofGetWindowWidth(), ofGetWindowHeight(), 4.0f);

    mTreeShader.setUniform1f("uAlpha", mAlpha);

    mTreeShader.setUniform4f("uPosition", mRandomPos.x, mRandomPos.y, 0, 0);
    
    ofDrawRectangle(0, 0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    

    mTreeShader.end();
}

//------------------------------------------------------------------------------
void Tree::incrementTreeGrowth()
{
    mShouldActivateTreeGrowth = true;
    mActivationCounter += 1;
}

//------------------------------------------------------------------------------
void Tree::growthActivation()
{
    mRandomPos.x = ofRandom(0, ofGetWindowHeight());
    mRandomPos.y = ofRandom(0, ofGetWindowWidth());

    mActivationTime = ofGetElapsedTimef();
    mActivationDuration = ofRandom(1, 2) * 60;
}

void Tree::restart()
{


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
