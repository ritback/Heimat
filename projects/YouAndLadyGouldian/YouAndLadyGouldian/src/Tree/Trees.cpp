#include "Silhouette.h"
#include "Kinect.h"

Silhouette::Silhouette(HEKinect* inKinect)
    : mStreamImage(inKinect,
                  ofPoint(0, 0),
                  ofPoint(ofGetWindowWidth(), ofGetWindowHeight()))
    , mDepthLessBkgndImage(&(mStreamImage.mDepthImage))
    , mSilhouetteShader("Silhouette")
{
    ofPoint size = mStreamImage.getSize();
    mPixelCanvas.allocate(size.x, size.y, OF_IMAGE_GRAYSCALE);

    mDepthLessBkgndImage.refreshBackgroungNeeded();
}

Silhouette::~Silhouette()
{

}

//------------------------------------------------------------------------------
void Silhouette::update()
{
    mStreamImage.update();
    mDepthLessBkgndImage.update();
}

void Silhouette::render()
{
    mDepthLessBkgndImage.render(ofPoint(0, 0), ofGetWindowSize());
    //renderStreamImage();


    /*
    mSilhouetteShader.begin();

    ofPoint sResolution = ofGetWindowSize();
    float pRes[3] = {sResolution.x, sResolution.y, 0};
    mSilhouetteShader.setUniform3fv("uResolution", pRes, 1);

    mSilhouetteShader.setUniform1f("uGlobalTime", ofGetElapsedTimef());

    //mSilhouetteShader.setUniform1f("uColorChangeSpeed", mBlinkingColorParameters.mColorChangeSpeed);
    

    mPixelCanvas.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

    mSilhouetteShader.end();
    */
}

void Silhouette::renderStreamImage()
{
    mStreamImage.render(ofPoint(0, 0), ofGetWindowSize());
}

void Silhouette::renderBkgnd()
{
    mDepthLessBkgndImage.renderBkgnd(ofPoint(0, 0), ofGetWindowSize());
}

//------------------------------------------------------------------------------
void Silhouette::refreshBackground()
{
    mDepthLessBkgndImage.refreshBackgroungNeeded();
}
