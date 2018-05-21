#include "Yolo2ObjRecognition.h"

#define USE_YOLO 1

ofxYolo2 Yolo2ObjRecognition::mYolo;

Yolo2ObjRecognition::Yolo2ObjRecognition()
{
#if USE_YOLO == 1
    static bool isSetup = false;
    if(!isSetup)
    {
        mYolo.setup();
        isSetup = true;
    }
#endif
}

Yolo2ObjRecognition::~Yolo2ObjRecognition()
{

}

//------------------------------------------------------------------------------
void Yolo2ObjRecognition::process(ofPixels* inImg)
{
#if USE_YOLO == 1
    // Yolo2 tracking.
    if(inImg)
    {
        mLastResults = mYolo.detect(*inImg);
    }
#endif
}

