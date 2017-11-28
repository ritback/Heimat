#include "DrawnPerson.h"

ofImage DrawnPerson::mDrawnFront[DrawnPerson::NUM_IMAGES];
ofImage DrawnPerson::mDrawnFrontSide[DrawnPerson::NUM_IMAGES];
ofImage DrawnPerson::mDrawnSide[DrawnPerson::NUM_IMAGES];
ofImage DrawnPerson::mDrawnBehindSide[DrawnPerson::NUM_IMAGES];
ofImage DrawnPerson::mDrawnBehind[DrawnPerson::NUM_IMAGES];


// -----------------------------------------------------------------------------
DrawnPerson::DrawnPerson(ofPoint inPoint)
: Boid(inPoint)
, mNeighborsBoids()
, mMinimalSqrDistances()
, mImagesWidth(0)
, mImagesHeight(0)
, mImagesPos(0)
, mCurrentImgIndex(floor(ofRandom(0, 3.99999)))
, mFrameCounterImgChange(0)
, mNextImgChange(0)
{
    init();
}

DrawnPerson::~DrawnPerson()
{
    
}

// -----------------------------------------------------------------------------
void DrawnPerson::init()
{
    
    // Flock
    
    mMaxSteering = 100000.0;
    
    mCohesionInfluenceFactor = 1;
    mSeparationInfluenceFactor = 1;
    mAlignmentInfluenceFactor = 1;
    
    mCohesionDistance = ofRandom(100, 200);
    mSeparationDistance = ofRandom(50, 100);
    mAlignmentDistance = ofRandom(100, 200);
    
    mCohesionForceScale = ofRandom(10, 12);
    mSeparationForceScale = ofRandom(12, 13);
    mAlignmentForceScale = ofRandom(7, 10);
    
    
    
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
            sImgFilePath << "DrawnImg/Drawn_Front" << i+1 << ".png";
            mDrawnFront[i].load(sImgFilePath.str());
        }
        for (int i = 0; i < NUM_IMAGES; ++i)
        {
            stringstream sImgFilePath;
            sImgFilePath << "DrawnImg/Drawn_FrontSide" << i+1 << ".png";
            mDrawnFrontSide[i].load(sImgFilePath.str());
        }
        for (int i = 0; i < NUM_IMAGES; ++i)
        {
            stringstream sImgFilePath;
            sImgFilePath << "DrawnImg/Drawn_Side" << i+1 << ".png";
            mDrawnSide[i].load(sImgFilePath.str());
        }
        for (int i = 0; i < NUM_IMAGES; ++i)
        {
            stringstream sImgFilePath;
            sImgFilePath << "DrawnImg/Drawn_BehindSide" << i+1 << ".png";
            mDrawnBehindSide[i].load(sImgFilePath.str());
        }
        for (int i = 0; i < NUM_IMAGES; ++i)
        {
            stringstream sImgFilePath;
            sImgFilePath << "DrawnImg/Drawn_Behind" << i+1 << ".png";
            mDrawnBehind[i].load(sImgFilePath.str());
        }
    }
    
    mImagesWidth = mDrawnFront[0].getWidth()/ofRandom(4, 6);
    mImagesHeight = mDrawnFront[0].getHeight()/ofRandom(4, 6);
    mImagesPos = ofPoint(-mImagesWidth/2, -mImagesHeight * 5/8, 0);
}

// -----------------------------------------------------------------------------
void DrawnPerson::renderingUpdate()
{
    
}

void DrawnPerson::render()
{
    drawLines();
    
    ofColor charColor(255);
    drawCharacter(charColor);

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
void DrawnPerson::drawCharacter(ofColor& inColor)
{
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(mPos);
    if (mHeading < -90 || mHeading > 90)
    {
        ofScale(-1, 1, 1);
    }
    
    ofRotate(45, 1, 0, 0);
    
    ofSetColor(inColor);
    
    float imgWidth = mDrawnFront[0].getWidth()/5;
    float imgHeight = mDrawnFront[0].getHeight()/5;
    
    ofPoint imgPos = ofPoint(-imgWidth/2, -imgHeight * 5/8, 0);
    
    if(mFrameCounterImgChange >= mNextImgChange)
    {
        mCurrentImgIndex = (mCurrentImgIndex+1)%4;
        mFrameCounterImgChange = 0;
        mNextImgChange = floor(ofRandom(4,6));
    }
    ++mFrameCounterImgChange;
    
    
    if (mHeading >= 67.5 && mHeading <= 112.5)
    {
        mDrawnBehind[mCurrentImgIndex].draw(mImagesPos, mImagesWidth, mImagesHeight);
    }
    
    else if ((mHeading >= 22.5 && mHeading <= 67.5) ||
             (mHeading >= 112.5 && mHeading <= 157.5))
    {
        mDrawnBehindSide[mCurrentImgIndex].draw(mImagesPos, mImagesWidth, mImagesHeight);
    }
    
    else if ((mHeading <= 22.5 && mHeading >= -22.5) ||
             (mHeading >= 157.5 || mHeading <= -157.5))
    {
        mDrawnSide[mCurrentImgIndex].draw(mImagesPos, mImagesWidth, mImagesHeight);
    }
    
    else if ((mHeading <= -22.5 && mHeading >= -67.5) ||
             (mHeading <= -112.5 && mHeading >= -157.5))
    {
        mDrawnFrontSide[mCurrentImgIndex].draw(mImagesPos, mImagesWidth, mImagesHeight);
    }
    
    else if (mHeading <= -67.5 && mHeading >= -112.5)
    {
        mDrawnFront[mCurrentImgIndex].draw(mImagesPos, mImagesWidth, mImagesHeight);
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}

void DrawnPerson::drawLines()
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
void DrawnPerson::setOtherFlockingInteraction(Boid* inBoid,
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

// -----------------------------------------------------------------------------
void DrawnPerson::applyOtherFlockingForces()
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

