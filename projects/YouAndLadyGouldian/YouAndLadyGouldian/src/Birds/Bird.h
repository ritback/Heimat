#pragma once

#include "ofMain.h"

#include "Flock/HE_Boid.h"

class Feather;

class Bird: public HEBoid
{
public:
    Bird(const ofPoint& inPos);
    virtual ~Bird();
    
public:
    virtual void update() override;
    virtual void render() override;
    
private:
    void renderBird();
    void createShape();
    void updateColor();
    
private:
    void mayAddNewFeather();
    
private:
    void updateTail();
    
private:
    // shapes and rendering
    float maxHeight;
    float bodyHeight;
    float bodyWidth;
    ofPath shape;
    ofPath shape2;
    ofPath shape3;
    ofPoint headCenter;
    float headDiameter;
    
    ofColor colorFish;
    ofColor currentColor;
    float colorPhase;
    float colorPhaseInc;
    float colorPhaseAmp;
    
private:    // tail
    typedef std::deque<HEMassParticle*> Tail;
    typedef Tail::iterator TailIt;
    Tail mTail;
    int mNumPointsInTail;
    
protected: // wingManagement
    float wingAngle;
    float wingAngleInc;
    float wingAngleAmp;
    float wingCurrentAngle;
    float wingAnglePhase;
public:
    void updateWingPosition ();
    
private:    // tail
    typedef std::deque<Feather*> Feathers;
    typedef Feathers::iterator FeathersIt;
    Feathers mFeathers;
    
};

