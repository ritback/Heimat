#include "ofApp.h"
//------------------------------------------------------------------------------
void ofApp::initGui()
{
	mDisplayGui = false;

	mUTPanel.setup("User tracking control Panel"); // most of the time you don't need a name
	mUTPanel.add(mUTBgdRefresh.setup("Refresh background"));
	mUTPanel.add(mUTImgThresold.setup("Img threeshold", mUsersTracker.getImgThreshold(), -1, 255));
	mUTPanel.add(mUTImgBlur.setup("Img blur", mUsersTracker.getImgBlur(), 0, 50));

}

void ofApp::launchGui()
{
	mDisplayGui = true;

	mUTBgdRefresh.addListener(this, &ofApp::UTRefreshBgd);
	mUTImgThresold.addListener(this, &ofApp::UTSetThreshold);
	mUTImgBlur.addListener(this, &ofApp::UTSetBlur);

}

void ofApp::removeGui()
{
	mDisplayGui = false;

	mUTBgdRefresh.removeListener(this, &ofApp::UTRefreshBgd);
	mUTImgThresold.removeListener(this, &ofApp::UTSetThreshold);
	mUTImgBlur.removeListener(this, &ofApp::UTSetBlur);
}

//------------------------------------------------------------------------------
void ofApp::renderGui()
{
	mUTPanel.draw();
}

//------------------------------------------------------------------------------
void ofApp::UTRefreshBgd()
{
	mUsersTracker.refreshBackgroundNeeded();
}

void ofApp::UTSetThreshold(float &inThreshold)
{
	mUsersTracker.setImgThreshold(inThreshold);
}

void ofApp::UTSetBlur(float &inBlur)
{
	mUsersTracker.setImgBlur(inBlur);
}
