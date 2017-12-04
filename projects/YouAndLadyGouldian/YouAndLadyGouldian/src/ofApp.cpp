#include "ofApp.h"

ofApp::ofApp()
    : ofBaseApp()
    , mFlock()
#if USE_KINECT
    , mKinect(&mFlock)
#endif
    , mJungleBackgound()
    , mForest()
    , mGui(this)
    , mColonyManager(&mFlock)
{
    
}

ofApp::~ofApp()
{

}

//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
    mGui.initGui();
    mGui.launchGui();
}

void ofApp::exit()
{

}

//------------------------------------------------------------------------------
void ofApp::update()
{
    mColonyManager.update();
    
    mJungleBackgound.update();
    
    mForest.update();

#if USE_KINECT
    mKinect.updateSilhoutte();
    mKinect.updateScarecrows();
#endif

    mFlock.update();
}

void ofApp::draw()
{   
    ofBackground(0);
    
    mJungleBackgound.render();
    
    mForest.render();


#if USE_KINECT

    if(mGui.mKinectParametersGui.mSilhouetteRenderNormal)
        mKinect.renderSilhouette();
    else if(mGui.mKinectParametersGui.mSilhouetteRenderStream)
        mKinect.mSilhouette.renderStreamImage();
    else if(mGui.mKinectParametersGui.mSilhouetteRenderBackground)
        mKinect.mSilhouette.renderBkgnd();
    else if(mGui.mKinectParametersGui.mSilhouetteRenderDepthLessBackground)
        mKinect.mSilhouette.renderDepthLessBkgnd();

    if(mGui.mKinectParametersGui.mRenderSkeletons)
        mKinect.renderScarecrows();
#endif

    drawFlock();

    mGui.renderGui();

}

void ofApp::drawFlock()
{
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

    mFlock.render();

    if(mGui.mFlockParametersGui.mRenderWorld)
        mFlock.renderWorld();

    ofPopMatrix();
}



//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch(key)
    {
        case 'f': case 'F':
            ofToggleFullscreen();
            break;
#if USE_KINECT
        case 'b': case 'B':
            mKinect.mSilhouette.refreshBackground();
            break;
#endif

        case 'd': case 'D':
            mGui.mDisplayGui = !mGui.mDisplayGui;
            if(mGui.mDisplayGui)
                mGui.launchGui();
            else
                mGui.removeGui();

        case 'S':
        case 's':
            mGui.saveParameters();
            break;
        case 'L':
        case 'l':
            mGui.loadParameters();
            break;
            break;
    }
}

void ofApp::keyReleased(int key){
    
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    
}

void ofApp::mouseDragged(int x, int y, int button)
{
    
}

void ofApp::mousePressed(int x, int y, int button)
{
    
}

void ofApp::mouseReleased(int x, int y, int button)
{
    Forest::createTreeAt(ofPoint(x, y));
    //Forest::createTreeAt(ofPoint(x, y));
}

void ofApp::mouseEntered(int x, int y)
{
    
}

void ofApp::mouseExited(int x, int y)
{
    
}

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    ofPoint worldLimitMin(-ofGetWindowWidth() / 2, -ofGetWindowHeight() / 2);
    ofPoint worldLimitMax(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

    HEBoxWorld* boxWorld = mFlock.getWorld();

    boxWorld->setWorldLimitMin(worldLimitMin);
    boxWorld->setWorldLimitMax(worldLimitMax);

    float margin = 100;
    ofPoint worldLimitDistanceMin(worldLimitMin.x + margin, worldLimitMin.y + margin);
    ofPoint worldLimitDistanceMax(worldLimitMax.x - margin, worldLimitMax.y - margin);

    boxWorld->setWorldLimitDistanceMin(worldLimitDistanceMin);
    boxWorld->setWorldLimitDistanceMax(worldLimitDistanceMax);
}

void ofApp::gotMessage(ofMessage msg)
{
    
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}

//------------------------------------------------------------------------------
BirdsFlock* ofApp::getFlock()
{
    return &mFlock;
}

#if USE_KINECT
Kinect* ofApp::getKinect()
{
    return &mKinect;
}
#endif

