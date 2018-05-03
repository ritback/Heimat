#include "EyesContainer.h"

#include "EyeController.h"

EyesContainer::EyesContainer()
    : mDrawingsPositions()
    , mDrawingsWidth(ofGetWindowWidth() / 4)
    , mDrawingsHeight(ofGetWindowHeight() / 4)
{
    mColumnsPosX[0] = ofGetWindowWidth() * 1 / 4;
    mColumnsPosX[1] = ofGetWindowWidth() * 2 / 4;
    mColumnsPosX[2] = ofGetWindowWidth() * 3 / 4;

    mLinesPosY[0] = ofGetWindowHeight() * 1 / 4;
    mLinesPosY[1] = ofGetWindowHeight() * 2 / 4;
    mLinesPosY[2] = ofGetWindowHeight() * 3 / 4;

    updateDrawingsPosition();

    for (int i = 1; i <= NUM_EYES; ++i)
    {
        mEyes.push_back(new EyeController(mDrawingsPositions[i].x, mDrawingsPositions[i].y,
                                          mDrawingsWidth, mDrawingsHeight));
    }
}

EyesContainer::~EyesContainer()
{
    for (EyesIt it = mEyes.begin(); it != mEyes.end(); ++it)
    {
        delete (*it);
    }
}

// -----------------------------------------------------------------------------
void EyesContainer::render()
{
    for (EyesIt it = mEyes.begin(); it != mEyes.end(); ++it)
    {
        (*it)->render();
    }
}

void EyesContainer::update()
{
    for (EyesIt it = mEyes.begin(); it != mEyes.end(); ++it)
    {
        (*it)->update();
    }
}

// -----------------------------------------------------------------------------
void EyesContainer::stareAt(float inToPosX, float inToPosY)
{
    for (EyesIt it = mEyes.begin(); it != mEyes.end(); ++it)
    {
        (*it)->stareAt(inToPosX, inToPosY);
    }
}

// -----------------------------------------------------------------------------
void EyesContainer::setDrawingsWidth(float inDimension)
{
    mDrawingsWidth = inDimension;
    updateDrawingsSize();
}

float EyesContainer::getDrawingsWidth()
{
    return mDrawingsWidth;
}

void EyesContainer::setDrawingsHeight(float inDimension)
{
    mDrawingsHeight = inDimension;
    updateDrawingsSize();
}

float EyesContainer::getDrawingsHeight()
{
    return mDrawingsHeight;
}


void EyesContainer::setDrawingsColumnsPos(float* inDimension)
{
    mColumnsPosX[0] = inDimension[0];
    mColumnsPosX[1] = inDimension[1];
    mColumnsPosX[2] = inDimension[2];
    updateDrawingsPosition();
}

void EyesContainer::setDrawingsLinesPos(float* inDimension)
{
    mLinesPosY[0] = inDimension[0];
    mLinesPosY[1] = inDimension[1];
    mLinesPosY[2] = inDimension[2];
    updateDrawingsPosition();
}

float* EyesContainer::getDrawingsColumnsPos()
{
    return mColumnsPosX;
}

float* EyesContainer::getDrawingsLinesPos()
{
    return mLinesPosY;
}

//------------------------------------------------------------------------------
void EyesContainer::updateDrawingsPosition()
{
    int numColumn = 3;
    int columnIndex = 0;
    int lineIndex = 0;
    for (int i = 0; i < NUM_EYES; ++columnIndex, ++i)
    {
        if (columnIndex == 1 && lineIndex == 1)
        {
            ++columnIndex;
        }

        if (columnIndex >= numColumn)
        {
            columnIndex = 0;
            ++lineIndex;
        }
        mDrawingsPositions[i].x = mColumnsPosX[columnIndex];
        mDrawingsPositions[i].y = mLinesPosY[lineIndex];
    }

    int i = 0;
    for (EyesIt it = mEyes.begin();
         it != mEyes.end();
         ++it)
    {
        (*it)->setPos(mDrawingsPositions[i]);
        ++i;
    }
}

void EyesContainer::updateDrawingsSize()
{
    for (EyesIt it = mEyes.begin();
         it != mEyes.end();
         ++it)
    {
        (*it)->setSize(ofPoint(mDrawingsWidth, mDrawingsHeight));
    }
}