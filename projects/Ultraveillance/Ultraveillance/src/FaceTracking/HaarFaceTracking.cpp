#include "HaarFaceTracking.h"

HaarFaceTracking::HaarFaceTracking()
{
    mCVHaarFinder.setup("haarcascade_frontalface_default.xml");
}

HaarFaceTracking::~HaarFaceTracking()
{

}

//------------------------------------------------------------------------------
void HaarFaceTracking::process(const ofxCvGrayscaleImage& inImg)
{
    mCVHaarFinder.findHaarObjects(inImg, 10, 10);
}
