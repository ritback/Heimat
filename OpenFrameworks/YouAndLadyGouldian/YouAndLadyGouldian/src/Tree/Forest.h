#pragma once

#include "ofMain.h"
#include "TreeForest.h"

#include <deque>


class Forest
{
public:
    Forest();
    ~Forest();

public:
    void update();
    void render();

public:
    static void createTreeAt(const ofPoint& inPos);

public:
    int getNumTree();
    
private:
    void activateATree();

private:
    typedef std::deque<Tree*> Trees;
    typedef Trees::iterator TreesIt;
    Trees mTrees;
    
private:
    static bool bShouldActivateATree;
    static ofPoint mCreateTreeAtPos;

};
 
