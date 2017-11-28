#include "GridShape.h"


GridShape::GridShape(const ofPoint& inPos, int inImageIndex)
: HEMassParticle(inPos)
, mCentralPos(inPos)
, mShapeImgIndex(inImageIndex)
, mColor(ofRandom(255), ofRandom(255), ofRandom(255))
, mWidth(ofRandom(0, 10) < 35 ? ofRandom(5, 30) : ofRandom(20, 30))
, mHeight(mWidth)
{
    switch (mShapeImgIndex)
    {
        case 0:
            mWidth = 125;
            mHeight = mWidth;
            mColor = ofColor(255);
            break;
            
        case 1:
            mWidth = 165;
            mHeight = mWidth;
            mColor = ofColor(240, 240, 240, 245);
            break;
            
        case 2:
            mWidth = 300;
            mHeight = mWidth/2;
            mColor = ofColor(240, 240, 240, 245);
            break;
            
        case 3:
            mWidth = 129;
            mHeight = mWidth;
            mColor = ofColor(240, 240, 240, 245);
            break;
            
        case 4:
            mWidth = 134;
            mHeight = mWidth;
            mColor = ofColor(240, 240, 240, 245);
            break;
            
        case 5:
            mWidth = 232;
            mHeight = 398;
            mColor = ofColor(240, 240, 240, 245);
            break;
            
        case 6:
            mWidth = 175;
            mHeight = mWidth;
            mColor = ofColor(240, 240, 240, 245);
            break;
        
    }
    
}

GridShape::~GridShape()
{
    
}

// -----------------------------------------------------------------------------
void GridShape::update()
{
    
}
