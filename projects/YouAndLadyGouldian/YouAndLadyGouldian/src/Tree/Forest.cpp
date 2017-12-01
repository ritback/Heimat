#include "Forest.h"

Forest::Forest()
{
    for (int i = 0; i < 20; i++)
    {
        Tree * newTree = new Tree();
        mTrees.push_back(newTree);
    }
}

Forest::~Forest()
{
    for (TreesIt it = mTrees.begin(); it < mTrees.end(); ++it)
    {
        delete (*it);
    }
}

//------------------------------------------------------------------------------
void Forest::update()
{
    for (TreesIt it = mTrees.begin(); it < mTrees.end(); ++it)
    {
        (*it)->update();
    }
}

void Forest::render()
{
    for (TreesIt it = mTrees.begin(); it < mTrees.end(); ++it)
    {
        (*it)->render();
    }
}


//------------------------------------------------------------------------------


void Forest::activateATree(const ofPoint& inPos)
{
    TreesIt it = mTrees.begin();
    while (it != mTrees.end())
    {
        if (!(*it)->mIsVisible)
        {
            (*it)->activate(inPos);
            break;
        }
        ++it;
    }
}

