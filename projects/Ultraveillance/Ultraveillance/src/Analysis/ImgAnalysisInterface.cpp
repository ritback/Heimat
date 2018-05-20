#include "ImgAnalysisInterface.h"

ImgAnalysisInterface::ImgAnalysisInterface()
{

}

ImgAnalysisInterface::~ImgAnalysisInterface()
{
    for(ROIsIt it = mROIs.begin(); it != mROIs.end(); ++it)
    {
        delete (*it);
    }
}

//------------------------------------------------------------------------------
const ofRectangle* ImgAnalysisInterface::getROI(const int& inIndex)
{
    if(inIndex < 0 || inIndex >= mROIs.size())
    {
        return 0;
    }
    AnalysisROI* atIndex = mROIs[inIndex];
    if(atIndex->isValid())
    {
        return atIndex;
    }
    return 0;
}

int ImgAnalysisInterface::getROISize()
{
    if(mROIs.size() == 0) return 0;

    int size = 0;
    ROIsIt it = mROIs.begin();
    while(it != mROIs.end())
    {
        if((*it)->isValid())
        {
            ++size;
        }
        else
        {
            break;
        }
        ++it;
    }

    return size;
}

//------------------------------------------------------------------------------
void ImgAnalysisInterface::pushROI(AnalysisROI& inROI)
{
    AnalysisROI* roi = findFirstInvalidROI();
    *roi = inROI;
}

void ImgAnalysisInterface::invalidateRestOfROIFrom(ROIsIt& inIt)
{
    for(ROIsIt it = inIt; it != mROIs.end(); ++it)
    {
        (*it)->invalidate();
    }
}

void ImgAnalysisInterface::invalidateROIs()
{
    ROIsIt itBegin = mROIs.end();
    invalidateRestOfROIFrom(itBegin);
}

void ImgAnalysisInterface::findFirstInvalidROI(ROIsIt& outIt)
{

    for(outIt = mROIs.begin(); outIt != mROIs.end(); ++outIt)
    {
        if( ! (*outIt)->isValid() )
        {
            return;
        }
    }

    // add a new ROI emplacement in the ROI Arrray
    AnalysisROI* newROI = new AnalysisROI();
    mROIs.push_back(newROI); // will invalidate iterators => possible issues with other iterator loops running.. !!!
    //outROI = newROI;
    outIt = std::prev(mROIs.end());
}


AnalysisROI* ImgAnalysisInterface::findFirstInvalidROI()
{

    for(ROIsIt it = mROIs.begin(); it != mROIs.end(); ++it)
    {
        if(!(*it)->isValid())
        {
            return (*it);
        }
    }

    // add a new ROI emplacement in the ROI Arrray
    mROIs.push_back(new AnalysisROI()); // will invalidate iterators => possible issues with other iterator loops running.. !!!
    return mROIs.back();
}



