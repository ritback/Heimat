#include "Bird.h"

#include "Feather.h"
#include "HEHelpers_Maths.h"


void Bird::renderBird() {
    
    // Draw a triangle rotated in the direction of velocity
    float heading = heading2D(mVel) + 90;
    
    // update the global color;
    updateColor ();
    ofEnableSmoothing();
    
    
    // store the coordinates system
    ofPushMatrix();
    // modify the coordination system
    ofTranslate(mPos);
    ofRotate(heading);
    if (heading < 0 || heading > 180)
        ofScale(-1, 1, 1);
    
    
    // beak !
    // ------
    ofSetColor(255, 200, 100);
    float beakLenght = headDiameter * 7/8;
    float beakWidth = headDiameter * 3/8;
    ofPoint beakPic = ofPoint ( headCenter.x + beakWidth, headCenter.y - beakLenght);
    ofPoint beakChin = ofPoint (headCenter.x + beakWidth, headCenter.y);
    ofDrawTriangle(headCenter, beakPic, beakChin);
    
    
    // Body !
    // ------
    shape.setFillColor(currentColor);
    shape.draw();
    
    ofColor shape2Color = ofColor(currentColor.r - 100, currentColor.g, currentColor.b + 100);
    shape2.setFillColor(shape2Color);
    shape2.draw();
    
    
    // head !
    // ------
    // eye
    ofSetColor(0, 0, 0, 125);
    ofDrawEllipse(headCenter, headDiameter*2/3, headDiameter*2/3);
    ofSetColor(255);
    ofDrawEllipse(headCenter, headDiameter/2, headDiameter/2);
    ofSetColor(0);
    ofDrawEllipse(headCenter, headDiameter/4, headDiameter/4);
    
    
    // Wing !
    // ------
    ofTranslate(- bodyWidth * 3/16, - ((bodyHeight/2)*3/16));
    updateWingPosition();
    ofRotate(wingCurrentAngle);
    ofColor shape3Color = ofColor(currentColor.r/2 + 100, currentColor.g/2 + 100, currentColor.b/2 + 100);
    shape3.setFillColor(shape3Color);
    shape3.draw(0, 0);
    
    
    // restore the normal coodinates system
    ofPopMatrix();
    
}

