#include "ofApp.h"

/*

ofShader mShader;
ofImage mVideoStreamImg;
ofVideoGrabber mCamera;
ofFbo mFbo;
*/
//--------------------------------------------------------------
void ofApp::setup()
{
    mCamWidth = 1280;
    mCamHeight = 720;

    mShader.load("shaders/CameraShampain");

    
    mCamera.setVerbose(false);
	
    std::vector<ofVideoDevice> devices = mCamera.listDevices();
    /*for (int i = 0; i < devices.size(); i++)
    {
        if (devices[i].bAvailable && strcmp(devices[i].deviceName.c_str(), "PC VGA Camer@ Plus") == 0)
        {
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
            mCamera.setDeviceID(devices[i].id);
            mCamera.setDesiredFrameRate(60);
            mCamera.initGrabber(mCamWidth, mCamHeight);
        }
    }
    */
    mCamera.setDeviceID(3);
    mCamera.setDesiredFrameRate(60);
    mCamera.initGrabber(mCamWidth, mCamHeight);

    ofSetVerticalSync(true);



    //mVideoStream.loadImage("images/Noise.png");

    //mVideoStream.allocate(mCamera.getTexture().getTextureData());

    mVideoStream.allocate(mCamWidth, mCamHeight, 0);

    //mFbo.allocate(mCamWidth, mCamHeight);
    //mFbo.allocate(mVideoStream.getWidth(), mVideoStream.getHeight());
    mFbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());


    mLogos[0].loadImage("images/logo-destroy-facebook.png");
    mLogos[1].loadImage("images/logo-destroy-twitter.png");

}

//--------------------------------------------------------------
void ofApp::update()
{
    mCamera.update();
    //if (mCamera.isFrameNew())
    {
        mVideoStream = mCamera.getTexture();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // draw in FBO
    mFbo.begin();
    ofClear(0, 0, 0, 255);
    mShader.begin();

    float pRes[3] = { mFbo.getWidth(), mFbo.getHeight(), 0 };
    mShader.setUniform3fv("uResolution", pRes, 1);

    mShader.setUniform1f("uGlobalTime", ofGetElapsedTimef());

    mShader.setUniformTexture("uVideoStream", mVideoStream, 1);
    float pVideoStreamRes[3] = { mVideoStream.getWidth(), mVideoStream.getHeight(), 0 };
    mShader.setUniform3fv("uVideoStreamResolution", pVideoStreamRes, 1);

    mVideoStream.draw(0, 0, mFbo.getWidth(), mFbo.getHeight());

    mShader.end();
    mFbo.end();

    // draw
    ofPushMatrix();
    ofTranslate(0, ofGetWindowHeight());
    ofScale(1, -1);
    mFbo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    ofPopMatrix();


    float logosDrawingSpacing = 10;
    float logosDrawingSize = 50;
    float logosPosY = ofGetWindowHeight() - logosDrawingSize - logosDrawingSpacing;

    for (int i = 0; i < NUM_LOGOS; ++i)
    {
        mLogos[i].draw(i * (logosDrawingSpacing + logosDrawingSize) + logosDrawingSpacing,
                       logosPosY,
                       logosDrawingSize, logosDrawingSize);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
