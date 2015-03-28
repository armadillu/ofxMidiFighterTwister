#include "ofApp.h"

void ofApp::setup(){

	twister.setup();

	ofAddListener(twister.eventEncoder, this, &ofApp::onEncoderUpdate);
	ofAddListener(twister.eventPushSwitch, this, &ofApp::onPushSwitchUpdate);
}


void ofApp::onEncoderUpdate(ofxMidiFighterTwister::EncoderEventArgs & a){
	ofLogNotice() << "Encoder '" << a.ID << "' Event! val: " << a.value;
}


void ofApp::onPushSwitchUpdate(ofxMidiFighterTwister::PushSwitchEventArgs & a){
	ofLogNotice() << "PushSwitch '" << a.ID << "' Event! val: " << a.value;
}


void ofApp::keyPressed(int key){

	float val = 0.5 + 0.5 * sin(ofGetElapsedTimef() * 10);
	int val8 = ofGetFrameNum()%8;

	//all encoders on all pages [0..63] (4 pages, 16 per page)
	for(int encoderID = 0; encoderID < 16 * 4; encoderID++){

		switch (key) {

			case '1': twister.setEncoderRingValue(encoderID, val); break;
			case '2': twister.setEncoderColor(encoderID, val); break;
			case '3': twister.setEncoderRingAnimationStrobe(encoderID, val8); break;
			case '4': twister.setEncoderRingAnimationPulse(encoderID, val8); break;
			case '5': twister.setEncoderRingBrightness(encoderID, val); break;

			case '6': twister.setEncoderColorAnimationStrobe(encoderID, val8); break;
			case '7': twister.setEncoderColorAnimationPulse(encoderID, val8); break;
			case '8': twister.setEncoderColorBrightness(encoderID, val); break;
			case '9': twister.setEncoderColorAnimationRainbow(encoderID); break;
			case '0': twister.setEncoderAnimationsOff(encoderID); break;

			default:
				break;
		}
	}
}

