#include "Scarecrow.h"

#include "..\Birds\BirdsFlock.h"

#include "HE_FlockingWorld.h"
#include "HEHelpers_Maths.h"

Scarecrow::Scarecrow()
    : HESkeleton<ScarecrowJoint>()
{

}

Scarecrow::~Scarecrow()
{

}

//------------------------------------------------------------------------------
void Scarecrow::applyEffectOnBirds(BirdsFlock* inFlock)
{
    ScarecrowJoint* rightElbowJoint = &mJoints[NUI_SKELETON_POSITION_ELBOW_RIGHT];
    ScarecrowJoint* leftElbowJoint = &mJoints[NUI_SKELETON_POSITION_ELBOW_LEFT];
    
    // current joint
    ScarecrowJoint* joint = &mJoints[0];

    for(int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i, ++joint)
    {
        if(joint->mTrackingState == NUI_SKELETON_POSITION_TRACKED)
        {
            // left/right side attraction is limited to left/right elbow
            if (!isJointOnRightHandComponent((NUI_SKELETON_POSITION_INDEX) i))
            {
                if (isJointOnRightSide((NUI_SKELETON_POSITION_INDEX) i)
                    || isJointOnTrunk((NUI_SKELETON_POSITION_INDEX) i))
                {
                    if (joint->getAttraction() > rightElbowJoint->getAttraction())
                    {
                        joint->setAttraction(rightElbowJoint->getAttraction());
                    }
                }
            }

            if (!isJointOnLeftHandComponent((NUI_SKELETON_POSITION_INDEX) i))
            {
                if (isJointOnLeftSide((NUI_SKELETON_POSITION_INDEX) i)
                    || isJointOnTrunk((NUI_SKELETON_POSITION_INDEX) i))
                {
                    if (joint->getAttraction() > leftElbowJoint->getAttraction())
                    {
                        joint->setAttraction(leftElbowJoint->getAttraction());
                    }
                }
            }

            // set the force
            float forceMag = 0.5 * joint->getAttraction();

            if(isJointOnRightHandComponent((NUI_SKELETON_POSITION_INDEX) i)
               || isJointOnLeftHandComponent((NUI_SKELETON_POSITION_INDEX) i))
            {
                forceMag *= 2;
            }

            if(i == NUI_SKELETON_POSITION_ELBOW_LEFT
               || i == NUI_SKELETON_POSITION_ELBOW_RIGHT)
            {
                forceMag *= 2;
            }

            // transfer from Skeleton/Screen position to Flock world pos
            ofPoint jointPos = joint->mPos;
            ofPoint worldLimitMin((inFlock->getWorld()->getWorldLimitMin()));
            ofPoint worldLimitMax((inFlock->getWorld()->getWorldLimitMax()));
            ofPoint forcePos(jointPos);
            forcePos.z = 0; // it's not in 3D... lol
            ofPoint screenSize(ofGetWindowSize());

            scaleToRange(forcePos,
                         ofPoint(0, 0, 0), screenSize,
                         worldLimitMin, worldLimitMax);
            float viscosity = forceMag > 0 ? 0 : 0.5;
            inFlock->applyForceToBoidsFromPosition(forcePos, forceMag, 75, viscosity);
        }
    }
}

//------------------------------------------------------------------------------
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



