#pragma once

#include "ofMain.h"
#include <vector>

class Vertebra;

class Spirit
{
public:
    Spirit();
    virtual ~Spirit();
    
public:
    void update();
    void draw();

public:
    Vertebra* getHead();
    Vertebra* getVertebra(int inIndex); // return null if end

private:
    void drawWorm();
    float getCurrentWormThickness(float inWormCurrentLenght);
    float mWormThickness;
    
private:
    void drawDebug();
    
private:
    void limitToScreen();
    
private:
    typedef std::vector<Vertebra*> Vertebrae;
    typedef Vertebrae::iterator VertebraeIt;
    typedef Vertebrae::reverse_iterator ReVertebraeIt;
    Vertebrae mSpine;
    
    float mAlpha;
};

