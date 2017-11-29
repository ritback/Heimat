#pragma once

#include "ofMain.h"
#include "HEHelpers_Shader.h"

class HEKinect;

class Trees
{
public:
    Trees();
    ~Trees();

public:
    void update();
    void render();

private:
    HEShaderHelper mTreesShader;
    ofImage mPixelCanvas;
};
 