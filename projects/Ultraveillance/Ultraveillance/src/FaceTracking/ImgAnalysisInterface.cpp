#include "ImgAnalysisInterface.h"

AnalysisROI::AnalysisROI()
{
    invalidate();
}

AnalysisROI::~AnalysisROI()
{

}

void AnalysisROI::invalidate()
{
    mROI.set(ofPoint(-1, -1), ofPoint(-1, -1));
}

//------------------------------------------------------------------------------
ImgAnalysisInterface::ImgAnalysisInterface()
{

}

ImgAnalysisInterface::~ImgAnalysisInterface()
{

}


