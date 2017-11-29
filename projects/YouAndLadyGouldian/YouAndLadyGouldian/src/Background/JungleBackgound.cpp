#include "JungleBackgound.h"

JungleBackgound::JungleBackgound()
    : mJungleImage()
    , mHeatShader("CrossfadingHeat")
{
    if(!mJungleImage.isUsingTexture())
    {
        mJungleImage.setUseTexture(true);
    }
    mJungleImage.loadImage("images/Rousseau_ApesInTheOrangeGrove.jpg");

    mPixelCanvas.allocate(mJungleImage.getWidth(), mJungleImage.getHeight(), OF_IMAGE_COLOR);
}

JungleBackgound::~JungleBackgound()
{

}

//------------------------------------------------------------------------------
void JungleBackgound::update()
{

}

void JungleBackgound::render()
{
    mHeatShader.begin();

    ofPoint sResolution = ofGetWindowSize();
    float pRes[3] = {sResolution.x, sResolution.y, 0};
    mHeatShader.setUniform3fv("uResolution", pRes, 1);

    mHeatShader.setUniform1f("uGlobalTime", ofGetElapsedTimef());

    mHeatShader.setUniformTexture("uBackgroundTexture", mJungleImage.getTexture(), 1);
    float pBackgroundRes[3] = {mJungleImage.getWidth(), mJungleImage.getHeight(), 0};
    mHeatShader.setUniform3fv("uBackgroundTextureRes", pBackgroundRes, 1);


    mPixelCanvas.draw(0, 0, ofGetWidth(), ofGetHeight());

    mHeatShader.end();
}
