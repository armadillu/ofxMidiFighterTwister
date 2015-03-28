#pragma once

#include "ofMain.h"
#include "ofxMidiFighterTwister.h"

class ofApp : public ofBaseApp{
	public:
		void setup();

		void keyPressed(int key);

		ofxMidiFighterTwister twister;

		void onEncoderUpdate(ofxMidiFighterTwister::EncoderEventArgs &);
		void onPushSwitchUpdate(ofxMidiFighterTwister::PushSwitchEventArgs &);
};
