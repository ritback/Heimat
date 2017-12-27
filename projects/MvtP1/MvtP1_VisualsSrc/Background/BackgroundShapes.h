#pragma once

#include "ofMain.h"

#include "HEHelpers_Shader.h"


#include "BackgroundShapesParameters.h"

class BackgroundShapes
{
public:
    BackgroundShapes();
    virtual ~BackgroundShapes();
    
public:
    void updateParameters(const BlobsParameters& inParameters);
    void updateParameters(const SandParameters& inParameters);
    void updateParameters(const BlinkingColorParameters& inParameters);
    
public:
    void drawShader();
    
private:
    void drawBlobsShader();
    void drawSandShader();
    void drawBlinkingColorShader();
    
private:
    HEShaderHelper mBlobsShader;
    HEShaderHelper mSandShader;
    HEShaderHelper mBlinkingColorShader;
    ofImage mPixelCanvas;
    
private:
    BlobsParameters mBlobsParameters;
    SandParameters mSandParameters;
    BlinkingColorParameters mBlinkingColorParameters;
    
		
};
