#pragma once

#include "ofMain.h"

#include "FlakesParameters.h"

class Flake;
class HEFlowField;

class SnowFlakes
{
public:
    SnowFlakes(HEFlowField* inFlowField = 0);
    virtual ~SnowFlakes();
    
public:
    void update();
    void draw();
    
public:
    void updateParameters(const FlakesParameters& inParameters);
    
public:
    void setFlowField(HEFlowField* inFlowField);
    
private:
    void limitToScreen();
    
private:
    typedef std::vector<Flake*> Flakes;
    typedef Flakes::iterator FlakesIt;
    Flakes mFlakes;
    
private:
    ofImage mFlakesImg;
    
private:
    FlakesParameters mFlakesParameters;
    
private:
    HEFlowField* mFlowField;
    
};
