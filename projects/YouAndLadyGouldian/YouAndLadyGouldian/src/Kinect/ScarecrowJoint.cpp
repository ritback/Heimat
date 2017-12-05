#include "ScarecrowJoint.h"

ScarecrowJoint::ScarecrowJoint()
    : HESkeletonJoint()
    , mAttraction(-10)
    , mAttractionMin(-10)
    , mAttractionMax(3)
    , mAttractionInc(0.25)
    , mHasMoveDistance(100)
    , mUpdateTailFrameCount(0)
{
    for(int i = 0; i < 10; i++)
    {
        ofPoint* newPos = new ofPoint(0, 0, 0);
        mTail.push_back(newPos);
    }
}

ScarecrowJoint::ScarecrowJoint(const ScarecrowJoint& inJoint)
    : HESkeletonJoint(inJoint)
{
    for(int i = 0; i < (inJoint.mTail).size(); ++i)
    {
        ofPoint* newPos = new ofPoint(*(inJoint.mTail)[i]);
        mTail.push_back(newPos);
    }
}

ScarecrowJoint::~ScarecrowJoint()
{
    for(TailIt it = mTail.begin();
        it != mTail.end();
        ++it)
    {
        delete (*it);
    }
}

//------------------------------------------------------------------------------
void ScarecrowJoint::update(const HESkeletonJoint& inJoint)
{
    // update the join normally
    HESkeletonJoint::update(inJoint);

    // track activity
    ++mUpdateTailFrameCount;
    if(mUpdateTailFrameCount > 10)
    {
        *(mTail.back()) = mPos; // set new data
        mTail.push_front(mTail.back()); // place the back to the top
        mTail.pop_back(); // pop the back
        mUpdateTailFrameCount = 0;
    }
    
    updateAttraction();
}

//------------------------------------------------------------------------------
void ScarecrowJoint::setAttraction(float inValue)
{
    mAttraction = inValue;
}

float ScarecrowJoint::getAttraction()
{
    return mAttraction;
}

//------------------------------------------------------------------------------
void ScarecrowJoint::setHasMoveDistance(float inValue)
{
    mHasMoveDistance = inValue;
}

float ScarecrowJoint::getHasMoveDistance()
{
    return mHasMoveDistance;
}

void ScarecrowJoint::setAttractionInc(float inValue)
{
    mAttractionInc = inValue;
}

float ScarecrowJoint::getAttractionInc()
{
    return mAttractionInc;
}

void ScarecrowJoint::setAttractionMin(float inValue)
{
    mAttractionMin = inValue;
}

float ScarecrowJoint::getAttractionMin()
{
    return mAttractionMin;
}

void ScarecrowJoint::setAttractionMax(float inValue)
{
    mAttractionMax = inValue;
}

float ScarecrowJoint::getAttractionMax()
{
    return mAttractionMax;
}

//------------------------------------------------------------------------------
void ScarecrowJoint::renderTracked()
{
    ofSetColor(255, 30, 50, 50);
    ofDrawCircle(ofPoint(mPos.x, mPos.y), 75);

    if(mAttraction > mAttractionMin + 0.5)
        ofSetColor(0, 255, 0);
    else
        ofSetColor(255, 255, 255);

    ofDrawCircle(ofPoint(mPos.x, mPos.y), 5 + 0.5*(mAttraction - mAttractionMin));

}


//------------------------------------------------------------------------------
void ScarecrowJoint::updateAttraction()
{
    if(hasMove())
    {
        mAttraction = mAttractionMin;
    }
    else
    {
        if(mAttraction < mAttractionMax)
        {
            mAttraction += mAttractionInc;
        }
    }
}

bool ScarecrowJoint::hasMove()
{
    ofPoint previousLocation = *(mTail.front());
    static int frameCount = 0;

    for(TailIt it = mTail.begin();
        it != mTail.end() - 1;
        ++it)
    {
        ofPoint currentPos = *(*it);
        ofPoint nextPos = *(*(it + 1));
        currentPos.z = 0;
        nextPos.z = 0;
        if(currentPos.squareDistance(nextPos) > mHasMoveDistance)
        {
            return true;
        }
    }
    return false;
}

