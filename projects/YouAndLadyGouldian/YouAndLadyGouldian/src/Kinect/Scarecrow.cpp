#include "Scarecrow.h"

#include "..\Birds\BirdsFlock.h"

#include "HE_FlockingWorld.h"
#include "HEHelpers_Maths.h"

#include "Forest.h"

Scarecrow::Scarecrow()
    : HESkeleton<ScarecrowJoint>()
    , mTreeCreationTime(60)
    , mLastTrunkMoveTime(10000)
{

}

Scarecrow::~Scarecrow()
{

}

//------------------------------------------------------------------------------
void Scarecrow::applyEffectOnBirds(BirdsFlock* inFlock)
{
    // current joint
    ScarecrowJoint* joint = &mJoints[0];

    for(int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i, ++joint)
    {
        if(joint->mTrackingState == NUI_SKELETON_POSITION_TRACKED)
        {
            // left/right side attraction is limited to left/right elbow
            limitTrunkAttractionToElbow(joint, i);

            // get if a trunk has moved
            detectTrunkMoves(joint, i);

            // set the force
            float forceMag = 0.5 * joint->getAttraction();

            /* // removing here.. Hand + wrist attract to much birds
            if(isJointOnRightHandComponent((NUI_SKELETON_POSITION_INDEX) i)
               || isJointOnLeftHandComponent((NUI_SKELETON_POSITION_INDEX) i))
            {
                forceMag *= 1.5;
            }
            */
            if(i == NUI_SKELETON_POSITION_ELBOW_LEFT
               || i == NUI_SKELETON_POSITION_ELBOW_RIGHT)
            {
                forceMag *= 1.25;
            }

            applyForceToBirds(inFlock, joint->mPos, forceMag, joint->getEffectRange());
        }
    }

    // add repulsive points where it miss somes
    applyForceToBirdsBetween2Joints(inFlock,
                                    NUI_SKELETON_POSITION_SHOULDER_CENTER,
                                    NUI_SKELETON_POSITION_SPINE);
    applyForceToBirdsBetween2Joints(inFlock,
                                    NUI_SKELETON_POSITION_HIP_LEFT,
                                    NUI_SKELETON_POSITION_KNEE_LEFT);
    applyForceToBirdsBetween2Joints(inFlock,
                                    NUI_SKELETON_POSITION_HIP_RIGHT,
                                    NUI_SKELETON_POSITION_KNEE_RIGHT);

}

//------------------------------------------------------------------------------
void Scarecrow::setJointsEffectRange(float inValue)
{
    ScarecrowJoint* joint = &mJoints[0];
    for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i, ++joint)
    {
        joint->setEffectRange(inValue);
    }
}

float Scarecrow::getJointsEffectRange()
{
    ScarecrowJoint* joint = &mJoints[0];
    return joint->getEffectRange();
}

void Scarecrow::setJointsHasMoveDistance(float inValue)
{
    ScarecrowJoint* joint = &mJoints[0];
    for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i, ++joint)
    {
        joint->setHasMoveDistance(inValue);
    }
}

float Scarecrow::getJointsHasMoveDistance()
{
    ScarecrowJoint* joint = &mJoints[0];
    return joint->getHasMoveDistance();
}

void Scarecrow::setJointsAttractionInc(float inValue)
{
    ScarecrowJoint* joint = &mJoints[0];
    for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i, ++joint)
    {
        joint->setAttractionInc(inValue);
    }
}

float Scarecrow::getJointsAttractionInc()
{
    ScarecrowJoint* joint = &mJoints[0];
    return joint->getAttractionInc();
}

void Scarecrow::setJointsAttractionMin(float inValue)
{
    ScarecrowJoint* joint = &mJoints[0];
    for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i, ++joint)
    {
        joint->setAttractionMin(inValue);
    }
}

float Scarecrow::getJointsAttractionMin()
{
    ScarecrowJoint* joint = &mJoints[0];
    return joint->getAttractionMin();
}

void Scarecrow::setJointsAttractionMax(float inValue)
{
    ScarecrowJoint* joint = &mJoints[0];
    for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i, ++joint)
    {
        joint->setAttractionMax(inValue);
    }
}

float Scarecrow::getJointsAttractionMax()
{
    ScarecrowJoint* joint = &mJoints[0];
    return joint->getAttractionMax();
}

//------------------------------------------------------------------------------
void Scarecrow::setTreeCreationTime(float inValue)
{
    mTreeCreationTime = inValue;
}

