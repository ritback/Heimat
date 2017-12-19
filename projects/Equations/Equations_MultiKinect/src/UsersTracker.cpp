#include "UsersTracker.h"

UsersTracker::UsersTracker()
	: mKinects()
    , mDepthImageMultiKinect(0)
    , mDepthLessBkgnd(0)
	, mSafeZone(ofPoint(-1000, -1000))
{
    int numKinect = Kinect::getSensorNumber();
    for(int i = 0; i < numKinect; ++i)
    {
        mKinects.push_back(new Kinect());
    }

    mDepthImageMultiKinect = new DepthImageMultiKinectRotated(&mKinects);

    mDepthLessBkgnd = new DepthLessBkgndImage(&mDepthImageMultiKinect->mSingleDepthImage);


	for (int i = 0; i < NUM_USERS; ++i)
	{
		ofPoint newUser(mSafeZone);
		mUsers.push_back(newUser);
	}

    mDepthLessBkgnd->refreshBackgroungNeeded();
}

UsersTracker::~UsersTracker()
{
    if(mDepthImageMultiKinect)
        delete mDepthImageMultiKinect;
    if(mDepthLessBkgnd)
        delete mDepthLessBkgnd;

    for(int i = 0; i < mKinects.size(); ++i)
    {
        delete mKinects[i];
        mKinects[i] = 0;
    }

    mUsers.clear();
}

//--------------------------------------------------------------
void UsersTracker::update()
{
    if(mKinects.size() == 0)
        return;
    for(int i = 0; i < mKinects.size(); ++i)
    {
        if (!mKinects[i]->isAvailable())
            return;
    }

    mDepthImageMultiKinect->update();
    mDepthLessBkgnd->update();


	// update blob detection
    ofPoint detectionSize = getRoomSize();
	int diag = detectionSize.x * detectionSize.y;

	int minArea = diag / 100;
	int maxArea = diag / 3;
	bool bFindHoles = false;
	bool bUseApproximation = true;
	mContourFinder.findContours(mDepthLessBkgnd->mDepthLessBkgndImage,
								minArea,
								maxArea,
                                NUM_USERS,
								bFindHoles,
								bUseApproximation);


    int mNumBlob= mContourFinder.nBlobs;
    mNumActiveUser = mNumBlob;

    UsersIt it = mUsers.begin();
	for (int i = 0; i < mNumBlob; ++i)
	{
        ofPoint userPosOnImage(0, 0);
        float blobArea =  mContourFinder.blobs[i].area;
        if(blobArea < maxArea / 5)
        {
            (*it) = mContourFinder.blobs[i].centroid;
            ++it;
        }
        else // if area is to big it should be divided
        {
            ofRectangle boundingRect = mContourFinder.blobs[i].boundingRect;
            float boundingRectWidth = boundingRect.getWidth();
            float boundingRectHeight = boundingRect.getHeight();

            ofPoint user1Pos = boundingRect.getTopLeft();
            ofPoint user2Pos = boundingRect.getTopLeft();
            if(boundingRectWidth < boundingRectHeight)
            {
                user1Pos.x += boundingRectWidth * 1 / 2;
                user1Pos.y += boundingRectHeight * 1 / 4;
                user2Pos.x += boundingRectWidth * 1 / 2;
                user2Pos.y += boundingRectHeight * 3 / 4;
            }
            else
            {
                user1Pos.x += boundingRectWidth * 1 / 4;
                user1Pos.y += boundingRectHeight * 1 / 2;
                user2Pos.x += boundingRectWidth * 3 / 4;
                user2Pos.y += boundingRectHeight * 1 / 2;
            }

            (*it) = user1Pos;
            ++it;
            (*it) = user2Pos;
            ++it;
            ++mNumActiveUser;
        }
	}

	for (it; it != mUsers.end(); ++it)
	{
		(*it) = mSafeZone;
	}
}

//--------------------------------------------------------------
void UsersTracker::refreshBackgroundNeeded()
{
    mDepthLessBkgnd->refreshBackgroungNeeded();
}

void UsersTracker::render()
{
    for(int i = 0; i < mKinects.size(); ++i)
    {
        if(!mKinects[i]->isAvailable())
        {
            ofBackground(255, 0, 0);
            ofSetColor(0);
            for(int i = 0; i < ofGetWindowWidth() / 100; ++i)
                for(int j = 0; j < ofGetWindowHeight() / 50; ++j)
                    ofDrawBitmapString("NO KINECT!", i * 100, j * 50);
            return;
        }
    }

    ofPoint rendersSize(ofGetWindowWidth() / 3, ofGetWindowHeight());

    mDepthImageMultiKinect->render(ofPoint(0, 0), rendersSize);
    mDepthLessBkgnd->renderBkgnd(ofPoint(ofGetWindowWidth() * 1 / 3, 0), rendersSize);

    mDepthLessBkgnd->render(ofPoint(ofGetWindowWidth() * 2 / 3, 0), rendersSize);
    renderBlobs(ofPoint(ofGetWindowWidth() * 2 / 3, 0), rendersSize);
    renderUsers(ofPoint(ofGetWindowWidth() * 2 / 3, 0), rendersSize);
}

void UsersTracker::renderBlobs(const ofPoint& inTopLeft,
                               const ofPoint& inSize)
{
	mContourFinder.draw(inTopLeft.x, inTopLeft.y, inSize.x, inSize.y);

    ofPoint detectionSize = getRoomSize();
    ofPoint imageSizeRatio = inSize / detectionSize;

	ofPushStyle();
	ofSetColor(255, 0, 0);
    ofPoint boidCenter;
	for (int i = 0; i < mContourFinder.nBlobs; i++)
	{
		boidCenter = mContourFinder.blobs[i].centroid * imageSizeRatio;
		ofDrawEllipse(boidCenter + inTopLeft, 20, 20);
	}
	ofPopStyle();
}

void UsersTracker::renderUsers(const ofPoint& inTopLeft,
                               const ofPoint& inSize)
{
    ofPoint detectionSize = getRoomSize();
    ofPoint imageSizeRatio = inSize / detectionSize;

	ofPushStyle();
	ofSetColor(0, 255, 0);
	for (UsersIt it = mUsers.begin();
		 it != mUsers.end();
		 ++it)
	{
        ofDrawEllipse((*it)*imageSizeRatio + inTopLeft, 10, 10);
	}
	ofPopStyle();
}


//--------------------------------------------------------------
ofPoint UsersTracker::getRoomSize()
{
    ofPoint detectionSize((mDepthImageMultiKinect->mSingleDepthImage).getWidth(),
                          (mDepthImageMultiKinect->mSingleDepthImage).getHeight(),
                          0);

    return detectionSize;
}

void UsersTracker::getUserPosInRoom(ofPoint** outUsers, int* outNumUsers)
{
    (*outUsers) = &(mUsers[0]);
    *outNumUsers = mNumActiveUser;
}

int UsersTracker::getNumActiveUser()
{
    return mNumActiveUser;
}

//--------------------------------------------------------------
void UsersTracker::setImgThreshold(float inThreshold)
{
    mDepthLessBkgnd->setThreshold(inThreshold);
}

float UsersTracker::getImgThreshold()
{
	return mDepthLessBkgnd->getThreshold();
}

void UsersTracker::setImgBlur(float inBlur)
{
    mDepthLessBkgnd->setBlur(inBlur);
}

float UsersTracker::getImgBlur()
{
	return mDepthLessBkgnd->getBlur();
}

