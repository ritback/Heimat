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
    // reinitialize detection
    invalidateROIs();

    // Open CV Haar face tracking
    mCVHaarFinder.findHaarObjects(inImg, 10, 10);

    // copy ROI
    for(unsigned int i = 0; i < mCVHaarFinder.blobs.size(); i++)
    {
        AnalysisROI roi(mCVHaarFinder.blobs[i].boundingRect);
        pushROI(roi);
    }
    ROIsIt it = mROIs.begin() + mCVHaarFinder.blobs.size();
    invalidateRestOfROIFrom(it);

}
