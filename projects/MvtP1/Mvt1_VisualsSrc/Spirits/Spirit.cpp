#include "Spirit.h"

#include "Vertebra.h"

Spirit::Spirit()
: mWormThickness(20)
, mAlpha(0)
{
    
    //mSpine.push_back(new Vertebra(ofPoint(400, 400)));

    int numVertebra = (int)ofRandom(8, 15);
    float springLenght = ofRandom(20, 50);

    ofPoint newPos(ofRandom(0, ofGetWindowWidth()),
                   ofRandom(0, ofGetWindowHeight()));
    mSpine.push_back(new Vertebra(newPos));
    
    for (int i = 0; i < numVertebra; ++i)
    {
        ofPoint newPos(mSpine[i]->mPos);
        newPos.x += 10;
        Vertebra * newVert = new Vertebra(newPos, mSpine[i]);
        
        newVert->mSpringLenght = springLenght;
        newVert->mMass = 1.0;
        
        mSpine.push_back(newVert);
    }
}

Spirit::~Spirit()
{
    for (VertebraeIt it = mSpine.begin(); it < mSpine.end(); ++it)
    {
        delete (*it);
    }
}

// -----------------------------------------------------------------------------

void Spirit::update()
{
    limitToScreen();
    
    for (VertebraeIt it = mSpine.begin(); it < mSpine.end(); ++it)
    {
        // apply world Friction
        float worldViscosity = 0.5;
        (*it)->applyForce(- worldViscosity * (*it)->mVel);
        
        // apply spine effect
        (*it)->applySpineForces();
    }
    
    // finally update position
    for (VertebraeIt it = mSpine.begin(); it < mSpine.end(); ++it)
    {
        (*it)->updatePos();
        
    }
    
    
}

void Spirit::draw()
{
    drawWorm();
    
    //drawDebug();
    
}

// -----------------------------------------------------------------------------
Vertebra* Spirit::getHead()
{
    return mSpine[0];
}

Vertebra* Spirit::getVertebra(int inIndex)
{
    if (inIndex >= mSpine.size())
        return 0;
    return mSpine[inIndex];
}

// -----------------------------------------------------------------------------
void Spirit::drawDebug()
{
    ofPushStyle();
    for (VertebraeIt it = mSpine.begin(); it < mSpine.end(); ++it)
    {
        ofSetColor(0, 0, 178, 150);
        // node pos
        ofDrawCircle((*it)->mPos, 10);
        if ((*it)->mFrontVertebra)
        {
            // springLink
            ofSetColor(0, 245, 0, 150);
            ofSetLineWidth(5);
            ofDrawLine((*it)->mPos, (*it)->mFrontVertebra->mPos);
            
            // normal
            ofSetColor(0, 255, 255);
            ofPoint normalPoint;
            normalPoint.x = -(*it)->mRelativePosToFront.y;
            normalPoint.y = (*it)->mRelativePosToFront.x;
            ofDrawLine((*it)->mPos, (*it)->mPos + normalPoint);
            ofDrawLine((*it)->mPos, (*it)->mPos - normalPoint);
            
            // velocity
            ofPushMatrix();
            ofSetColor(255, 0, 0, 255);
            
            ofTranslate((*it)->mPos.x, (*it)->mPos.y);
            ofRotate(heading2D((*it)->mVel));
            
            ofDrawLine(0, 0, 30, 0);
            
            ofPopMatrix();
            
        }
    }
    ofPopStyle();
    
}

