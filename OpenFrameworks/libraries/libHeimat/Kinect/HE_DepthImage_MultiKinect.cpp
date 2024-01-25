#include "HE_DepthImage_MultiKinect.h"

HEDepthImageMultiKinect::HEDepthImageMultiKinect(std::vector<HEKinect*>* inKinects, bool inVertical)
    : HEDepthImageMultiKinect(inKinects, ofPoint(0, 0), ofGetWindowSize(), inVertical)
{

}

HEDepthImageMultiKinect::HEDepthImageMultiKinect(std::vector<HEKinect*>* inKinects,
                                             const ofPoint& inTopLeft,
                                             const ofPoint& inSize,
                                             bool inVertical)
    : mKinects(inKinects)
    , mSize(inSize)
    , mTopLeft(inTopLeft)
    , mDepthImages()
    , mIsVertical(inVertical)
{
    ofPoint singleDepthImageSize = ofPoint(0, 0);
    for(int i = 0; i < mKinects->size(); ++i)
    {
        mDepthImages.push_back(new HEKinectDepthImage((*mKinects)[i], ofPoint(0, 0), ofPoint(0, 0)));

        ofPoint channelSizeI = ((*mKinects)[i]->getStreamHandler())->getStreamResolution();

        if(mIsVertical)
        {
            if(channelSizeI.x > singleDepthImageSize.x)
            {
                singleDepthImageSize.x = channelSizeI.x;
            }
            singleDepthImageSize.y += channelSizeI.y;
        }
        else
        {
            singleDepthImageSize.x += channelSizeI.x;
            if(channelSizeI.y > singleDepthImageSize.y)
            {
                singleDepthImageSize.y = channelSizeI.y;
            }
        }
    }

    mSingleDepthChannel.allocate(singleDepthImageSize.x, singleDepthImageSize.y, OF_PIXELS_GRAY);
    mSingleDepthImage.allocate(singleDepthImageSize.x, singleDepthImageSize.y);
}

HEDepthImageMultiKinect::~HEDepthImageMultiKinect()
{
    for(int i = 0; i < mDepthImages.size(); ++i)
    {
        delete mDepthImages[i];
        mDepthImages[i] = 0;
    }
}

// -----------------------------------------------------------------------------
void HEDepthImageMultiKinect::update()
{
    for(int i = 0; i < mDepthImages.size(); ++i)
    {
        mDepthImages[i]->update();
        updateImage(i);
    }
    updateSingleDepthImage();
}

void HEDepthImageMultiKinect::updateImage(int inImageIndex)
{

}

// -----------------------------------------------------------------------------
void HEDepthImageMultiKinect::render()
{
    mSingleDepthImage.draw(mTopLeft.x, mTopLeft.y,
                           mSize.x, mSize.y);
}

void HEDepthImageMultiKinect::render(const ofPoint& inTopLeft,
                                   const ofPoint& inSize)
{
    mSingleDepthImage.draw(inTopLeft.x, inTopLeft.y,
                           inSize.x, inSize.y);
}

// -----------------------------------------------------------------------------
void HEDepthImageMultiKinect::resize(ofPoint inSize)
{
    mSize = inSize;
}

ofPoint HEDepthImageMultiKinect::getSize()
{
    return mSize;
}

void HEDepthImageMultiKinect::setTopLeft(ofPoint inTopLeft)
{
    mTopLeft = inTopLeft;
}

ofPoint HEDepthImageMultiKinect::getTopLeft()
{
    return mTopLeft;
}

// -----------------------------------------------------------------------------
void HEDepthImageMultiKinect::updateSingleDepthImage()
{
    int currentIndexX = 0;
    int currentIndexY = 0;
    for(int i = 0; i < mDepthImages.size(); ++i)
    {
        ofPixels depthImages = (mDepthImages[i]->mDepthChannel);

        if(mIsVertical)
        {
            depthImages.pasteInto(mSingleDepthChannel, currentIndexX, currentIndexY);
            currentIndexY += depthImages.getHeight();
        }
        else
        {
            depthImages.pasteInto(mSingleDepthChannel, currentIndexX, currentIndexY);
            currentIndexX += depthImages.getWidth();
        }
    }

    mSingleDepthImage.setFromPixels(mSingleDepthChannel);

}


// -----------------------------------------------------------------------------
HEDepthImageMultiKinectRotated::HEDepthImageMultiKinectRotated(std::vector<HEKinect*>* inKinects,
                                                           bool inVertical)
    : HEDepthImageMultiKinect(inKinects, inVertical)
{

}

HEDepthImageMultiKinectRotated:: ~HEDepthImageMultiKinectRotated()
{

}


// -----------------------------------------------------------------------------
void HEDepthImageMultiKinectRotated::updateImage(int inImageIndex)
{
    if (inImageIndex % 2 != 0) // reverse all impair index (kinect 2 / 4 / 6)...
    {
        ((mDepthImages[inImageIndex])->mDepthChannel).mirror(true, true);
    }
}