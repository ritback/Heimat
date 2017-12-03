#include "Tree.h"

Tree::Tree()
    : mPos(ofGetWindowHeight() / 2, ofGetWindowWidth() / 2)
    , mSize(ofGetWindowHeight()/2, ofGetWindowWidth()/2)
{
    mTreeShader.load("shaders/Tree.frag");
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
    
    mTreeShader.setUniform1f("uAlpha", mAlpha);
    
    
    float pOnScreenPos[3] = {mPos.x, mPos.y, mPos.z};
    mTreeShader.setUniform3fv("uOnScreenPos", pOnScreenPos);
    
    
    
    ofDrawRectangle(0, 0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
    
    mTreeShader.end();
}

//------------------------------------------------------------------------------
void Tree::activate(const ofPoint& inPos)
{
    mIsVisible = true;

    mPos = inPos;

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
