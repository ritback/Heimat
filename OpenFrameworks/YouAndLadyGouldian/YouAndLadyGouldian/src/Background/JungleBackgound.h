#pragma once

#include "ofMain.h"

#include "HEHelpers_Shader.h"

class HEKinect;

class JungleBackgound
{
public:
    JungleBackgound();
    ~JungleBackgound();

public:
    void update();
    void render();

private:
    ofImage mJungleImage;
    HEShaderHelper mHeatShader;
    ofImage mPixelCanvas;
};
 