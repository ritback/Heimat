#include "Forest.h"

bool Forest::bShouldActivateATree = false;
ofPoint Forest::mCreateTreeAtPos = ofPoint(0, 0);


//------------------------------------------------------------------------------
Forest::Forest()
{
    for (int i = 0; i < 1; i++)
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
    if(bShouldActivateATree)
    {
        activateATree();
        bShouldActivateATree = false;
    }
    
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
void Forest::createTreeAt(const ofPoint& inPos)
{
    bShouldActivateATree = true;
    mCreateTreeAtPos = inPos;
}

//------------------------------------------------------------------------------
void Forest::activateATree()
{
    TreesIt it = mTrees.begin();
    while (it != mTrees.end())
    {
        if (!(*it)->mIsVisible)
        {
            (*it)->activate(mCreateTreeAtPos);
            break;
        }
        ++it;
    }
}

