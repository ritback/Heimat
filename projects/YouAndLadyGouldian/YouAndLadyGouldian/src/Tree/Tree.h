#pragma once

#include "ofMain.h"

#include "HEHelpers_Shader.h"

class HEKinect;

class Tree
{
public:
    Tree();
    ~Tree();

public:
    void update();
    void render();


private:
    HEShaderHelper mTreeShader;
    ofImage mPixelCanvas;
};
 