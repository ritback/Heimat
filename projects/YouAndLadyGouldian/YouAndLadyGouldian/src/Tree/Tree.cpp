#include "Tree.h"

Tree::Tree()
    : mPos(ofGetWindowHeight() / 2, ofGetWindowWidth() / 2)
    , mSize(ofGetWindowHeight()/2, ofGetWindowWidth()/2)
    , mTreeShader("Tree")
{
    mPixelCanvas.allocate(mSize.x, mSize.y, OF_IMAGE_COLOR);
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

    ofPoint sResolution = ofGetWindowSize();
    float pRes[3] = {sResolution.x, sResolution.y, 0};
    mTreeShader.setUniform3fv("uResolution", pRes, 1);

    mTreeShader.setUniform1f("uGlobalTime", ofGetElapsedTimef());

    mTreeShader.setUniform1f("uAlpha", mAlpha);

    float pOnScreenPos[3] = {mPos.x, mPos.y, mPos.z};
    mTreeShader.setUniform3fv("uOnScreenPos", pOnScreenPos, 1);
    float pTreeSize[3] = {mSize.x, mSize.y, mSize.z};
    mTreeShader.setUniform3fv("uTreeSize", pTreeSize, 1);
    float pMousePos[3] = {(float)ofGetMouseX(), (float)ofGetMouseY(), 0};
    mTreeShader.setUniform3fv("uMouse", pMousePos, 1);

    
    //mPixelCanvas.draw(mPos.x - mSize.x/2, ofGetWindowHeight() - mSize.y, mSize.x, mSize.y);

    mPixelCanvas.draw(0, 0, ofGetWidth(), ofGetHeight());

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
