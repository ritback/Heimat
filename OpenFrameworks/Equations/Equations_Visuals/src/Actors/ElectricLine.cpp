#include "ElectricLine.h"

#include <math.h>


ElectricLine::ElectricLine()
: mStart(ofPoint(0,0,0))
, mEnd()
{
    init();
}

ElectricLine::ElectricLine(const ofPoint& inStart, const ofPoint& inEnd)
: mStart(inStart)
, mEnd(inEnd)
{
    
    init();
}

ElectricLine::~ElectricLine()
{
    for (LightningLinesIt it = mLightningLines.begin();
         it < mLightningLines.end();
         ++it)
    {
        delete (*it);
    }
    
    mLightningLines.clear();
}

// -----------------------------------------------------------------------------

void ElectricLine::update(const ofPoint* inNewStart, const ofPoint* inNewEnd)
{
    /*
    static int stop = 0;
    if (stop != 10)
    {
        ++stop;
        return;
    }
    stop = 0;
    */
    
    mIsVisible = true;
    
    if (inNewStart)
        mStart = *inNewStart;
    
    if (inNewEnd)
        mEnd = *inNewEnd;
    
    
    ofPoint vecDir;
    vecDir.x = mEnd.x - mStart.x;
    vecDir.y = mEnd.y - mStart.y;
    vecDir.z = mEnd.z - mStart.z;
    
    for (LightningLinesIt it = mLightningLines.begin();
         it < mLightningLines.end();
         ++it)
    {
        float noiseScale = 5;
        for (int i = 0; i < (*it)->size(); ++i)
        {
            float t = (float)i / ((*it)->size()-1);
            float posX = vecDir.x * t + mStart.x;
            float posY = vecDir.y * t + mStart.y;
            float posZ = vecDir.z * t + mStart.z;
            
            float noiseX = ofRandom(-1, 1) * sin(t * PI) * noiseScale + ofRandom(-1, 1);
            float noiseY = ofRandom(-1, 1) * sin(t * PI) * noiseScale + ofRandom(-1, 1);
            float noiseZ = ofRandom(-1, 1) * sin(t * PI) * noiseScale + ofRandom(-1, 1);
            
            (*(*it))[i].x = posX + noiseX;
            (*(*it))[i].y = posY + noiseY;
            (*(*it))[i].z = posZ + noiseZ;
        }
    }
}

void ElectricLine::render()
{
    if (!mIsVisible) return;
    
    //ofDrawLine(mStart, mEnd);
    
    for (LightningLinesIt it = mLightningLines.begin();
         it < mLightningLines.end();
         ++it)
    {
        (*it)->draw();
        for (int i = 0; i < ((*it)->size()); ++i)
        {
            ofDrawSphere((*(*it))[i], 2);
        }
    }
}

// -----------------------------------------------------------------------------
void ElectricLine::resetLine(const ofPoint* inNewStart, const ofPoint* inNewEnd)
{
    if (inNewStart)
        mStart = *inNewStart;
    
    if (inNewEnd)
        mEnd = *inNewEnd;
}

void ElectricLine::setInvisible()
{
    mIsVisible = false;
}



// -----------------------------------------------------------------------------

void ElectricLine::init()
{
    int mNumLightning = 1;
    
    for (int j = 0; j < mNumLightning; ++j)
    {
        ofPolyline* newLine = new ofPolyline();
        int numVertex = (int)ofRandom(2, 4);
        
        for (int i = 0; i < numVertex; ++i)
        {
            newLine->addVertex(0, 0, 0);
        }
        
        mLightningLines.push_back(newLine);
    }
    
    update();
}

