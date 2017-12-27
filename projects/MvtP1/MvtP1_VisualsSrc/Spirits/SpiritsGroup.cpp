#include "SpiritsGroup.h"

#include "Spirit.h"
#include "Vertebra.h"
#include "HE_FlowField.h"

SpiritsGroup::SpiritsGroup(HEFlowField* inFlowField)
: mFlowField(inFlowField)
, mSpiritsParameters()
{
    mSpiritsParameters.setDefault();
    
    for (int i = 0; i < 15; ++i)
    {
        ofPoint newPos(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()));
        mSpirits.push_back(new Spirit());
    }
}

SpiritsGroup::~SpiritsGroup()
{
    for (SpiritsIt it = mSpirits.begin(); it < mSpirits.end(); ++it)
    {
        delete (*it);
    }
}

// -----------------------------------------------------------------------------
void SpiritsGroup::update()
{
    int index = 0;
    for (SpiritsIt it = mSpirits.begin(); it < mSpirits.end(); ++it, ++index)
    {
        if (index >= mSpiritsParameters.mNumSpirits) break;
        
        HEMassParticle* vertebra = (*it)->getHead();
        
        // set Mass:
        vertebra->setMass(mSpiritsParameters.mHeadMass);
        
        // forceField force
        if (mFlowField)
        {
            if (mFlowField->mFboDrawn)
            {
                float flowFieldForceMag = mSpiritsParameters.mForceFieldMag;
                ofPoint flowFieldForce = mFlowField->getForceFieldForce(vertebra->getPos(),
                                                                        flowFieldForceMag);
                vertebra->applyForce(flowFieldForce);
            }
        }
        
        // spirits are repulsive
        int index2 = index + 1;
        for (SpiritsIt it2 = it + 1; it2 < mSpirits.end(); ++it2, ++index2)
        {
            if (index2 >= mSpiritsParameters.mNumSpirits) break;
            
            HEMassParticle* vertebra2 = (*it2)->getHead();
            ofPoint relativePos = vertebra->getPos() - vertebra2->getPos();
            
            float relativePosLength = relativePos.lengthSquared();
            if (relativePosLength > 50*50)
            {
                relativePos *= 75;
                relativePos /= relativePosLength;
                vertebra2->applyForce(-relativePos);
                vertebra->applyForce(relativePos);
            }
        }
        
        // attract to center
        ofPoint screenCenter = ofGetWindowSize() / 2;
        ofPoint vertebraPosToCenter = vertebra->getPos() - screenCenter;
        if (vertebraPosToCenter.lengthSquared() > 10000)
        {
            vertebraPosToCenter.normalize();
            vertebraPosToCenter *= -2.0;
            vertebra->applyForce(vertebraPosToCenter);
        }

        
        (*it)->update();
    }

}

void SpiritsGroup::draw()
{
    int index = 0;
    for (SpiritsIt it = mSpirits.begin(); it < mSpirits.end(); ++it, ++index)
    {
        if (index >= mSpiritsParameters.mNumSpirits) break;
        (*it)->draw();
    }
}

// -----------------------------------------------------------------------------
void SpiritsGroup::updateParameters(const SpiritsParameters& inParameters)
{
    mSpiritsParameters.updateParameters(inParameters);
}

// -----------------------------------------------------------------------------
void SpiritsGroup::setFlowField(HEFlowField* inFlowField)
{
    mFlowField = inFlowField;
}


