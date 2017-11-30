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

}

void Tree::render()
{

    mTreeShader.begin();

    ofPoint sResolution = ofGetWindowSize();
    float pRes[3] = {sResolution.x, sResolution.y, 0};
    mTreeShader.setUniform3fv("uResolution", pRes, 1);

    mTreeShader.setUniform1f("uGlobalTime", ofGetElapsedTimef());

    float pScreenPos[3] = {mPos.x, mPos.y, mPos.z};
    mTreeShader.setUniform3fv("uScreenPos", pScreenPos, 1);
    float pTreeSize[3] = {mSize.x, mSize.y, mSize.z};
    mTreeShader.setUniform3fv("uTreeSize", pTreeSize, 1);


    mPixelCanvas.draw(0, 0, ofGetWidth(), ofGetHeight());

    mTreeShader.end();
}
