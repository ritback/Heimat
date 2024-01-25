#include "HE_KinectDepthImage.h"


HEKinectDepthImage::HEKinectDepthImage(HEKinect* inKinect)
    : HEKinectDepthImage(inKinect, ofPoint(0, 0), ofGetWindowSize())
{

}

HEKinectDepthImage::HEKinectDepthImage(HEKinect* inKinect,
                       const ofPoint& inTopLeft,
                       const ofPoint& inSize)
    : HEDepthStreamHandlerInterface()
    , mDepthChannel()
    , mDepthImage()
    , mSize(inSize)
    , mTopLeft(inTopLeft)
    , mKinect(inKinect)
{
    ofPoint channelSize = (mKinect->getStreamHandler())->getStreamResolution();
    mDepthChannel.allocate(channelSize.x, channelSize.y, OF_PIXELS_GRAY);

    mDepthImage.allocate(mDepthChannel.getWidth(),
                         mDepthChannel.getHeight());
}

HEKinectDepthImage::~HEKinectDepthImage()
{

}

// -----------------------------------------------------------------------------
void HEKinectDepthImage::update()
{
    updateDepthChannel();
    updateImage(mDepthChannel);
    additionnalUpdates();
}

void HEKinectDepthImage::render()
{
    mDepthImage.draw(mTopLeft.x, mTopLeft.y,
                     mSize.x, mSize.y);
}

void HEKinectDepthImage::render(const ofPoint& inTopLeft,
                        const ofPoint& inSize)
{
    mDepthImage.draw(inTopLeft.x, inTopLeft.y,
                     inSize.x, inSize.y);
}

// -----------------------------------------------------------------------------
void HEKinectDepthImage::resize(ofPoint inSize)
{
    mSize = inSize;
}

ofPoint HEKinectDepthImage::getSize()
{
    return mSize;
}

void HEKinectDepthImage::setTopLeft(ofPoint inTopLeft)
{
    mTopLeft = inTopLeft;
}

ofPoint HEKinectDepthImage::getTopLeft()
{
    return mTopLeft;
}

// -----------------------------------------------------------------------------
void HEKinectDepthImage::additionnalUpdates()
{

}

// -----------------------------------------------------------------------------
void HEKinectDepthImage::updateDepthChannel()
{
    HEKinectStreamHandler* stream = mKinect->getStreamHandler();
    stream->streamDepthTo(this, &mDepthChannel, 1);
}

void HEKinectDepthImage::updateImage(ofPixels& inPixels)
{
    mDepthImage.setFromPixels(inPixels);
}

// -----------------------------------------------------------------------------
void HEKinectDepthImage::setPixel(ofPixels* inDepthChannel,
                          int inPixelIndex,
                          unsigned char inKinectGreyLevel)
{
    (*inDepthChannel)[inPixelIndex] = inKinectGreyLevel;
}


