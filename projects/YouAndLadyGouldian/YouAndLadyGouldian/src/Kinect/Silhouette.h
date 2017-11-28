#pragma once

#include "ofMain.h"
#include "HE_DepthLessBkgndImage.h"

#include "HEHelpers_Shader.h"

class HEKinect;

class Silhouette
{
public:
    Silhouette(HEKinect* inKinect);
    ~Silhouette();

public:
    void update();
    void render();
    void renderStreamImage();
    void renderBkgnd();

public:
    void refreshBackground();

private:
    HEKinectDepthImage mStreamImage;
    HEDepthLessBkgndImage mDepthLessBkgndImage;

private:
    HEShaderHelper mSilhouetteShader;
    ofImage mPixelCanvas;
};
 