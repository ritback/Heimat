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
    ScarecrowJoint* joint = &mJoints[0];
    /*TODO:
    - Left/right side of the body is limited to the force of the left/right elbow

    */
    for(int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i, ++joint)
    {
        if(joint->mTrackingState == NUI_SKELETON_POSITION_TRACKED)
        {
            float forceMag = 0.5 * joint->getAttraction();

            if(i == NUI_SKELETON_POSITION_HAND_LEFT
               || i == NUI_SKELETON_POSITION_HAND_RIGHT)
            {
                forceMag *= 3;
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
