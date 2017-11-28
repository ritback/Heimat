#pragma once

#include "ofMain.h"
#include "Eye.h"

class EyeWithAnimations : public Eye
{
public:
    EyeWithAnimations(float inX, float inY, float inWidth, float inHeight);
	virtual ~EyeWithAnimations();

public:
    virtual void render() override;
    virtual void update() override;

public:
	void launchBlink(double inBlinkTime); // to be set by the class pair of eyes
    
public:
    void launchLookingElsewhere(); // to be set by the class pair of eyes
    bool isLookingElsewhere();
    
private:
    void setupEyelidAnimation();
    void createEyelidShape();
    
private:
    void drawEyelid();
    
private:
    void updateEyelid();
    
private:
    void updateLookingElsewhere();

private:
    ofColor mIrisColor;

private: // blink animation

    ofPath mEyelid;

    bool mBlinkAnimationIsRunning;
	float mBlinkBeginTime;
	float mBlinkTime;

    ofPoint cpCurrentCornerLeft;
    ofPoint cpCurrentCornerRight;
    
    ofPoint mAnimCoefLeftA;
    ofPoint mAnimCoefLeftB;
    ofPoint mAnimCoefRightA;
    ofPoint mAnimCoefRightB;
    
private: // look elsewhere animation
    bool mIsLookingElsewhere;
    float mLookingElsewhereBeginTimeOnPoint;
    float mLookingElsewhereTimeOnPoint;
    int mNumLookingElsewherePoints;
    int mCurrentLookingElsewherePoint;
    ofPoint mLookingElsewherePoints[5];
    
    
};

