#include "HE_DepthLessBkgndImage.h"


HEDepthLessBkgndImage::HEDepthLessBkgndImage(ofxCvGrayscaleImage* inStreamImage)
    : HEDepthLessBkgndImage(inStreamImage, ofPoint(0, 0), ofGetWindowSize())
{

}


HEDepthLessBkgndImage::HEDepthLessBkgndImage(ofxCvGrayscaleImage* inStreamImage,
											 const ofPoint& inTopLeft,
											 const ofPoint& inSize)
	: mStreamImage(inStreamImage)
	, mThreshold(20)
	, mBlur(33)
    , mTopLeft(inTopLeft)
    , mSize(inSize)
{
	mBkgndDepthImage.allocate(mStreamImage->getWidth(),
                              mStreamImage->getHeight());
	mDepthLessBkgndImage.allocate(mStreamImage->getWidth(),
                                  mStreamImage->getHeight());
}

HEDepthLessBkgndImage::~HEDepthLessBkgndImage()
{

}

// -----------------------------------------------------------------------------
void HEDepthLessBkgndImage::update()
{
    if(mNeedRefresh)
    {
        mBkgndDepthImage = *mStreamImage;
        mNeedRefresh = false;
    }

    mDepthLessBkgndImage.absDiff(*mStreamImage, mBkgndDepthImage);

    if(mBlur > 0)
        mDepthLessBkgndImage.blur(mBlur);
    if(mThreshold > 0)
        mDepthLessBkgndImage.threshold(mThreshold);
}

void HEDepthLessBkgndImage::render()
{
	mDepthLessBkgndImage.draw(mTopLeft.x, mTopLeft.y,
                              mSize.x, mSize.y);
}

void HEDepthLessBkgndImage::render(const ofPoint& inTopLeft,
                                 const ofPoint& inSize)
{
    mDepthLessBkgndImage.draw(inTopLeft.x, inTopLeft.y,
                              inSize.x, inSize.y);
}

void HEDepthLessBkgndImage::renderBkgnd()
{
	mBkgndDepthImage.draw(mTopLeft.x, mTopLeft.y,
						  mSize.x, mSize.y);
}

void HEDepthLessBkgndImage::renderBkgnd(const ofPoint& inTopLeft,
                                 const ofPoint& inSize)
{
    mBkgndDepthImage.draw(inTopLeft.x, inTopLeft.y,
                              inSize.x, inSize.y);
}

// -----------------------------------------------------------------------------
void HEDepthLessBkgndImage::refreshBackgroungNeeded()
{
	mNeedRefresh = true;
}

// -----------------------------------------------------------------------------
void HEDepthLessBkgndImage::setThreshold(float inThreshold)
{
	mThreshold = inThreshold;
}

float HEDepthLessBkgndImage::getThreshold()
{
	return mThreshold;
}

void HEDepthLessBkgndImage::setBlur(float inBlur)
{
	mBlur = inBlur;
}

float HEDepthLessBkgndImage::getBlur()
{
	return mBlur;
}

// -----------------------------------------------------------------------------
void HEDepthLessBkgndImage::resize(ofPoint inSize)
{
    mSize = inSize;
}

ofPoint HEDepthLessBkgndImage::getSize()
{
    return mSize;
}

void HEDepthLessBkgndImage::setTopLeft(ofPoint inTopLeft)
{
    mTopLeft = inTopLeft;
}

ofPoint HEDepthLessBkgndImage::getTopLeft()
{
    return mTopLeft;
}
