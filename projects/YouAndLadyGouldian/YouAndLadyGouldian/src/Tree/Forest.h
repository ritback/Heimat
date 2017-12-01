#pragma once

#include "ofMain.h"
#include "Tree.h"

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
    void activateATree(const ofPoint& inPos);

private:
    typedef std::deque<Tree*> Trees;
    typedef Trees::iterator TreesIt;
    Trees mTrees;

};
 