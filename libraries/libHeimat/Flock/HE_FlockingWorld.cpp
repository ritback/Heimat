#include "HE_FlockingWorld.h"

#include "HE_Boid.h"
#include <cmath>

#define INITIAL_MARGIN 100

HEFlockingWorldInterface::HEFlockingWorldInterface()
: mWorldLimit(-ofGetWindowWidth()/2, -ofGetWindowHeight()/2,
              ofGetWindowWidth(), ofGetWindowHeight())
, mWorldLimitDistance(-ofGetWindowWidth()/2 + INITIAL_MARGIN,
                      -ofGetWindowHeight()/2 + INITIAL_MARGIN,
                      ofGetWindowWidth() - 2 * INITIAL_MARGIN,
                      ofGetWindowHeight() - 2 * INITIAL_MARGIN)
, mWorldRepulsionMag(1)
, mWorldViscosity(0.0)
{
    
}

HEFlockingWorldInterface::~HEFlockingWorldInterface()
{
    
}


// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void HEFlockingWorldInterface::render()
{
    ofPushStyle();
    ofNoFill();
    ofSetColor(180, 0, 0);
    ofDrawRectangle(mWorldLimit);
    ofSetColor(0, 180, 0);
    ofDrawRectangle(mWorldLimitDistance);
    ofPopStyle();
}


// -----------------------------------------------------------------------------
void HEFlockingWorldInterface::applyWorldViscosity(HEBoid* inBoid)
{
    ofPoint viscosity = - mWorldViscosity * inBoid->getVel();
    inBoid->applyForce(viscosity);
}

void HEFlockingWorldInterface::teleportOtherSideOfWorld(HEBoid* inBoid)
{
    float worldLimitLeft = mWorldLimit.getLeft();
    float worldLimitTop = mWorldLimit.getTop();
    float worldLimitRight = mWorldLimit.getRight();
    float worldLimitBottom = mWorldLimit.getBottom();
    ofPoint pos = inBoid->getPos();
    
    // Walls
    if (pos.x < worldLimitLeft)
    {
        inBoid->setPos(ofPoint(worldLimitRight, pos.y, pos.z));
    }
    else if (pos.x > worldLimitRight)
    {
        inBoid->setPos(ofPoint(worldLimitLeft, pos.y, pos.z));
    }
    
    // Ceiling and floor
    if (pos.y < worldLimitTop)
    {
        inBoid->setPos(ofPoint(pos.x, worldLimitBottom, pos.z));
    }
    else if (pos.y > worldLimitBottom)
    {
        inBoid->setPos(ofPoint(pos.x, worldLimitTop, pos.z));
    }
}


// -----------------------------------------------------------------------------
void HEFlockingWorldInterface::setWorldLimitCenter(const ofPoint& inWorldLimit)
{
    mWorldLimit.setFromCenter(inWorldLimit,
                              mWorldLimit.width,
                              mWorldLimit.height);
}


ofPoint HEFlockingWorldInterface::getWorldLimitCenter()
{
    return mWorldLimit.getCenter();
}

void HEFlockingWorldInterface::setWorldLimitMin(const ofPoint& inWorldLimit)
{
    mWorldLimit.set(inWorldLimit, mWorldLimit.getBottomRight());
}


ofPoint HEFlockingWorldInterface::getWorldLimitMin()
{
    return mWorldLimit.getTopLeft();
}


void HEFlockingWorldInterface::setWorldLimitMax(const ofPoint& inWorldLimit)
{
    mWorldLimit.set(mWorldLimit.getTopLeft(), inWorldLimit);
}


ofPoint HEFlockingWorldInterface::getWorldLimitMax()
{
    return mWorldLimit.getBottomRight();
}

void HEFlockingWorldInterface::setWorldLimit(const ofPoint& inWorldLimitOirgin,
                                             float width, float height)
{
    ofPoint origin(inWorldLimitOirgin);
    origin.x -= width / 2;
    origin.y -= height / 2;
    setWorldLimitMin(origin);
    origin.x += width;
    origin.y += height;
    setWorldLimitMax(origin);
}

void HEFlockingWorldInterface::setWorldLimit(const ofPoint& inWorldLimitMin,
                                             const ofPoint& inWorldLimitMax)
{
    setWorldLimitMin(inWorldLimitMin);
    setWorldLimitMax(inWorldLimitMax);
}

void HEFlockingWorldInterface::setWorldLimit(const ofRectangle& inWorldLimit)
{
    mWorldLimit = inWorldLimit;
}


ofRectangle HEFlockingWorldInterface::getWorldLimit()
{
    return mWorldLimit;
}


// -----------------------------------------------------------------------------
void HEFlockingWorldInterface::setWorldLimitDistanceMin(const ofPoint& inWorldLimit)
{
    mWorldLimitDistance.set(inWorldLimit, mWorldLimitDistance.getBottomRight());
}


ofPoint HEFlockingWorldInterface::getWorldLimitDistanceMin()
{
    return mWorldLimitDistance.getTopLeft();
}


void HEFlockingWorldInterface::setWorldLimitDistanceMax(const ofPoint& inWorldLimit)
{
    mWorldLimitDistance.set(mWorldLimitDistance.getTopLeft(), inWorldLimit);
}


ofPoint HEFlockingWorldInterface::getWorldLimitDistanceMax()
{
    return mWorldLimitDistance.getBottomRight();
}

