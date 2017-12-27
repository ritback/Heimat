#include "ofApp.h"

#include "UsersTracking/UsersTracker.h"
#include "Flock/HE_FlockingWorld.h"
#include "Flock/HE_Flock.h"

//------------------------------------------------------------------------------
void ofApp::initGui()
{
	mDisplayGui = false;

	mGuiPanel.setup("Control Panel");
	ofPoint worldLimitMin = mFlock->getWorldLimitMin();
	ofPoint worldLimitMax = mFlock->getWorldLimitMax();
	
    mGuiPanel.add(mFlockRenderWorld.setup("Render World Limits", false));
	mGuiPanel.add(mFlockWorldLimitMinX.setup("World Limit Min X", worldLimitMin.x, -1200, 0));
	mGuiPanel.add(mFlockWorldLimitMinY.setup("World Limit Min Y", worldLimitMin.y, -1200, 0));
	mGuiPanel.add(mFlockWorldLimitMaxX.setup("World Limit Max X", worldLimitMax.x, 0, 1200));
	mGuiPanel.add(mFlockWorldLimitMaxY.setup("World Limit Max Y", worldLimitMax.y, 0, 1200));

    
    ofPoint roomLimitMin = mFlock->getWorldLimitMin();
    ofPoint roomLimitMax = mFlock->getWorldLimitMax();
    mGuiPanel.add(mRenderUsers.setup("Render Users", false));
    mGuiPanel.add(mRenderUsersRoom.setup("Render Room Limits", false));
    mGuiPanel.add(mUsersRoomLimitMinX.setup("Room Limit Min X", roomLimitMin.x, -1200, 0));
    mGuiPanel.add(mUsersRoomLimitMinY.setup("Room Limit Min Y", roomLimitMin.y, -1200, 0));
    mGuiPanel.add(mUsersRoomLimitMaxX.setup("Room Limit Max X", roomLimitMax.x, 0, 1200));
    mGuiPanel.add(mUsersRoomLimitMaxY.setup("Room Limit Max Y", roomLimitMax.y, 0, 1200));

    mGuiPanel.add(mUsersInfluenceCohesion.setup("Cohesion", 1, 0, mUsersTracker->getUsersInfluenceCohesionMaxValue()));
    mGuiPanel.add(mUsersInfluenceAlignement.setup("Alignement", 1, 0, mUsersTracker->getUsersInfluenceAlignementMaxValue()));
    mGuiPanel.add(mUsersInfluenceSeparation.setup("Separation", 1, 0, mUsersTracker->getUsersInfluenceSeparationMaxValue()));
}

void ofApp::launchGui()
{
	mDisplayGui = true;

	mFlockWorldLimitMinX.addListener(this, &ofApp::resizeFlockWorld);
	mFlockWorldLimitMinY.addListener(this, &ofApp::resizeFlockWorld);
	mFlockWorldLimitMaxX.addListener(this, &ofApp::resizeFlockWorld);
	mFlockWorldLimitMaxY.addListener(this, &ofApp::resizeFlockWorld);

    mUsersRoomLimitMinX.addListener(this, &ofApp::resizeUsersRoom);
    mUsersRoomLimitMinY.addListener(this, &ofApp::resizeUsersRoom);
    mUsersRoomLimitMaxX.addListener(this, &ofApp::resizeUsersRoom);
    mUsersRoomLimitMaxY.addListener(this, &ofApp::resizeUsersRoom);

    mUsersInfluenceCohesion.addListener(this, &ofApp::changeUsersInfluenceCohesion);
    mUsersInfluenceAlignement.addListener(this, &ofApp::changeUsersInfluenceAlignement);
    mUsersInfluenceSeparation.addListener(this, &ofApp::changeUsersInfluenceSeparation);
}

void ofApp::removeGui()
{
	mDisplayGui = false;

	mFlockWorldLimitMinX.removeListener(this, &ofApp::resizeFlockWorld);
	mFlockWorldLimitMinY.removeListener(this, &ofApp::resizeFlockWorld);
	mFlockWorldLimitMaxX.removeListener(this, &ofApp::resizeFlockWorld);
	mFlockWorldLimitMaxY.removeListener(this, &ofApp::resizeFlockWorld);

    mUsersRoomLimitMinX.removeListener(this, &ofApp::resizeUsersRoom);
    mUsersRoomLimitMinY.removeListener(this, &ofApp::resizeUsersRoom);
    mUsersRoomLimitMaxX.removeListener(this, &ofApp::resizeUsersRoom);
    mUsersRoomLimitMaxY.removeListener(this, &ofApp::resizeUsersRoom);


    mUsersInfluenceCohesion.removeListener(this, &ofApp::changeUsersInfluenceCohesion);
    mUsersInfluenceAlignement.removeListener(this, &ofApp::changeUsersInfluenceAlignement);
    mUsersInfluenceSeparation.removeListener(this, &ofApp::changeUsersInfluenceSeparation);

}

//------------------------------------------------------------------------------
void ofApp::renderGui()
{
    mUsersInfluenceCohesion = mUsersTracker->getUsersInfluenceCohesion();
    mUsersInfluenceAlignement = mUsersTracker->getUsersInfluenceAlignement();
    mUsersInfluenceSeparation = mUsersTracker->getUsersInfluenceSeparation();

	mGuiPanel.draw();
}


//------------------------------------------------------------------------------
void ofApp::resizeFlockWorld(float & inLimit)
{
	ofPoint worldLimitMin(mFlockWorldLimitMinX, mFlockWorldLimitMinY);
	ofPoint worldLimitMax(mFlockWorldLimitMaxX, mFlockWorldLimitMaxY);
	mFlock->setWorldLimitMin(worldLimitMin);
	mFlock->setWorldLimitMax(worldLimitMax);
}

void ofApp::resizeUsersRoom(float & inLimit)
{
    ofPoint roomLimitMin(mUsersRoomLimitMinX, mUsersRoomLimitMinY);
    ofPoint roomLimitMax(mUsersRoomLimitMaxX, mUsersRoomLimitMaxY);
    mUsersTracker->setRoomLimitMin(roomLimitMin);
    mUsersTracker->setRoomLimitMax(roomLimitMax);
}


//------------------------------------------------------------------------------
void ofApp::changeUsersInfluenceCohesion(float & inValue)
{
    mUsersTracker->changeUsersInfluenceCohesion(inValue);
}

void ofApp::changeUsersInfluenceAlignement(float & inValue)
{
    mUsersTracker->changeUsersInfluenceAlignement(inValue);
}

void ofApp::changeUsersInfluenceSeparation(float & inValue)
{
    mUsersTracker->changeUsersInfluenceSeparation(inValue);
}
