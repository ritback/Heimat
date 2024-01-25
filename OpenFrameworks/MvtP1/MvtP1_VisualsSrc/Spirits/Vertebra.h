#pragma once

#include "ofMain.h"

#include "HE_MassParticle.h"

class Vertebra: public HEMassParticle
{
public:
    Vertebra(const ofPoint& inPos,
             Vertebra* inFrontVertebra = 0, Vertebra* inBackVertebra = 0);
    virtual ~Vertebra();

public:
    void applySpineForces(); //linking between vertebrae

public:
    void updatePos();
    
public:
    void connectFrontTo(Vertebra* inVertebra);
    void connectBackTo(Vertebra* inVertebra);
    void disconnectFrontVertebra();
    void disconnectBackVertebra();
    
public:
    Vertebra* mFrontVertebra;
    Vertebra* mBackVertebra;
    
public:
    ofPoint mRelativePosToFront;
    
public:
    float mSpringLenght;
    float mSpringStrength;
    float mSpringDamping;
    
};