float Scarecrow::getTreeCreationTime()
{
    return mTreeCreationTime;
}

//------------------------------------------------------------------------------
void Scarecrow::limitTrunkAttractionToElbow(ScarecrowJoint* joint, int i)
{
    if(!isJointOnRightHandComponent((NUI_SKELETON_POSITION_INDEX)i))
    {
        if(isJointOnRightSide((NUI_SKELETON_POSITION_INDEX)i)
           || isJointOnTrunk((NUI_SKELETON_POSITION_INDEX)i))
        {
            ScarecrowJoint* rightElbowJoint = &mJoints[NUI_SKELETON_POSITION_ELBOW_RIGHT];
            if(joint->getAttraction() > rightElbowJoint->getAttraction())
            {
                joint->setAttraction(rightElbowJoint->getAttraction());
            }
        }
    }

    if(!isJointOnLeftHandComponent((NUI_SKELETON_POSITION_INDEX)i))
    {
        if(isJointOnLeftSide((NUI_SKELETON_POSITION_INDEX)i)
           || isJointOnTrunk((NUI_SKELETON_POSITION_INDEX)i))
        {
            ScarecrowJoint* leftElbowJoint = &mJoints[NUI_SKELETON_POSITION_ELBOW_LEFT];
            if(joint->getAttraction() > leftElbowJoint->getAttraction())
            {
                joint->setAttraction(leftElbowJoint->getAttraction());
            }
        }
    }
}

void Scarecrow::detectTrunkMoves(ScarecrowJoint* joint, int i)
{
    if(i == NUI_SKELETON_POSITION_SHOULDER_CENTER) // isJointOnTrunk((NUI_SKELETON_POSITION_INDEX)i)
    {
        if(joint->getAttraction() < joint->getAttractionMax() - 0.5)
        {
            mLastTrunkMoveTime = ofGetElapsedTimef();
        }
        else
        {
            checkTreeCreation(joint->mPos);
        }
    }
}

//------------------------------------------------------------------------------
void Scarecrow::applyForceToBirds(BirdsFlock* inFlock, const ofPoint& inJointPos,
                                  float forceMag, float inRange)
{
    // transfer from Skeleton/Screen position to Flock world pos
    ofPoint jointPos = inJointPos;
    ofPoint worldLimitMin((inFlock->getWorld()->getWorldLimitMin()));
    ofPoint worldLimitMax((inFlock->getWorld()->getWorldLimitMax()));
    ofPoint forcePos(jointPos);
    forcePos.z = 0; // it's not in 3D... lol
    ofPoint screenSize(ofGetWindowSize());

    scaleToRange(forcePos,
                 ofPoint(0, 0, 0), screenSize,
                 worldLimitMin, worldLimitMax);
    inFlock->applyForceToBoidsFromPosition(forcePos, forceMag, inRange);

    if(forceMag > 0)
    {
        inFlock->reduceSpeedOfBirdsInDistance(forcePos, 0.5, inRange);
    }
}

//------------------------------------------------------------------------------
void Scarecrow::applyForceToBirdsBetween2Joints(BirdsFlock* inFlock,
                                     NUI_SKELETON_POSITION_INDEX inJoint1,
                                     NUI_SKELETON_POSITION_INDEX inJoint2)
{
    ScarecrowJoint* joint1 = &mJoints[inJoint1];
    ScarecrowJoint* joint2 = &mJoints[inJoint2];
    if(joint1->mTrackingState == NUI_SKELETON_POSITION_TRACKED
       && joint2->mTrackingState == NUI_SKELETON_POSITION_TRACKED)
    {

        float forceMag = 0.5 * joint1->getAttraction();
        // find center point
        ofPoint mBetweenPoint(0);
        mBetweenPoint.x = (joint1->mPos.x - joint2->mPos.x) / 2 + joint2->mPos.x;
        mBetweenPoint.y = (joint1->mPos.y - joint2->mPos.y) / 2 + joint2->mPos.y;

        applyForceToBirds(inFlock, mBetweenPoint, forceMag, joint1->getEffectRange());
    }
}

//------------------------------------------------------------------------------
void Scarecrow::checkTreeCreation(const ofPoint& inPos)
{
    float mEllapsedTime = ofGetElapsedTimef();
    
    if(mEllapsedTime - mLastTrunkMoveTime >= mTreeCreationTime)
    {
        Forest::createTreeAt(inPos);
        mLastTrunkMoveTime = mEllapsedTime;
    }
}

