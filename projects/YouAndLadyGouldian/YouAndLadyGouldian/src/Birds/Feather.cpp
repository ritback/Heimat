#include "Feather.h"

Feather::Feather()
: HEMassParticle()
, lenght(ofRandom(17, 25)) //(40)
, shape(ofPath())
, mIsVisible(false)
{
    createShape();
}

Feather::~Feather()
{
    
}

// -----------------------------------------------------------------------------
void Feather::update()
{
    if (!mIsVisible) return;
    applyForce(ofPoint(-0.01 * mVel.x, 0.01));
    incrementPos();
    
    updateColor ();
    angle += angleInc;
}

void Feather::render()
{
    if (!mIsVisible) return;
    
    ofEnableSmoothing();
    
    ofPushMatrix();
    ofTranslate(mPos);
    ofRotate(angle);
    
    // Body !
    shape.setFillColor(currentColor);
    shape.draw();
    
    shape2.setFillColor(currentColor);
    shape2.draw();
    
    ofPopMatrix();
}

// -----------------------------------------------------------------------------
void Feather::activate(const ofPoint& inPos, const ofPoint& inVel)
{
    mIsVisible = true;
    
    angle = ofRandom(0, 359);
    angleInc = ofRandom(-3, 3);
    
    currentColor = ofColor (ofRandom(200,255), ofRandom(60,255), ofRandom(80,120));
    timeFromCreation = 0;
    
    mPos = inPos;
    mVel = inVel;
}

// -----------------------------------------------------------------------------
void Feather::createShape ()
{
    float width = lenght/4;
    
    // back
    ofPoint beginnigPoint = ofPoint (0,lenght/2);
    shape.moveTo (beginnigPoint);
    
    // back
    ofPoint backVenter = ofPoint(-width/2, 0);
    ofPoint cpb1 = ofPoint(beginnigPoint.x, beginnigPoint.y - lenght/16);
    ofPoint cpb2 = ofPoint(backVenter.x, backVenter.y + lenght/8);
    shape.quadBezierTo(cpb1, cpb2, backVenter);
    
    ofPoint topPick = ofPoint (0, -lenght/2);
    ofPoint cpb3 = ofPoint (backVenter.x, backVenter.y - lenght/8);
    ofPoint cpb4 = ofPoint (topPick.x, topPick.y + lenght/16);
    shape.quadBezierTo(cpb3, cpb4, topPick);
    
    
    // front
    
    ofPoint frontVenter = ofPoint(width/2, 0);
    ofPoint cpf1 = ofPoint(topPick.x, topPick.y + lenght/16);
    ofPoint cpf2 = ofPoint(frontVenter.x, frontVenter.y - lenght/8);
    shape.quadBezierTo(cpf1, cpf2, frontVenter);
    
    
    ofPoint cpf3 = ofPoint (frontVenter.x, frontVenter.y + lenght/8);
    ofPoint cpf4 = ofPoint (beginnigPoint.x, beginnigPoint.y - lenght/16);
    shape.quadBezierTo(cpf3, cpf4, beginnigPoint);
    
    
    shape.close();
    
    // tail
    float tailWidth = lenght/(20);
    shape2.rectangle(-tailWidth/2, lenght/4, tailWidth, lenght/3);
}

// -----------------------------------------------------------------------------
void Feather::updateColor()
{
    timeFromCreation++;
    float inc = 0.1;
    if (timeFromCreation>50)
    {
        currentColor.a -= inc;
    }
    
    if (currentColor.a <= 0)
        mIsVisible = false;
}