// -----------------------------------------------------------------------------
void Bird::createShape ()
{
    headDiameter = bodyWidth * 7/8;
    float tailLenght = headDiameter;
    
    float stayingLenght = bodyHeight - headDiameter - tailLenght;
    float neckLenght = stayingLenght * 1/8;
    
    
    
    headCenter = ofPoint (-bodyWidth/2 + headDiameter/2, -bodyHeight/2 + headDiameter/2);
    
    
    // back
    shape.moveTo (-bodyWidth/2, bodyHeight/2);
    shape.lineTo (-bodyWidth/2, headCenter.y);
    
    // head
    //shape.moveTo(headCenter);
    shape.arc (headCenter, headDiameter/2, headDiameter/2, 180, 50, true);
    
    
    // neck
    float neckEndY = -bodyHeight/2 + headDiameter + neckLenght;
    
    ofPoint neckVenter = ofPoint(-(bodyWidth/2-headDiameter/2)/2, neckEndY - neckLenght/2);
    ofPoint cpn1 = ofPoint(neckVenter.x, neckEndY - neckLenght*3/4);
    ofPoint cpn2 = ofPoint(neckVenter.x, neckEndY - neckLenght*3/4);
    shape.quadBezierTo(cpn1, cpn2, neckVenter);
    
    ofPoint neckEnd = ofPoint (0, neckEndY);
    ofPoint cpn3 = ofPoint (neckVenter.x, neckEndY - neckLenght/4);
    ofPoint cpn4 = ofPoint (neckVenter.x, neckEndY - neckLenght/4);
    shape.quadBezierTo(cpn3, cpn4, neckEnd);
    
    
    // stomach
    //shape.moveTo(stomachCenter);
    
    ofPoint stomachVenter = ofPoint (bodyWidth/2, 0);
    ofPoint cps1 = ofPoint (neckEnd.x, neckEnd.y); // tangant = 0;
    ofPoint cps2 = ofPoint (stomachVenter.x, neckEndY*3/4);
    shape.quadBezierTo(cps1, cps2, stomachVenter);
    
    ofPoint stomachEnd = ofPoint (headCenter.x, bodyHeight/2 - tailLenght);
    ofPoint cps3 = ofPoint (stomachVenter.x, -neckEndY/4); // tangant = 0;
    ofPoint cps4 = ofPoint (bodyWidth/2, stomachEnd.y/2);
    shape.quadBezierTo(cps3, cps4, stomachEnd);
    
    
    // tail
    ofPoint tailEnd = ofPoint (-bodyWidth/2, bodyHeight/2);
    ofPoint cpt1 = ofPoint (stomachEnd.x, stomachEnd.y + tailLenght/8); // tangant = 0;
    ofPoint cpt2 = ofPoint (tailEnd.x + headDiameter/2, tailEnd.y - tailLenght/4);
    shape.quadBezierTo(cpt1, cpt2, tailEnd);
    
    
    shape.close();
    
    
    // Shape 2
    // ----------------
    
    // back
    shape2.moveTo (-bodyWidth/2, bodyHeight/2 - tailLenght);
    shape2.lineTo (-bodyWidth/2, headCenter.y);
    
    // head
    //shape.moveTo(headCenter);
    shape2.arc (headCenter, headDiameter/2, headDiameter/2, 180, 260, true);
    
    // body
    ofPoint bodyEnd2 = ofPoint(-headDiameter/4, bodyHeight/2 - 2*tailLenght);
    shape2.lineTo(bodyEnd2);
    
    // tail
    ofPoint tailEnd2 = ofPoint (-bodyWidth/2, bodyHeight/2 - tailLenght);
    ofPoint cpt21 = ofPoint (bodyEnd2.x, bodyEnd2.y + tailLenght/8); // tangant = 0;
    ofPoint cpt22 = ofPoint (tailEnd2.x + headDiameter/4, tailEnd2.y - tailLenght/8);
    shape2.quadBezierTo(cpt21, cpt22, tailEnd2);
    
    
    shape2.close();
    
    
    
    // Shape 3
    // ----------------
    
    // Wing parameters
    wingAngle = 40;
    wingAngleAmp = 40;
    wingAngleInc = ofRandom(0.6, 1);
    wingAnglePhase = ofRandom(-10,0);
    
    // Wing drawing
    float wingWidth = headDiameter;
    float wingHeight = bodyHeight * 2/3;
    float wingDepth = wingHeight - wingWidth/2;
    
    shape3.moveTo(-wingWidth/2, wingDepth);
    shape3.lineTo(-wingWidth/2, 0);
    shape3.arc(ofPoint(0, 0), wingWidth/2, wingWidth/2, 180, 0, true);
    
    ofPoint plumeBegin = ofPoint ( -wingWidth/8, wingDepth*3/4);
    ofPoint cpw1 = ofPoint (wingWidth/2, wingDepth*1/8);
    ofPoint cpw2 = ofPoint (plumeBegin.x + wingWidth/8, plumeBegin.y + wingWidth/4);
    shape3.quadBezierTo(cpw1, cpw2, plumeBegin);
    
    shape3.lineTo(plumeBegin.x, plumeBegin.y - wingDepth/4);
    
    
    
    shape3.close();
    
}

// -----------------------------------------------------------------------------
void Bird::updateWingPosition () {
    wingCurrentAngle = wingAngleAmp * sin (wingAnglePhase) + wingAngle;
    wingAnglePhase += wingAngleInc;
}

// -----------------------------------------------------------------------------
void Bird::updateColor () {
    float inc = colorPhaseAmp*sin (colorPhase);
    colorPhase += colorPhaseInc;
    
    float red = colorFish.r + inc;
    red = red>=255 ? 255 : red;
    red = red<=0 ? 0 : red;
    float green = colorFish.g + inc;
    green = green>=255 ? 255 : green;
    green = green<=0 ? 0 : green;
    float blue = colorFish.b + inc;
    blue = blue>=255 ? 255 : blue;
    blue = blue<=0 ? 0 : blue;
    
    currentColor = ofColor (red, green, blue);
}







