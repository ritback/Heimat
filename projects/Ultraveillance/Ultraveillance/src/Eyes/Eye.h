#pragma once

#include "ofMain.h"

class Eye 
{
public:
	Eye(float inX, float inY, float inWidth, float inHeight);
	virtual ~Eye();

public:
	virtual void render();
	virtual void update();
    
public:
    void stareAt(float inToX, float inToY);
    
public:
    void setPos(const ofPoint& inPos);
    void setSize(const ofPoint& inSize);
    const ofPoint& getPos();
    const ofPoint& getSize();

protected:
    void drawEyeBack();
    void drawIris();

protected:
    void createEyeBackShape();
    void createIrisShape();

protected:
    ofPoint mPos;
    ofPoint mSize;
    
protected:
    ofPoint mIrisPos;
    float mIrisRadius;

protected:
    ofTexture mIrisTexture;
    ofFbo mIrisAlphaMaskFBO;

protected:
    ofPath mEyeContour;
    ofPath mEyeContourMask;
    bool bNeedRefreshMask;

protected:
    ofPoint mEyeCornerLeft;
    ofPoint mEyeCornerRight;
    ofPoint cpCornerUpLeft;
    ofPoint cpCornerUpRight;
    ofPoint cpCornerDownLeft;
    ofPoint cpCornerDownRight;

protected:
    ofColor mBackColor;
    ofColor mIrisColor;
};


/** NOTE ON RENDERING AND SCALINGS:
* Every the position of the eye is centered => mPosX/Y are the center of the eyes.
* Everything is scale at rendering => the shape are build with a width and height of 1.
*/
