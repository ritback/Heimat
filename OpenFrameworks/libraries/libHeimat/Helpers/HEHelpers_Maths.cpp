#include "HEHelpers_Maths.h"


// -----------------------------------------------------------------------------
float heading2D(const ofPoint& v)
{
    if(v.lengthSquared() == 0) return 0;
    float angle = (float)-v.angle(ofPoint(1, 0, 0));
    angle = v.y > 0 ? -angle : angle;
    return angle;
}

float computeOrientedAngle(const ofPoint& Va, const ofPoint& Vb)
{
    float angle = Va.angle(Vb);

    ofPoint cross = Va.getCrossed(Vb);
    if(cross.dot(ofPoint(0, 0, 1)) < 0)
    {
        angle = -angle;
    }
    return angle;
}

// -----------------------------------------------------------------------------
template<class Type>
void clampValue(Type& outValToClamp, const Type& inMinVal, const Type& inMaxVal)
{
    if(outValToClamp > inMaxVal)
    {
        outValToClamp = inMaxVal;
    }
    else if(outValToClamp < inMinVal)
    {
        outValToClamp = inMinVal;
    }
}

// -----------------------------------------------------------------------------
template<typename type>
void scaleToRange(type& value,
                  const type& inBaseRangeMin, const type& inBaseRangeMax,
                  const type& inOutRangeMin, const type& inOutRangeMax)
{
    if((inBaseRangeMax - inBaseRangeMin) != 0)
        value = ((inOutRangeMax - inOutRangeMin) * (value - inBaseRangeMin) / (inBaseRangeMax - inBaseRangeMin)) + inOutRangeMin;
    else
        value = 0;
}


void scaleToRange(ofPoint& value,
                  const ofPoint& inBaseRangeMin, const ofPoint& inBaseRangeMax,
                  const ofPoint& inOutRangeMin, const ofPoint& inOutRangeMax)
{
    scaleToRange(value.x, inBaseRangeMin.x, inBaseRangeMax.x, inOutRangeMin.x, inOutRangeMax.x);
    scaleToRange(value.y, inBaseRangeMin.y, inBaseRangeMax.y, inOutRangeMin.y, inOutRangeMax.y);
    scaleToRange(value.z, inBaseRangeMin.z, inBaseRangeMax.z, inOutRangeMin.z, inOutRangeMax.z);
}

