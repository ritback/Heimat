#include "Eye.h"

Eye::Eye(float inX, float inY, float inWidth, float inHeight)
    : mPos(inX, inY)
    , mSize(inWidth, inHeight)
    , mIrisRadius(0.25f)
    , mIrisPos(0, 0)
    , mBackColor(100, 100, 100, 0)
    , bNeedRefreshMask(false)
{
    createEyeBackShape();
    createIrisShape();

    mIrisTexture.allocate(mSize.x, mSize.y, GL_RGBA);
    mIrisAlphaMaskFBO.allocate(mSize.x, mSize.y, GL_RGBA);
}

Eye::~Eye()
{

}

// -----------------------------------------------------------------------------
void Eye::render()
{
    ofPushMatrix();
    ofTranslate(mPos.x, mPos.y);
    ofScale(mSize);

    drawEyeBack();
    drawIris();
    
    ofPopMatrix();
}

void Eye::update()
{
    if (bNeedRefreshMask)
    {
        mIrisTexture.allocate(mSize.x, mSize.y, GL_RGBA);
        mIrisAlphaMaskFBO.allocate(mSize.x, mSize.y, GL_RGBA);
        bNeedRefreshMask = false;
    }
}

// -----------------------------------------------------------------------------
void Eye::stareAt(float inToX, float inToY)
{
    // position relative to the eye.
    float inRelativePosX = inToX - mPos.x;
    float inRelativePosY = inToY - mPos.y;
    // need to be scale to 1.
    mIrisPos.x = inRelativePosX * 1 / ofGetWindowWidth();
    mIrisPos.y = inRelativePosY * 1 / ofGetWindowHeight();

    // limit 
    float sqrIrisDist = mIrisPos.lengthSquared();
    float restrictedRadius = 0.5f - mIrisRadius; // limit is (height - the iris radius)
    if (sqrIrisDist > (restrictedRadius*restrictedRadius))
    {
        mIrisPos.normalize();
        mIrisPos *= restrictedRadius;
    }
}

// -----------------------------------------------------------------------------
void Eye::setPos(const ofPoint& inPos)
{
    mPos = inPos;
}

void Eye::setSize(const ofPoint& inSize)
{
    bNeedRefreshMask = true;
    mSize = inSize;
}

const ofPoint& Eye::getPos()
{
    return mPos;
}

const ofPoint& Eye::getSize()
{
    return mSize;
}



// -----------------------------------------------------------------------------
/** NOTE ON RENDERING AND SCALINGS:
* Every the position of the eye is centered => mPosX/Y are the center of the eyes.
* Everything is scale at rendering => the shape are build with a width and height of 1.
*/
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Eye::drawEyeBack()
{
    mEyeContour.draw();
}

void Eye::drawIris()
{
    // Draw alpha mask.
    mIrisAlphaMaskFBO.begin();
    ofPushMatrix();
    ofClear(0, 0, 0, 0);

    ofTranslate(mSize / 2);

    ofSetColor(255);
    ofDrawCircle(mIrisPos * mSize, mIrisRadius * mSize.y);

    ofScale(mSize);

    mEyeContourMask.draw();

    ofPopMatrix();
    mIrisAlphaMaskFBO.end();

    mIrisTexture.setAlphaMask(mIrisAlphaMaskFBO.getTexture());
    
    // Draw resulting Texture masked.
    ofPushStyle();
    ofSetColor(0);
    mIrisTexture.draw(-0.5f, -0.5f, 1.f, 1.f);
    ofPopStyle();
}

// -----------------------------------------------------------------------------
void Eye::createEyeBackShape()
{
    mEyeContour.clear();

    mEyeCornerLeft = ofPoint(-0.5f, 0);
    mEyeCornerRight = ofPoint(0.5f, 0);

    float factor = 5.f / 8;

    // Eye contour up
    mEyeContour.moveTo(mEyeCornerLeft); // begin left
    cpCornerUpLeft = ofPoint(-0.25f, -1 * factor);
    cpCornerUpRight = ofPoint(0.25f, -1 * factor);
    mEyeContour.bezierTo(cpCornerUpLeft, cpCornerUpRight, mEyeCornerRight);

    // Eye contour down
    cpCornerDownRight = ofPoint(0.25f, 1 * factor);
    cpCornerDownLeft = ofPoint(-0.25f, 1 * factor);
    mEyeContour.bezierTo(cpCornerDownRight, cpCornerDownLeft, mEyeCornerLeft);

    mEyeContour.close();

    mEyeContour.setFillColor(mBackColor);
    mEyeContour.setStrokeColor(ofColor(0, 0, 0));
    mEyeContour.setStrokeWidth(1.f);
}

void Eye::createIrisShape()
{
    mEyeContourMask.clear();

    // create AlphaMask
    mEyeContourMask = ofPath(mEyeContour);
    mEyeContourMask.setFillColor(ofColor(0));
    mEyeContourMask.rectangle(-1.f, -1.f, 1.f * 2, 1.f * 2);
}

