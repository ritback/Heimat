#pragma once

#include "HE_KinectDef.h"

class HEKinect;

class HEDepthStreamHandlerInterface
{
public:
    HEDepthStreamHandlerInterface();
	virtual ~HEDepthStreamHandlerInterface();

public:
	virtual void setPixel(ofPixels* inDepthChannel,
						  int inPixelIndex,
						  unsigned char inKinectGreyLevel) = 0;
};

class HESkeletonsStreamHandlerInterface
{
public:
    HESkeletonsStreamHandlerInterface();
    virtual ~HESkeletonsStreamHandlerInterface();

public:
    virtual void processSkeletons(NUI_SKELETON_FRAME& skeletonFrame) = 0;
};


// --------------------------------------------------------
class HEKinectStreamHandler
{
public:
	HEKinectStreamHandler(INuiSensor* inKinect,
				  NUI_IMAGE_RESOLUTION inStreamResolution = NUI_IMAGE_RESOLUTION_640x480);
	virtual ~HEKinectStreamHandler();

public:
	void streamDepthTo(HEDepthStreamHandlerInterface* inToStream,
					   ofPixels* inDepthChannel,
					   float inWaitingTime = 0);

public:
    void streamSkeletonsTo(HESkeletonsStreamHandlerInterface* inToStream,
                           float inWaitingTime = 0);

public:
	ofPoint getStreamResolution();

public:
	void setGreyLevelMax(float inGreyLevelMax);
	void setGreyLevelMin(float inGreyLevelMin);

protected:
	INuiSensor* mKinect;

protected:
	float mGreyLevelMax;
	float mGreyLevelMin;

protected:
	HANDLE mDepthStreamHandle;
	HANDLE mNextDepthFrameEvent;
    HANDLE mSkeletonStreamHandle;
    HANDLE mNextSkeletonEvent;
	ofPoint mStreamResolution;
};

// --------------------------------------------------------
class HEKinect
{
public:
    HEKinect(bool bGetSkeleton = true, bool bGetDepthImage = true);
    virtual ~HEKinect();

public:
	HEKinectStreamHandler* getStreamHandler();

public:
    bool isAvailable();

public:
    static int getSensorNumber();

private:
    bool createFirstConnected(bool bGetSkeleton, bool bGetDepthImage);

private:
	INuiSensor* mNuiSensor;
	HEKinectStreamHandler* mStreamHandler;
    static int mSensorIndex;

private:
    bool mIsConnected;
};
