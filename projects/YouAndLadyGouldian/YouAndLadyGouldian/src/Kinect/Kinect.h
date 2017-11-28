#pragma once

#include "ofMain.h"

#include "HE_Kinect.h"
#include "Silhouette.h"
#include "ScarecrowsTracker.h"

class BirdsFlock;

class Kinect
{
public:
    Kinect(BirdsFlock* inFlock);
    virtual ~Kinect();

public:
    void updateSilhoutte();
    void renderSilhouette();

public:
    void updateScarecrows();
    void renderScarecrows();

public:
    HEKinect mKinect;
    Silhouette mSilhouette;
    ScarecrowsTracker mScarecrowsTracker;
};
