#include "ofApp.h"

void ofApp::setup() 
{

    enum YOLO_DATASET
    {
        YOLO_9000,
        MS_COCO,
        PASCAL_VOC
    };

    std::string cfgfile;
    std::string weightfile;
    std::string namesfile;
    switch(YOLO_9000)
    {
        case YOLO_9000: // YOLO2 with 9000 classes
            cfgfile = ofToDataPath("cfg/yolo9000.cfg");
            weightfile = ofToDataPath("yolo9000.weights");
            namesfile = ofToDataPath("cfg/9k.names");
            break;
        case MS_COCO: // MS COCO dataset(80 different classes)
            cfgfile = ofToDataPath("cfg/yolo.cfg");
            weightfile = ofToDataPath("yolo.weights");
            namesfile = ofToDataPath("cfg/coco.names");
            break;
        case PASCAL_VOC: // Pascal VOC dataset (20 different classes)
            cfgfile = ofToDataPath("cfg/yolo-voc.cfg");
            weightfile = ofToDataPath("yolo-voc.weights");
            namesfile = ofToDataPath("cfg/voc.names");
            break;
    }
    

	darknet.init( cfgfile, weightfile, namesfile );

	video.setDeviceID( 0 );
	video.setDesiredFrameRate( 30 );
	video.initGrabber( 640, 480 );
}

void ofApp::update()
{
	video.update();
}

void ofApp::draw()
{
    // detected objects with confidence < threshold are omitted
	float thresh = ofMap( ofGetMouseX(), 0, ofGetWidth(), 0, 1 );

    // if a detected object overlaps >maxOverlap with another detected
    // object with a higher confidence, it gets omitted
    float maxOverlap = 0.25;
    
	ofSetColor( 255 );
	video.draw( 0, 0 );

	if( video.isFrameNew() ) {
		std::vector< detected_object > detections = darknet.yolo( video.getPixels(), thresh, maxOverlap );

		ofNoFill();	
		for( detected_object d : detections )
		{
			ofSetColor( d.color );
			glLineWidth( ofMap( d.probability, 0, 1, 0, 8 ) );
			ofNoFill();
			ofDrawRectangle( d.rect );
			ofDrawBitmapStringHighlight( d.label + ": " + ofToString(d.probability), d.rect.x, d.rect.y + 20 );
            
            // optionally, you can grab the 1024-length feature vector associated
            // with each detected object
            vector<float> & features = d.features;
		}
	}
}
