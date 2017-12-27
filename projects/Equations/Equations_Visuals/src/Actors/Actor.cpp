#include "Actor.h"

#include "HEHelpers_Maths.h"

ofImage Actor::mDrawnFront[Actor::NUM_IMAGES];
ofImage Actor::mDrawnFrontSide[Actor::NUM_IMAGES];
ofImage Actor::mDrawnSide[Actor::NUM_IMAGES];
ofImage Actor::mDrawnBehindSide[Actor::NUM_IMAGES];
ofImage Actor::mDrawnBehind[Actor::NUM_IMAGES];


// -----------------------------------------------------------------------------
Actor::Actor(const ofPoint& inPos)
    : HEBoid(inPos)
    , mNeighborsBoids()
    , mMinimalSqrDistances()
    , mImagesWidth(0)
    , mImagesHeight(0)
    , mImagesPos(0)
    , mCurrentImgIndex(floor(ofRandom(0, 3.99999)))
    , mFrameCounterImgChange(0)
    , mNextImgChange(0)
{
    // Flock
    /*
    mCohesionInfluenceFactor = 1;
    mSeparationInfluenceFactor = 1;
    mAlignmentInfluenceFactor = 1;

    mCohesionDistance = ofRandom(100, 200);
    mSeparationDistance = ofRandom(50, 100);
    mAlignmentDistance = ofRandom(100, 200);

    mCohesionForceScale = ofRandom(10, 12);
    mSeparationForceScale = ofRandom(12, 13);
    mAlignmentForceScale = ofRandom(7, 10);
    */

    // lines
    mMinimalSqrDistances[0] = 1000000000000;
    for (int i = 1; i < NUM_LINK; ++i)
    {
        mMinimalSqrDistances[i] = mMinimalSqrDistances[0] + i;
    }

    // imgs

    static bool areImageLoaded = false;
    if (!areImageLoaded)
    {
        areImageLoaded = true;
        for (int i = 0; i < NUM_IMAGES; ++i)
        {
            stringstream sImgFilePath;
            sImgFilePath << "DrawnImg/Drawn_Front" << i + 1 << ".png";
            mDrawnFront[i].load(sImgFilePath.str());
        }
        for (int i = 0; i < NUM_IMAGES; ++i)
        {
            stringstream sImgFilePath;
            sImgFilePath << "DrawnImg/Drawn_FrontSide" << i + 1 << ".png";
            mDrawnFrontSide[i].load(sImgFilePath.str());
        }
        for (int i = 0; i < NUM_IMAGES; ++i)
        {
            stringstream sImgFilePath;
            sImgFilePath << "DrawnImg/Drawn_Side" << i + 1 << ".png";
            mDrawnSide[i].load(sImgFilePath.str());
        }
        for (int i = 0; i < NUM_IMAGES; ++i)
        {
            stringstream sImgFilePath;
            sImgFilePath << "DrawnImg/Drawn_BehindSide" << i + 1 << ".png";
            mDrawnBehindSide[i].load(sImgFilePath.str());
        }
        for (int i = 0; i < NUM_IMAGES; ++i)
        {
            stringstream sImgFilePath;
            sImgFilePath << "DrawnImg/Drawn_Behind" << i + 1 << ".png";
            mDrawnBehind[i].load(sImgFilePath.str());
        }
    }

    mImagesWidth = mDrawnFront[0].getWidth() / ofRandom(4, 6);
    mImagesHeight = mDrawnFront[0].getHeight() / ofRandom(4, 6);
    mImagesPos = ofPoint(-mImagesWidth / 2, -mImagesHeight * 5 / 8, 0);
}

Actor::~Actor()
{

}

