#include "SnowFlakes.h"

#include "Flake.h"
#include "HE_FlowField.h"

SnowFlakes::SnowFlakes(HEFlowField* inFlowField)
: mFlowField(inFlowField)
, mFlakesParameters()
{
    //mFlakesImg.load("images/Flakes_50_400.png");
    mFlakesImg.load("images/Flake_round.png");
    
    mFlakesParameters.setDefault();
    
    for (int i = 0; i < 150; ++i)
    {
        ofPoint newPos(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()));
        int numIndex = (int)(mFlakesImg.getHeight() / mFlakesImg.getWidth() - 1);
        
        mFlakes.push_back(new Flake(newPos, numIndex));
    }
}

SnowFlakes::~SnowFlakes()
{
    for (FlakesIt it = mFlakes.begin(); it < mFlakes.end(); ++it)
    {
        delete (*it);
    }
}

// -----------------------------------------------------------------------------
void SnowFlakes::update()
{
    limitToScreen();
    
    int index = 0;
    // Flakes are repulsive for each others...
    for (FlakesIt it = mFlakes.begin(); it < mFlakes.end(); ++it, ++index)
    {
        if (index >= mFlakesParameters.mNumFlakes) break;
        HEMassParticle* flake = (*it);
        // set Mass:
        flake->mMass = mFlakesParameters.mMass;
        
        
        // force field force:
        if (mFlowField)
        {
            if (mFlowField->mFboDrawn)
            {
                float flowFieldForceMag = mFlakesParameters.mForceFieldMag;
                ofPoint flowFieldForce = mFlowField->getForceFieldForce(flake->mPos,
                                                                        flowFieldForceMag);
                
                flake->applyForce(-flowFieldForce);
            }
        }
        
        int index2 = index + 1;
        // repulsive forces from other boids
        for (FlakesIt it2 = it + 1; it2 < mFlakes.end(); ++it2, ++index2)
        {
            if (index2 >= mFlakesParameters.mNumFlakes) break;
            
            HEMassParticle* flake2 = (*it2);
            ofPoint relativePos = flake->mPos - flake2->mPos;
            
            float relativePosLength = relativePos.lengthSquared();
            if (relativePosLength > 30*30)
            {
                relativePos *= 25;
                relativePos /= relativePosLength;
                flake2->applyForce(-relativePos);
                flake->applyForce(relativePos);
            }
        }
        
        // attract to center
        ofPoint screenCenter = ofGetWindowSize() / 2;
        ofPoint flakePosToCenter = flake->mPos - screenCenter;
        if (flakePosToCenter.lengthSquared() > 10000)
        {
            flakePosToCenter.normalize();
            flakePosToCenter *= -1.5;
            flake->applyForce(flakePosToCenter);
        }
        
        // world viscosity (limit speed)
        float worldViscosity = mFlakesParameters.mWorldViscosity;
        (*it)->applyForce(- worldViscosity * (*it)->mVel);
        (*it)->updatePos();
    }
}

void SnowFlakes::draw()
{
    
    int index = 0;
    for (FlakesIt it = mFlakes.begin(); it < mFlakes.end(); ++it, ++index)
    {
        if (index >= mFlakesParameters.mNumFlakes) break;
        
        //(*it)->draw();
        
        ofPushStyle();
        ofSetColor((*it)->mColor);
        
        ofPushMatrix();
        
        ofTranslate((*it)->mPos);
        ofRotate((*it)->mHeading);
        
        /*
        mFlakesImg.drawSubsection(-(*it)->mWidth/2, -(*it)->mHeight/2,
                                  (*it)->mWidth, (*it)->mHeight,
                                  0.0, (float)(*it)->mFlakeImgIndex * mFlakesImg.getWidth());
        */
        
        mFlakesImg.draw(-(*it)->mWidth/2, -(*it)->mHeight/2,
                        (*it)->mWidth, (*it)->mHeight);
        
        ofPopMatrix();
        
        ofPopStyle();
        
    }
}

// -----------------------------------------------------------------------------
void SnowFlakes::updateParameters(const FlakesParameters& inParameters)
{
    mFlakesParameters.updateParameters(inParameters);
}

// -----------------------------------------------------------------------------
void SnowFlakes::setFlowField(HEFlowField* inFlowField)
{
    mFlowField = inFlowField;
}

// -----------------------------------------------------------------------------
void SnowFlakes::limitToScreen()
{
    ofPoint screenTopLeft(0, 0);
    ofPoint screenSize = ofGetWindowSize();
    
    float margin = -20;
    
    ofPoint restrictedAreaTopLeft(screenTopLeft.x + margin,
                                  screenTopLeft.y + margin);
    ofPoint restrictedAreaBottomRigth(screenTopLeft.x + screenSize.x - margin,
                                      screenTopLeft.y + screenSize.y - margin);
    
    
    for (FlakesIt it = mFlakes.begin(); it < mFlakes.end(); ++it)
    {
        if ((*it)->mPos.x <= restrictedAreaTopLeft.x)
        {
            (*it)->mPos.x = restrictedAreaBottomRigth.x;
        }
        else if ((*it)->mPos.x >= restrictedAreaBottomRigth.x)
        {
            (*it)->mPos.x = restrictedAreaTopLeft.x;
        }
        
        if ((*it)->mPos.y <= restrictedAreaTopLeft.y)
        {
            (*it)->mPos.y = restrictedAreaBottomRigth.y;
        }
        else if ((*it)->mPos.y >= restrictedAreaBottomRigth.y)
        {
            (*it)->mPos.y = restrictedAreaTopLeft.y;
        }
    }
}

