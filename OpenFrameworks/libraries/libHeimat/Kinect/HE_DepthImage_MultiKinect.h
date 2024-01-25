#pragma once

#include "HE_KinectDef.h"
#include "HE_Kinect.h"
#include "HE_KinectDepthImage.h"
#include <vector>

class HEDepthImageMultiKinect
{
public:
    HEDepthImageMultiKinect(std::vector<HEKinect*>* inKinects,
                          bool inVertical = true);
    HEDepthImageMultiKinect(std::vector<HEKinect*>* inKinects,
                          const ofPoint& inTopLeft,
                          const ofPoint& inSize,
                          bool inVertical = true);
    virtual ~HEDepthImageMultiKinect();

public:
    virtual void update();
    virtual void updateImage(int inImageIndex); // independently update DepthImage  before it's being added in the global image
    virtual void render();
    virtual void render(const ofPoint& inTopLeft,
                        const ofPoint& inSize);

public:
    void resize(ofPoint inSize);
    ofPoint getSize();
    void setTopLeft(ofPoint inTopLeft);
    ofPoint getTopLeft();

protected:
    virtual void updateSingleDepthImage();

protected:
    ofPoint mSize;
    ofPoint mTopLeft;

protected:
    std::vector<HEKinect*>* mKinects;
    std::vector<HEKinectDepthImage*> mDepthImages;

public:
    ofxCvGrayscaleImage mSingleDepthImage;
    ofPixels mSingleDepthChannel;

private:
    bool mIsVertical;
};

//--------------------------------------------------------------

// One on two Image is rotated. This help handle kinects that are one on top of each other
class HEDepthImageMultiKinectRotated : public HEDepthImageMultiKinect
{
public:
    HEDepthImageMultiKinectRotated(std::vector<HEKinect*>* inKinects,
                                 bool inVertical = true);
    virtual ~HEDepthImageMultiKinectRotated();

public:
    virtual void updateImage(int inImageIndex) override;
    
};