// -----------------------------------------------------------------------------
void Actor::render()
{
    drawLines();

    ofPushMatrix();
    ofTranslate(mPos);
    float heading = heading2D(mVel);
    if (heading < -90 || heading > 90)
    {
        ofScale(-1, 1, 1);
    }
    ofRotate(45, 1, 0, 0);


    ofColor charColor(255);
    drawCharacter(charColor, heading);

    ofPopMatrix();

    /*
    ofPushStyle();
    ofNoFill();

    ofSetColor(255, 0, 0, 100);
    ofDrawCircle(mPos, mCohesionDistance);

    ofSetColor(0, 255, 0, 100);
    ofDrawCircle(mPos, mSeparationDistance);

    ofSetColor(0, 0, 255, 100);
    ofDrawCircle(mPos, mAlignmentDistance);

    ofPopStyle();
    */
}


// -----------------------------------------------------------------------------
void Actor::drawCharacter(ofColor& inColor, float inHeading)
{
    ofPushStyle();

    ofSetColor(inColor);

    float imgWidth = mDrawnFront[0].getWidth() / 5;
    float imgHeight = mDrawnFront[0].getHeight() / 5;

    ofPoint imgPos = ofPoint(-imgWidth / 2, -imgHeight * 5 / 8, 0);

    if (mFrameCounterImgChange >= mNextImgChange)
    {
        mCurrentImgIndex = (mCurrentImgIndex + 1) % 4;
        mFrameCounterImgChange = 0;
        mNextImgChange = floor(ofRandom(4, 6));
    }
    ++mFrameCounterImgChange;


    // find the correct image corresponding to heading.
    ofImage* drawn = 0;

    if (inHeading >= 67.5 && inHeading <= 112.5)
    {
        drawn = &mDrawnBehind[mCurrentImgIndex];
    }

    else if ((inHeading >= 22.5 && inHeading <= 67.5) ||
             (inHeading >= 112.5 && inHeading <= 157.5))
    {
        drawn = &mDrawnBehindSide[mCurrentImgIndex];
    }

    else if ((inHeading <= 22.5 && inHeading >= -22.5) ||
             (inHeading >= 157.5 || inHeading <= -157.5))
    {
        drawn = &mDrawnSide[mCurrentImgIndex];
    }

    else if ((inHeading <= -22.5 && inHeading >= -67.5) ||
             (inHeading <= -112.5 && inHeading >= -157.5))
    {
        drawn = &mDrawnFrontSide[mCurrentImgIndex];
    }

    else if (inHeading <= -67.5 && inHeading >= -112.5)
    {
        drawn = &mDrawnFront[mCurrentImgIndex];
    }

    // draw correct image
    if (drawn)
    {
        drawn->draw(mImagesPos, mImagesWidth, mImagesHeight);
    }

    ofPopStyle();
}

void Actor::drawLines()
{
    ofPushStyle();
    ofSetColor(80, 80, 80, 100);
    for (int i = 0; i < NUM_LINK; ++i)
    {
        if (mNeighborsBoids[i] != 0)
        {
            mLines[i].render();
        }
    }
    ofPopStyle();
}

// -----------------------------------------------------------------------------
void Actor::otherFlockingInteraction(HEBoid* inBoid,
                                     float inBoidSqrDistance)
{
    for (int i = 0; i < NUM_LINK; ++i)
    {
        if (inBoidSqrDistance < mMinimalSqrDistances[i])
        {
            mMinimalSqrDistances[i] = inBoidSqrDistance;
            mNeighborsBoids[i] = inBoid;
            return;
        }
    }
}

void Actor::applyOtherFlockingInteraction()
{

    for (int i = 0; i < NUM_LINK; ++i)
    {
        if (mNeighborsBoids[i] != 0)
        {
            ofPoint it = mNeighborsBoids[i]->getPos();
            mLines[i].update(&mPos, &it);
        }
    }

    mMinimalSqrDistances[0] = 1000000000000;
    for (int i = 1; i < NUM_LINK; ++i)
    {
        mMinimalSqrDistances[i] = mMinimalSqrDistances[0] + i;
    }

}

