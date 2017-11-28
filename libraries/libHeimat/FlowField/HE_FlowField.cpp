#include "HE_FlowField.h"

HEFlowField::HEFlowField()
: mFboDrawn(false)
, mFbo()
, mFboPixels()
, mShader("Noises")
, mPixelCanvas()
{
    resizeFboAndCanvas(ofGetWidth(), ofGetHeight());
}

HEFlowField::~HEFlowField()
{
    
}


// -----------------------------------------------------------------------------



void HEFlowField::drawFboFlowField()
{
    mFbo.begin();
    drawNoise();
    mFbo.end();
    
    mFbo.readToPixels(mFboPixels);
    
    mFboDrawn = true;
}

// -----------------------------------------------------------------------------
void HEFlowField::drawNoise()
{
    mShader.begin();
    
    ofPoint sResolution = ofGetWindowSize();
    float pRes[3] = { sResolution.x, sResolution.y, 0 };
    mShader.setUniform3fv("uResolution", pRes, 1);
    
    mShader.setUniform1f("uGlobalTime", ofGetElapsedTimef());
    
    
    float pMouse[4] = { (float) ofGetMouseX(), (float) ofGetMouseY(),
        0, (float) ofGetMousePressed() };
    mShader.setUniform4fv("uMouse", pMouse, 1);
    
    
    mPixelCanvas.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    mShader.end();
}

void HEFlowField::drawField()
{
    float gridScale = 0.05;
    
    ofImage fboImage;
    fboImage.setFromPixels(mFboPixels);
    fboImage.draw(0, 0);
    
    ofPoint gridStepSize = ofGetWindowSize() * gridScale;
    int numCol = (int)(ofGetWindowWidth() / gridStepSize.x) + 1;
    int numLine = (int)(ofGetWindowHeight() / gridStepSize.y) + 1;
    
    for (int col = 0; col < numCol; ++col)
    {
        for (int line = 0; line < numLine; ++line)
        {
            
            int index = mFboPixels.getPixelIndex(col*gridStepSize.x + 1,
                                                 line * gridStepSize.y + 1);
            float angleDeg = (float)mFboPixels[index];
            angleDeg = scalingMap<float>(angleDeg, 0.0, 255.0, -190.0, 190.0);
            ofPushStyle();
            ofPushMatrix();
            
            ofTranslate(col*gridStepSize.x, line*gridStepSize.y);
            ofRotate(angleDeg);
            
            ofSetColor(255, 0,  0, 200);
            ofSetLineWidth(2);
            ofDrawLine(0, 0, gridStepSize.y, 0);
            
            ofPopMatrix();
            ofPopStyle();
        }
    }
}


// -----------------------------------------------------------------------------
float HEFlowField::getFlowFieldDirection(const ofPoint& inPos)
{
    ofPoint pos = inPos;
    
    if (inPos.x <= 0)
        pos.x = 0;
    else if (inPos.x >= mFboPixels.getWidth() - 10)
        pos.x = mFboPixels.getWidth() - 10; // patch buggy image ?
    
    if (inPos.y <= 0)
        pos.y = 0;
    else if (inPos.y >= mFboPixels.getHeight())
        pos.y = mFboPixels.getHeight() - 1;
        
    
    int index = mFboPixels.getPixelIndex(pos.x, pos.y);
    float angleDeg = (float)mFboPixels[index];
    angleDeg = scalingMap<float>(angleDeg, 0.0, 255.0, -190.0, 190.0);
    return angleDeg;
}

ofPoint HEFlowField::getForceFieldForce(const ofPoint& inPos, float inForceMag)
{
    float flowFieldDir = getFlowFieldDirection(inPos);
    
    ofPoint flowFieldForce(0, 0);
    flowFieldForce.x = inForceMag * cos(PI / 180.0 * flowFieldDir);
    flowFieldForce.y = inForceMag * sin(PI / 180.0 * flowFieldDir);
    
    
    return flowFieldForce;
}

// -----------------------------------------------------------------------------
void HEFlowField::resize(int w, int h)
{
    resizeFboAndCanvas(w, h);
}

// -----------------------------------------------------------------------------
void HEFlowField::resizeFboAndCanvas(int w, int h)
{
    //w += 200;
    //h += 200;
    
    mPixelCanvas.allocate(w, h, OF_IMAGE_GRAYSCALE);
    
    mFbo.allocate(w, h);
    
    ofFbo::Settings fboSettings;
    
    fboSettings.width = w;           // width of images attached to fbo
    fboSettings.height = h;         // height of images attached to fbo
    fboSettings.textureTarget = GL_TEXTURE_2D;  // GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE_ARB
    fboSettings.internalformat = GL_RGBA;       // GL_RGBA, GL_RGBA16F_ARB, GL_RGBA32F_ARB
    
    mFbo.allocate(fboSettings);
    
    mFbo.setUseTexture(true);
    mFbo.begin();
    ofClear(0, 0, 0, 255);
    mFbo.end();
    
    mFboPixels.allocate(w, h, OF_PIXELS_RGBA);
    
}
