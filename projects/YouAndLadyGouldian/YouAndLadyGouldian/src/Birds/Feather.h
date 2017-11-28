#pragma once

#include "ofMain.h"

#include "MassParticle/HE_MassParticle.h"

class Feather: public HEMassParticle
{
public:
    Feather();
    virtual ~Feather();
    
public:
    void update();
    void render();
    
public:
    void activate(const ofPoint& inPos, const ofPoint& inVel);
    
private:
    void createShape();
    void updateColor();
    
public:
    bool mIsVisible;
    
private:
    float lenght;
    float angle;
    float angleInc;
    ofPath shape;
    ofPath shape2;
    
private:
    ofColor currentColor;
    int timeFromCreation;
    
    
};

