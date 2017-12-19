#pragma once

#include "ofMain.h"
#include <vector>

#include "SpiritsParameters.h"

class Spirit;
class HEFlowField;

class SpiritsGroup
{
public:
    SpiritsGroup(HEFlowField* inFlowField = 0);
    virtual ~SpiritsGroup();
    
public:
    void update();
    void draw();
    
public:
    void updateParameters(const SpiritsParameters& inParameters);

public:
    void setFlowField(HEFlowField* inFlowField);
    
private:
    typedef std::vector<Spirit*> Spirits;
    typedef Spirits::iterator SpiritsIt;
    Spirits mSpirits;
    
private:
    SpiritsParameters mSpiritsParameters;
    
private:
    HEFlowField* mFlowField;


};



