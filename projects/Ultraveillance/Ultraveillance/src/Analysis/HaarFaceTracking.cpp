#include "HaarFaceTracking.h"

ofxCvHaarFinder HaarFaceTracking::mCVHaarFinder;

HaarFaceTracking::HaarFaceTracking()
{
    static bool isSetup = false;
    if(!isSetup)
    {
        mCVHaarFinder.setup("haarcascade_frontalface_default.xml");
        isSetup = true;
    }
}

HaarFaceTracking::~HaarFaceTracking()
{

}

//------------------------------------------------------------------------------
void HaarFaceTracking::process(const ofxCvGrayscaleImage& inImg)
{
    // Open CV Haar face tracking
    mCVHaarFinder.findHaarObjects(inImg, 10, 10);
}
