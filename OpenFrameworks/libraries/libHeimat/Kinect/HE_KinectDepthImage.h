#pragma once

#include "HE_KinectDef.h"
#include "HE_Kinect.h"
#include "ofxOpenCv.h"

class HEKinectDepthImage : public HEDepthStreamHandlerInterface
{
public:
    HEKinectDepthImage(HEKinect* inKinect);
	HEKinectDepthImage(HEKinect* inKinect,
			   const ofPoint& inTopLeft,
			   const ofPoint& inSize);
	virtual ~HEKinectDepthImage();

public:
	virtual void update();
	virtual void render();
    virtual void render(const ofPoint& inTopLeft,
                        const ofPoint& inSize);

public:
	void resize(ofPoint inSize);
	ofPoint getSize();
	void setTopLeft(ofPoint inTopLeft);
	ofPoint getTopLeft();

protected:
	virtual void additionnalUpdates();

protected:
    void updateDepthChannel();
    virtual void updateImage(ofPixels& inPixels);

protected:
	virtual void setPixel(ofPixels* inDepthChannel,
						  int inPixelIndex,
						  unsigned char inKinectGreyLevel) override;

public:
	ofPixels mDepthChannel;
    ofxCvGrayscaleImage mDepthImage;

protected:
	ofPoint mSize;
	ofPoint mTopLeft;

protected:
	HEKinect* mKinect;
};
