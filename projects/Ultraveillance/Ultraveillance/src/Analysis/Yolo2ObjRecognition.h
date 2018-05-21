#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxYolo2.h"


class Yolo2ObjRecognition
{
public:
    Yolo2ObjRecognition();
    virtual ~Yolo2ObjRecognition();

public:
    virtual void process(const ofxCvGrayscaleImage& inImg);

public:
    ofxYolo2 mYolo;
    std::vector<bbox_t> mLastResults;
};



