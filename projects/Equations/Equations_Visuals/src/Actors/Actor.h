#pragma once

#include "HE_Boid.h"

#include "ElectricLine.h"

class Actor: public HEBoid
{
public:
    Actor(const ofPoint& inPos);
    virtual ~Actor();
    
public:
    virtual void render() override;
    
protected:
    virtual void drawCharacter(ofColor& inColor, float inHeading);
    virtual void drawLines();
    
protected:
    virtual void otherFlockingInteraction(HEBoid* inBoid,
                                          float inBoidSqrDistance) override;
    virtual void applyOtherFlockingInteraction() override;
    
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
    HEBoid* mNeighborsBoids[NUM_LINK];
	float mMinimalSqrDistances[NUM_LINK];

    ElectricLine mLines[NUM_LINK];
    
};