void HEFlockingWorldInterface::setWorldLimitDistance(const ofPoint& inWorldLimitOirgin,
                                             float width, float height)
{
    ofPoint origin(inWorldLimitOirgin);
    origin.x -= width / 2;
    origin.y -= height / 2;
    setWorldLimitDistanceMin(origin);
    origin.x += width;
    origin.y += height;
    setWorldLimitDistanceMax(origin);
}

void HEFlockingWorldInterface::setWorldLimitDistance(const ofPoint& inWorldLimitMin,
                                             const ofPoint& inWorldLimitMax)
{
    setWorldLimitDistanceMin(inWorldLimitMin);
    setWorldLimitDistanceMax(inWorldLimitMax);
}

void HEFlockingWorldInterface::setWorldLimitDistance(const ofRectangle& inWorldLimit)
{
    mWorldLimitDistance = inWorldLimit;
}


ofRectangle HEFlockingWorldInterface::getWorldLimitDistance()
{
    return mWorldLimitDistance;
}

// -----------------------------------------------------------------------------
void HEFlockingWorldInterface::setWorldRepulsionMag(const float& inValue)
{
    mWorldRepulsionMag = inValue;
}

float HEFlockingWorldInterface::getWorldRepulsionMag()
{
    return mWorldRepulsionMag;
}

// -----------------------------------------------------------------------------
void HEFlockingWorldInterface::setWorldViscosity(const float& inValue)
{
    mWorldViscosity = inValue;
}

float HEFlockingWorldInterface::getWorldViscosity()
{
    return mWorldViscosity;
}




// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
HEBoxWorld::HEBoxWorld()
:HEFlockingWorldInterface()
{
    
}

HEBoxWorld::~HEBoxWorld()
{
    
}

// -----------------------------------------------------------------------------
void HEBoxWorld::applyWorldForce(HEBoid* inBoid)
{
    applyWorldViscosity(inBoid);
    teleportOtherSideOfWorld(inBoid);
    //return;
    
    float rightRepulsionDistance = abs(mWorldLimit.getRight() - mWorldLimitDistance.getRight());
    float leftRepulsionDistance = abs(mWorldLimit.getLeft() - mWorldLimitDistance.getLeft());
    float topRepulsionDistance = abs(mWorldLimit.getTop() - mWorldLimitDistance.getTop());
    float bottomRepulsionDistance = abs(mWorldLimit.getBottom() - mWorldLimitDistance.getBottom());
    
    ofPoint pos = inBoid->getPos();

    inBoid->applyLinearForceFromPosition(ofPoint(mWorldLimit.getLeft(), pos.y, pos.z),
                                   -mWorldRepulsionMag,
                                   rightRepulsionDistance);
    inBoid->applyLinearForceFromPosition(ofPoint(mWorldLimit.getRight(), pos.y, pos.z),
                                   -mWorldRepulsionMag,
                                   leftRepulsionDistance);

    inBoid->applyLinearForceFromPosition(ofPoint(pos.x, mWorldLimit.getTop(), pos.z),
                                   -mWorldRepulsionMag,
                                   topRepulsionDistance);
    inBoid->applyLinearForceFromPosition(ofPoint(pos.x, mWorldLimit.getBottom(), pos.z),
                                   -mWorldRepulsionMag,
                                   bottomRepulsionDistance);
}



// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
HEStreetWorld::HEStreetWorld()
:HEFlockingWorldInterface()
{
    
}

HEStreetWorld::~HEStreetWorld()
{
    
}

// -----------------------------------------------------------------------------
void HEStreetWorld::applyWorldForce(HEBoid* inBoid)
{
    
    applyWorldViscosity(inBoid);
    float max = 25;
    
    float streetEndDistance = 100;
    float streetLimitLengthMin = mWorldLimit.getLeft();
    float streetLimitLengthMax = mWorldLimit.getRight();
    
    float wallsRepulsionDistance = 50;
    float worldLimitThickMin = mWorldLimit.getTop();
    float worldLimitThickMax = mWorldLimit.getBottom();
    
    ofPoint pos = inBoid->getPos();
    
    // Walls
    if (pos.x < streetLimitLengthMin - streetEndDistance)
    {
        inBoid->setPos(ofPoint(streetLimitLengthMax + streetEndDistance, pos.y));
    }
    else if (pos.x > streetLimitLengthMax + streetEndDistance)
    {
        inBoid->setPos(ofPoint(streetLimitLengthMin - streetEndDistance, pos.y));
    }
    
    // Ceiling and floor
    if (pos.y < worldLimitThickMin + wallsRepulsionDistance)
    {
        float distance = 0;
        if (pos.y > worldLimitThickMin) // normal situation
        {
            distance = pos.y - worldLimitThickMin;
        }
        
        float repForce = max * (1 - distance / wallsRepulsionDistance);
        ofPoint repulsiveForce = ofPoint(0, 1);
        repulsiveForce *= repForce;
        
        inBoid->applyForce(repulsiveForce);
    }
    else if (pos.y > worldLimitThickMax - wallsRepulsionDistance)
    {
        float distance = 0;
        if (pos.y < worldLimitThickMax)
        {
            distance = worldLimitThickMax - pos.y;
        }
        
        float repForce = max * (1 - distance / wallsRepulsionDistance);
        ofPoint repulsiveForce = ofPoint(0, -1);
        repulsiveForce *= repForce;
        
        inBoid->applyForce(repulsiveForce);
    }
}
