#pragma once

#include "ofMain.h"

// -----------------------------------------------------------------------------
float heading2D(const ofPoint& v);
float computeOrientedAngle(const ofPoint& Va, const ofPoint& Vb);

// -----------------------------------------------------------------------------
template<class Type>
void clampValue(Type& outValToClamp, const Type& inMinVal, const Type& inMaxVal);

// -----------------------------------------------------------------------------
template<typename type>
void scaleToRange(type& value,
                  const type& inBaseRangeMin, const type& inBaseRangeMax,
                  const type& inOutRangeMin, const type& inOutRangeMax);

void scaleToRange(ofPoint& value,
                  const ofPoint& inBaseRangeMin, const ofPoint& inBaseRangeMax,
                  const ofPoint& inOutRangeMin, const ofPoint& inOutRangeMax);