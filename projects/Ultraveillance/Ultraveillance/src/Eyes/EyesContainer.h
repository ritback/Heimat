#pragma once

#include "ofMain.h"

class EyeController;

class EyesContainer
{
public:
    EyesContainer();
    ~EyesContainer();

public:
    void render();
    void update();

public:
    void stareAt(float inToPosX, float inToPosY);

public:
    void setDrawingsWidth(float inDimension);
    float getDrawingsWidth();
    void setDrawingsHeight(float inDimension);
    float getDrawingsHeight();

    void setDrawingsColumnsPos(float* inDimension);
    void setDrawingsLinesPos(float* inDimension);
    float* getDrawingsColumnsPos();
    float* getDrawingsLinesPos();

private:
    void updateDrawingsPosition();
    void updateDrawingsSize();

private:
    typedef std::vector<EyeController*> Eyes;
    typedef Eyes::iterator EyesIt;
    Eyes mEyes;

private:
    static const int NUM_EYES = 9;
    ofPoint mDrawingsPositions[NUM_EYES];
    float mDrawingsWidth;
    float mDrawingsHeight;
    float mColumnsPosX[3];
    float mLinesPosY[3];
};

