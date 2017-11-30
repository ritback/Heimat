#include "Silhouette.h"
#include "Kinect.h"

Silhouette::Silhouette(HEKinect* inKinect)
    : mStreamImage(inKinect,
                  ofPoint(0, 0),
                  ofPoint(ofGetWindowWidth(), ofGetWindowHeight()))
    , mDepthLessBkgndImage(&(mStreamImage.mDepthImage))
    , mSilhouetteShader("Silhouette")
{
    if(!mDepthLessBkgndImage.mBkgndDepthImage.isUsingTexture())
    {
        mDepthLessBkgndImage.mBkgndDepthImage.setUseTexture(true);
    }
    ofPoint size;
    size.x = mStreamImage.mDepthImage.getWidth();
    size.y = mStreamImage.mDepthImage.getHeight();
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
    mDepthLessBkgndImage.mDepthLessBkgndImage.updateTexture();
}

void Silhouette::render()
{
    mSilhouetteShader.begin();

    ofPoint sResolution = ofGetWindowSize();
    float pRes[3] = {sResolution.x, sResolution.y, 0};
    mSilhouetteShader.setUniform3fv("uResolution", pRes, 1);

    mSilhouetteShader.setUniform1f("uGlobalTime", ofGetElapsedTimef());

    ofTexture* silhouetteText = &mDepthLessBkgndImage.mDepthLessBkgndImage.getTexture();
    mSilhouetteShader.setUniformTexture("uSilhouetteTexture", *silhouetteText, 1);
    float pBackgroundRes[3] = {silhouetteText->getWidth(), silhouetteText->getHeight(), 0};
    mSilhouetteShader.setUniform3fv("uSilhouetteTextureRes", pBackgroundRes, 1);


    mPixelCanvas.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

    mSilhouetteShader.end();

}

void Silhouette::renderStreamImage()
{
    mStreamImage.render(ofPoint(0, 0), ofGetWindowSize());
}

void Silhouette::renderDepthLessBkgnd()
{
    mDepthLessBkgndImage.render(ofPoint(0, 0), ofGetWindowSize());
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
