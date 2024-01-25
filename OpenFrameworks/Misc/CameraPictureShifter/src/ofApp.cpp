#include "ofApp.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup()
{
    mWindowWidth = ofGetWindowWidth();
    mWindowHeight = ofGetWindowHeight();

    for(int i = 0; i < 50; ++i)
    {

    }
    randomizeCameraDrawingPos();

    mCamWidth = 320*2;  // try to grab at this size.
    mCamHeight = 240*2;

    //get back a list of de;
    vector<ofVideoDevice> devices = mVidGrabber.listDevices();

    for(size_t i = 0; i < devices.size(); i++)
    {
        if(devices[i].bAvailable)
        {
            //log the device
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }
        else
        {
            //log the device and note it as unavailable
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    mVidGrabber.setDeviceID(0);
    mVidGrabber.setDesiredFrameRate(60);
    mVidGrabber.initGrabber(mCamWidth, mCamHeight);

    mVideoPixels.allocate(mCamWidth, mCamHeight, OF_PIXELS_RGB);
    mVideoTexture.allocate(mVideoPixels);
    ofSetVerticalSync(true);

}

//--------------------------------------------------------------
void ofApp::update()
{
    ofBackground(100, 100, 100);
    mVidGrabber.update();

    int currentIndex;
    int redOffsetedIndex;
    int greenOffsetedIndex;
    int blueOffsetedIndex;

    ofVec2f redRandomOffset;
    ofVec2f greenRandomOffset;
    ofVec2f blueRandomOffset;

    if(mVidGrabber.isFrameNew())
    {
        mRedOffset.x = ofRandom(1, 20);
        mRedOffset.y = ofRandom(1, 20);

        mGreenOffset.x = ofRandom(1, 20);
        mGreenOffset.y = ofRandom(1, 20);

        mBlueOffset.x = ofRandom(1, 20);
        mBlueOffset.y = ofRandom(1, 20);


        ofPixels & pixels = mVidGrabber.getPixels();
        for(size_t iCol = 0; iCol < pixels.getWidth(); iCol++)
        {
            for(size_t iLine = 0; iLine < pixels.getHeight(); iLine++)
            {
                currentIndex = pixels.getPixelIndex(iCol, iLine);

                redRandomOffset.x = 0;
                redRandomOffset.y = 0;
                greenRandomOffset.x = 0;
                greenRandomOffset.y = 0;
                blueRandomOffset.x = 0;
                blueRandomOffset.y = 0;

                int range = 20;
                if(ofRandom(0, 10)<1)
                {
                    redRandomOffset.x = ofRandom(0, range);
                    //redRandomOffset.y = ofRandom(0, range);

                    greenRandomOffset.x = ofRandom(0, range);
                    //greenRandomOffset.y = ofRandom(0, range);

                    blueRandomOffset.x = ofRandom(0, range);
                    //blueRandomOffset.y = ofRandom(0, range);
                }

                redOffsetedIndex = std::abs((int)pixels.getPixelIndex(iCol + mRedOffset.x + redRandomOffset.x,
                                                                      iLine + mRedOffset.y + redRandomOffset.y));
                greenOffsetedIndex = std::abs((int)pixels.getPixelIndex(iCol + mGreenOffset.x + greenRandomOffset.x,
                                                                        iLine + mGreenOffset.y + greenRandomOffset.y));
                blueOffsetedIndex = std::abs((int)pixels.getPixelIndex(iCol + mBlueOffset.x + blueRandomOffset.x,
                    iLine + mBlueOffset.y + blueRandomOffset.y));



                mVideoPixels[currentIndex] = pixels[redOffsetedIndex];
                mVideoPixels[currentIndex+1] = pixels[greenOffsetedIndex+1];
                mVideoPixels[currentIndex+2] = pixels[blueOffsetedIndex+2];
            }
            
        }
        //load the inverted pixels
        mVideoTexture.loadData(mVideoPixels);
    }

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetHexColor(0xffffff);
    mVideoTexture.draw(0, 0, mWindowWidth, mWindowHeight);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if(key == 's' || key == 'S')
    {
        mVidGrabber.videoSettings();
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
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
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


void ofApp::randomizeCameraDrawingPos()
{
    for ()
}