// -----------------------------------------------------------------------------
void Spirit::drawWorm()
{
    
    ofPushStyle();
    
    if (mAlpha < 235) mAlpha += 2.0;
    
    ofSetColor(249, 244, 228, mAlpha);
    
    float wormCurrentLenght = 0;
    
    
    ofPoint firstBackwardRelativePos = mSpine[0]->mBackVertebra->mRelativePosToFront;
    ofPoint firstVertex = mSpine[0]->mPos + firstBackwardRelativePos / 2;
    
    ofPoint lastFrontRelativePos = mSpine[mSpine.size()-1]->mRelativePosToFront;
    ofPoint lastVertex = mSpine[mSpine.size()-1]->mPos - lastFrontRelativePos / 2;
    
    
    
    ofBeginShape();
    
    for (VertebraeIt it = mSpine.begin(); it < mSpine.end(); ++it)
    {
        if ((*it)->mFrontVertebra)
        {
            wormCurrentLenght += (*it)->mSpringLenght;
            
            float currentThickness = getCurrentWormThickness(wormCurrentLenght);
            
            ofPoint normalPoint;
            normalPoint.x = -(*it)->mRelativePosToFront.y;
            normalPoint.y = (*it)->mRelativePosToFront.x;
            normalPoint.normalize();
            normalPoint *= mWormThickness + currentThickness;
            ofPoint large = (*it)->mPos + normalPoint;
            ofCurveVertex(large);
        }
        else
        {
            if ((*it)->mBackVertebra)
            {
                ofVertex(firstVertex);
                ofCurveVertex(firstVertex);
                ofCurveVertex(firstVertex);
                
                ofPoint normalPointToVel;
                normalPointToVel.x = -firstBackwardRelativePos.y;
                normalPointToVel.y = +firstBackwardRelativePos.x;
                normalPointToVel.normalize();
                
                float currentThickness = getCurrentWormThickness(wormCurrentLenght);
                normalPointToVel *= mWormThickness + currentThickness;
                
                ofPoint firstCurveVertex = (*it)->mPos + normalPointToVel;
                ofCurveVertex(firstCurveVertex);
            }
        }
    }
    
    ofCurveVertex(lastVertex);
    ofCurveVertex(lastVertex);
    ofVertex(lastVertex);
    ofCurveVertex(lastVertex);
    ofCurveVertex(lastVertex);
    
    wormCurrentLenght += mSpine[0]->mSpringLenght;
    for (ReVertebraeIt it = mSpine.rbegin(); it < mSpine.rend(); ++it)
    {
        if ((*it)->mFrontVertebra)
        {
            
            float currentThickness = getCurrentWormThickness(wormCurrentLenght);
            
            wormCurrentLenght -= (*it)->mSpringLenght;
            
            
            ofPoint normalPoint;
            normalPoint.x = (*it)->mRelativePosToFront.y;
            normalPoint.y = -(*it)->mRelativePosToFront.x;
            normalPoint.normalize();
            normalPoint *= mWormThickness + getCurrentWormThickness(wormCurrentLenght);;
            ofPoint large = (*it)->mPos + normalPoint;
            ofCurveVertex(large);
        }
        else
        {
            if ((*it)->mBackVertebra)
            {
                ofPoint normalPointToVel;
                normalPointToVel.x = +firstBackwardRelativePos.y;
                normalPointToVel.y = -firstBackwardRelativePos.x;
                normalPointToVel.normalize();
                
                float currentThickness = getCurrentWormThickness(wormCurrentLenght);
                normalPointToVel *= mWormThickness + currentThickness;
                
                ofPoint firstCurveVertex = (*it)->mPos + normalPointToVel;
                ofCurveVertex(firstCurveVertex);
                
                ofCurveVertex(firstVertex);
                ofCurveVertex(firstVertex);
                
            }
        }
    }
    
    ofEndShape(true);
    
    ofPopStyle();
    
    
}

float Spirit::getCurrentWormThickness(float inWormCurrentLenght)
{
    float time = ofGetElapsedTimef();
    float phase = 0.04 * (1 + 0.2 * sin(0.0005 * time) + +0.8 * sin(0.00005 * time)) * inWormCurrentLenght;

    return 10 * sin(1.5 * ofGetElapsedTimef() + phase);
}

// -----------------------------------------------------------------------------
void Spirit::limitToScreen()
{
    ofPoint screenTopLeft(0, 0);
    ofPoint screenSize = ofGetWindowSize();
    
    float margin = -200;
    
    ofPoint restrictedAreaTopLeft(screenTopLeft.x + margin,
                                  screenTopLeft.y + margin);
    ofPoint restrictedAreaBottomRigth(screenTopLeft.x + screenSize.x - margin,
                                      screenTopLeft.y + screenSize.y - margin);
    
    ofPoint TeleportationOffSet(screenSize.x - 2*margin,
                                screenSize.y - 2*margin);
    
    
    // if head and tail are ouside, translate them to the other side.
    
    
    ofPoint headPos((*mSpine.begin())->mPos);
    ofPoint tailPos((*(mSpine.end()-1))->mPos);
    
    
    if (headPos.x < restrictedAreaTopLeft.x && tailPos.x < restrictedAreaTopLeft.x)
    {
        for (VertebraeIt it = mSpine.begin(); it < mSpine.end(); ++it)
        {
            (*it)->mPos += ofPoint(TeleportationOffSet.x, 0);
            mAlpha = 0;
        }
    }
    else if (headPos.x > restrictedAreaBottomRigth.x && tailPos.x > restrictedAreaBottomRigth.x)
    {
        for (VertebraeIt it = mSpine.begin(); it < mSpine.end(); ++it)
        {
            (*it)->mPos += ofPoint(-TeleportationOffSet.x, 0);
            mAlpha = 0;
        }
    }
    
    if (headPos.y < restrictedAreaTopLeft.y && tailPos.y < restrictedAreaTopLeft.y)
    {
        for (VertebraeIt it = mSpine.begin(); it < mSpine.end(); ++it)
        {
            (*it)->mPos += ofPoint(0, TeleportationOffSet.y);
            mAlpha = 0;
        }
    }
    else if (headPos.y > restrictedAreaBottomRigth.y && tailPos.y > restrictedAreaBottomRigth.y)
    {
        for (VertebraeIt it = mSpine.begin(); it < mSpine.end(); ++it)
        {
            (*it)->mPos += ofPoint(0, -TeleportationOffSet.y);
            mAlpha = 0;
        }
    }
}
