#pragma once

#include "Flock/Flock_Boid.h"

#include "ElectricLine.h"

class DrawnPerson: public Boid
{
public:
    DrawnPerson(ofPoint inPoint);
    virtual ~DrawnPerson();
    
protected:
    virtual void init() override;
    
public:
    virtual void renderingUpdate() override;
    virtual void render() override;
    
protected:
    virtual void drawCharacter(ofColor& inColor);
    virtual void drawLines();
    
protected:
    virtual void setOtherFlockingInteraction(Boid* inBoid,
                                             float inBoidSqrDistance) override;
    virtual void applyOtherFlockingForces() override;
    
protected:
    static const int NUM_IMAGES = 4;
    static ofImage mDrawnFront[NUM_IMAGES];
    static ofImage mDrawnFrontSide[NUM_IMAGES];
    static ofImage mDrawnSide[NUM_IMAGES];
    static ofImage mDrawnBehindSide[NUM_IMAGES];
    static ofImage mDrawnBehind[NUM_IMAGES];
    
    float mImagesWidth;
    float mImagesHeight;
    ofPoint mImagesPos;
    
    int mCurrentImgIndex;
    int mFrameCounterImgChange;
    int mNextImgChange;
    
private:
	static const int NUM_LINK = 2;
    Boid* mNeighborsBoids[NUM_LINK];
	float mMinimalSqrDistances[NUM_LINK];

    ElectricLine mLines[NUM_LINK];
    
};
