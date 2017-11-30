#pragma once

#include "ofMain.h"
#include "Tree.h"


class Trees
{
public:
    Trees();
    ~Trees();

public:
    void update();
    void render();

private:
    typedef std::vector<Tree*> Forest;
    typedef Forest::iterator TreesIt;
    Forest mTrees;

};
 