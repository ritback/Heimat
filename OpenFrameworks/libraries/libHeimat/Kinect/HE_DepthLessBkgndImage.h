#pragma once

#include "HE_KinectDef.h"
#include "HE_KinectDepthImage.h"

class HEDepthLessBkgndImage
{
public:
    HEDepthLessBkgndImage(ofxCvGrayscaleImage* inStreamImage);
    HEDepthLessBkgndImage(ofxCvGrayscaleImage* inStreamImage,
                        const ofPoint& inTopLeft,
                        const ofPoint& inSize);
	virtual ~HEDepthLessBkgndImage();

public:
	virtual void update();
    virtual void render();
    virtual void render(const ofPoint& inTopLeft,
                        const ofPoint& inSize);
	void renderBkgnd();
    void renderBkgnd(const ofPoint& inTopLeft,
                     const ofPoint& inSize);

public:
	void refreshBackgroungNeeded();

public:
	void setThreshold(float inThreshold);
	float getThreshold();
	void setBlur(float inBlur);
	float getBlur();

public:
    void resize(ofPoint inSize);
    ofPoint getSize();
    void setTopLeft(ofPoint inTopLeft);
    ofPoint getTopLeft();

public:
	ofxCvGrayscaleImage mDepthLessBkgndImage;
	ofxCvGrayscaleImage mBkgndDepthImage;

protected:
    ofxCvGrayscaleImage* mStreamImage;

protected:
    ofPoint mSize;
    ofPoint mTopLeft;

protected:
	float mThreshold;
	float mBlur;
	bool mNeedRefresh;
};

