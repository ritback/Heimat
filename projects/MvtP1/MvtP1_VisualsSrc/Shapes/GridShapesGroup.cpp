#include "GridShapesGroup.h"

#include "GridShape.h"
#include "HE_FlowField.h"

GridShapesGroup::GridShapesGroup(HEFlowField* inFlowField)
: mFlowField(inFlowField)
{
    ofImage* img1 = new ofImage();
    img1->load("../../../../MvtP1_VisualsAssets/images/Shapes/Shapes1.png");
    mImages.push_back(img1);

    ofImage* img2 = new ofImage();
    img2->load("../../../../MvtP1_VisualsAssets/images/Shapes/Shapes2.png");
    mImages.push_back(img2);

    ofImage* img3 = new ofImage();
    img3->load("../../../../MvtP1_VisualsAssets/images/Shapes/Shapes3.png");
    mImages.push_back(img3);
    
    ofImage* img4 = new ofImage();
    img4->load("../../../../MvtP1_VisualsAssets/images/Shapes/Shapes4.png");
    mImages.push_back(img4);
    
    ofImage* img5 = new ofImage();
    img5->load("../../../../MvtP1_VisualsAssets/images/Shapes/Shapes5.png");
    mImages.push_back(img5);
    
    ofImage* img6 = new ofImage();
    img6->load("../../../../MvtP1_VisualsAssets/images/Shapes/Shapes6.png");
    mImages.push_back(img6);
    
    ofImage* img7 = new ofImage();
    img7->load("../../../../MvtP1_VisualsAssets/images/Shapes/Shapes7.png");
    mImages.push_back(img7);
    
    
    int imgIndex = 0;
    for (int i = 0; i < 7; ++i, ++imgIndex)
    {
        if (imgIndex >= mImages.size()) imgIndex = 0;
        
        ofPoint newPos(ofRandom(ofGetWindowWidth()),
                       ofRandom(ofGetWindowHeight()));
        
        GridShape * newShape = new GridShape(newPos, imgIndex);
        newShape->setMass(15.0);
        
        mGridShapes.push_back(newShape);
        
    }
}

GridShapesGroup::~GridShapesGroup()
{
    for (GridShapesIt it = mGridShapes.begin(); it < mGridShapes.end(); ++it)
    {
        delete (*it);
    }
    
    for (GridImagesIt it = mImages.begin(); it < mImages.end(); ++it)
    {
        delete (*it);
    }
}

// -----------------------------------------------------------------------------
void GridShapesGroup::update()
{
    limitToScreen();
    
    if (mFlowField)
    {
        if (mFlowField->mFboDrawn)
        {
            float worldViscosity = 0.3;
            float flowFieldForceMag = 3.1;
            
            for (GridShapesIt it = mGridShapes.begin(); it < mGridShapes.end(); ++it)
            {
                HEMassParticle* shape = (*it);
                ofPoint flowFieldForce = mFlowField->getForceFieldForce(shape->getPos(),
                                                                        flowFieldForceMag);
                shape->applyForce(-flowFieldForce);
                
                
            }
        }
    }
    
    
    // head are repulsive for ach others...
    for (GridShapesIt it = mGridShapes.begin(); it < mGridShapes.end(); ++it)
    {
        HEMassParticle* shape = (*it);
        
        for (GridShapesIt it2 = it + 1; it2 < mGridShapes.end(); ++it2)
        {
            
            HEMassParticle* shape2 = (*it2);
            ofPoint relativePos = shape->getPos() - shape2->getPos();
            
            float relativePosLength = relativePos.lengthSquared();
            if (relativePosLength > 100*100)
            {
                relativePos *= 25;
                relativePos /= relativePosLength;
                shape2->applyForce(-relativePos);
                shape->applyForce(relativePos);
            }
        }
        
        // attract to center
        ofPoint shapePosToCenter = shape->getPos() - (*it)->mCentralPos;
        if (shapePosToCenter.lengthSquared() > 20000)
        {
            shapePosToCenter.normalize();
            shapePosToCenter *= -1.5;
            shape->applyForce(shapePosToCenter);
        }
        
        
    }

    
    for (GridShapesIt it = mGridShapes.begin(); it < mGridShapes.end(); ++it)
    {
        float worldViscosity = 1.0;
        (*it)->applyForce(- worldViscosity * (*it)->getVel());
        (*it)->incrementPos();
    }
    
}

void GridShapesGroup::draw()
{
    for (GridShapesIt it = mGridShapes.begin(); it < mGridShapes.end(); ++it)
    {
        //(*it)->draw();
        
        ofPushStyle();
        ofSetColor((*it)->mColor);
        
        ofPushMatrix();
        
        ofTranslate((*it)->getPos());
        ofRotate(56 * sin(0.8*ofGetElapsedTimef()));//(*it)->mHeading);
        
        mImages[(*it)->mShapeImgIndex]->draw(-(*it)->mWidth/2, -(*it)->mHeight/2,
                                             (*it)->mWidth, (*it)->mHeight);
        
        ofPopMatrix();
        
        ofPopStyle();
        
    }
}

// -----------------------------------------------------------------------------
void GridShapesGroup::setFlowField(HEFlowField* inFlowField)
{
    mFlowField = inFlowField;
}


// -----------------------------------------------------------------------------
void GridShapesGroup::limitToScreen()
{
    ofPoint screenTopLeft(0, 0);
    ofPoint screenSize = ofGetWindowSize();
    
    float margin = -50;
    
    ofPoint restrictedAreaTopLeft(screenTopLeft.x + margin,
                                  screenTopLeft.y + margin);
    ofPoint restrictedAreaBottomRigth(screenTopLeft.x + screenSize.x - margin,
                                      screenTopLeft.y + screenSize.y - margin);
    
    
    for (GridShapesIt it = mGridShapes.begin(); it < mGridShapes.end(); ++it)
    {
        ofPoint currentPos = (*it)->getPos();
        if (currentPos.x <= restrictedAreaTopLeft.x)
        {
            (*it)->setPos(ofPoint(restrictedAreaBottomRigth.x, currentPos.y));
        }
        else if (currentPos.x >= restrictedAreaBottomRigth.x)
        {
            (*it)->setPos(ofPoint(restrictedAreaTopLeft.x, currentPos.y));
        }
        
        if (currentPos.y <= restrictedAreaTopLeft.y)
        {
            (*it)->setPos(ofPoint(currentPos.x, restrictedAreaBottomRigth.y));
        }
        else if (currentPos.y >= restrictedAreaBottomRigth.y)
        {
            (*it)->setPos(ofPoint(currentPos.x, restrictedAreaTopLeft.y));
        }
    }
}


