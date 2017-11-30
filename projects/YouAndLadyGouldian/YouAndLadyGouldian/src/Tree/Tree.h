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
    ofPoint mPos;
    ofPoint mSize;
    HEShaderHelper mTreeShader;
    ofImage mPixelCanvas;
};
 