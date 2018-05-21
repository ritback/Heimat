#include "Yolo2ObjRecognition.h"

Yolo2ObjRecognition::Yolo2ObjRecognition()
{
    mYolo.setup();
}

Yolo2ObjRecognition::~Yolo2ObjRecognition()
{

}

//------------------------------------------------------------------------------
void Yolo2ObjRecognition::process(const ofxCvGrayscaleImage& inImg)
{
    // Yolo2 tracking.
    ofPixels* pImgPixels = const_cast<ofPixels*> (&(inImg.getPixels()));
    mLastResults = mYolo.detect(*pImgPixels);
}

