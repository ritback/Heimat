#pragma once

#include "ofMain.h"

class GridShape;
class HEFlowField;

class GridShapesGroup
{
public:
    GridShapesGroup(HEFlowField* inFlowField = 0);
    virtual ~GridShapesGroup();
    
public:
    void update();
    void draw();
    
public:
    void setFlowField(HEFlowField* inFlowField);
    
private:
    void limitToScreen();
    
private:
    typedef std::vector<GridShape*> GridShapes;
    typedef GridShapes::iterator GridShapesIt;
    GridShapes mGridShapes;
    
private:
    typedef std::vector<ofImage*> GridImages;
    typedef GridImages::iterator GridImagesIt;
    GridImages mImages;
    
private:
    HEFlowField* mFlowField;
    
};
