#pragma once

#include "ofMain.h"

class HEBoid;

class HEFlockingWorldInterface
{
public:
    HEFlockingWorldInterface();
    virtual ~HEFlockingWorldInterface();
    
public:
    virtual void applyWorldForce(HEBoid* inBoid)= 0;
    
public:
    virtual void render();

public:
    void setWorldLimitCenter(const ofPoint& inWorldLimit);
    ofPoint getWorldLimitCenter();
    void setWorldLimitMin(const ofPoint& inWorldLimit);
    ofPoint getWorldLimitMin();
    void setWorldLimitMax(const ofPoint& inWorldLimit);
    ofPoint getWorldLimitMax();
    void setWorldLimit(const ofPoint& inWorldLimitOirgin, float width, float height);
    void setWorldLimit(const ofPoint& inWorldLimitMin, const ofPoint& inWorldLimitMax);
    void setWorldLimit(const ofRectangle& inWorldLimit);
    ofRectangle getWorldLimit();
    
public:
    void setWorldLimitDistanceMin(const ofPoint& inWorldLimit);
    ofPoint getWorldLimitDistanceMin();
    void setWorldLimitDistanceMax(const ofPoint& inWorldLimit);
    ofPoint getWorldLimitDistanceMax();
    void setWorldLimitDistance(const ofPoint& inWorldLimitOirgin,
                               float width, float height);
    void setWorldLimitDistance(const ofPoint& inWorldLimitMin,
                               const ofPoint& inWorldLimitMax);
    void setWorldLimitDistance(const ofRectangle& inWorldLimit);
    ofRectangle getWorldLimitDistance();
    
public:
    void setWorldRepulsionMag(const float& inValue);
    float getWorldRepulsionMag();
    
public:
    void setWorldViscosity(const float& inValue);
    float getWorldViscosity();
    
protected:
    void applyWorldViscosity(HEBoid* inBoid);
    void teleportOtherSideOfWorld(HEBoid* inBoid);
    
protected:
    ofRectangle mWorldLimit;
    ofRectangle mWorldLimitDistance;
    
protected:
    float mWorldRepulsionMag;
    float mWorldViscosity;
};

// -----------------------------------------------------------------------------
class HEBoxWorld: public HEFlockingWorldInterface
{
public:
    HEBoxWorld();
    virtual ~HEBoxWorld();
    
public:
    virtual void applyWorldForce(HEBoid* inBoid) override;
    
};

// -----------------------------------------------------------------------------
class HEStreetWorld: public HEFlockingWorldInterface
{
public:
    HEStreetWorld();
    virtual ~HEStreetWorld();
    
public:
    virtual void applyWorldForce(HEBoid* inBoid) override;
    
};

