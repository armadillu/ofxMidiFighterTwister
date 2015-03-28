#include "ofApp.h"

void ofApp::setup(){

	ofSetFrameRate(60);

	twister.setup();

	for(int i = 0; i < 4; i++){
		kits[i].loadFromFolder("inst" + ofToString(i));
	}

	ofAddListener(twister.eventEncoder, this, &ofApp::onEncoderUpdate);
	ofAddListener(twister.eventPushSwitch, this, &ofApp::onPushSwitchUpdate);
	ofAddListener(twister.eventSideButton, this, &ofApp::onSideButtonPressed);

	ofAddListener(twister.eventSequencerNote, this, &ofApp::onSequencerNote);
	ofAddListener(twister.eventSequencerFilter, this, &ofApp::onSequencerFilter);
}

void ofApp::update(){
	twister.update();
}


void ofApp::onEncoderUpdate(ofxMidiFighterTwister::EncoderEventArgs & a){
	ofLogNotice() << "Encoder '" << a.ID << "' Event! val: " << a.value;
}


void ofApp::onPushSwitchUpdate(ofxMidiFighterTwister::PushSwitchEventArgs & a){
	ofLogNotice() << "PushSwitch '" << a.ID << "' Event! val: " << a.value;
}

void ofApp::onSideButtonPressed(ofxMidiFighterTwister::SideButtonEventArgs & a){
	ofLogNotice() << "Side Button Pressed ";;
}

void ofApp::onSequencerNote(ofxMidiFighterTwister::SequencerNoteEventArgs & note){
	//ofLogNotice() << "onSequencerNote: " << note.toString();

	int instrumentIndex = ofMap(note.pitch, 36, 76, 0, kits[note.voice].getNumInstruments()-1);
	float vol = ofMap(note.velocity, 0, 127, 0, 1);

	if (note.on){
		kits[note.voice].getInstrumentAtIndex(instrumentIndex).setVolume(vol);
		//kits[note.voice].getInstrumentAtIndex(instrumentIndex).setSpeed(vol * 2);
		kits[note.voice].getInstrumentAtIndex(instrumentIndex).play();
	}
}

void ofApp::onSequencerFilter(ofxMidiFighterTwister::SequencerFilterEventArgs & filter){
	//ofLogNotice() << "onSequencerFilter voice " << filter.voice << " filter value: "<< filter.value;

	float speedMap = ofMap(filter.value, 0, 1, 0.1, 1.9, true);

	for(int i = 0; i < kits[filter.voice].getNumInstruments(); i++){
		kits[filter.voice].getInstrumentAtIndex(i).setSpeed(speedMap);
	}
}



void ofApp::keyPressed(int key){

	float val = 0.5 + 0.5 * sin(ofGetElapsedTimef() * 10);
	int val8 = ofGetFrameNum()%8;

	//all encoders on all pages [0..63] (4 pages, 16 per page)
	for(int encoderID = 0; encoderID < 16 * 4; encoderID++){

		switch (key) {

			//set color / encoder values
			case '1': twister.setEncoderRingValue(encoderID, val); break;
			case '2': twister.setEncoderColor(encoderID, val); break;

			//set encoder ring animations
			case '3': twister.setEncoderRingAnimationStrobe(encoderID, val8); break;
			case '4': twister.setEncoderRingAnimationPulse(encoderID, val8); break;
			case '5': twister.setEncoderRingBrightness(encoderID, val); break;

			//set encoder color animations
			case '6': twister.setEncoderColorAnimationStrobe(encoderID, val8); break;
			case '7': twister.setEncoderColorAnimationPulse(encoderID, val8); break;
			case '8': twister.setEncoderColorBrightness(encoderID, val); break;
			case '9': twister.setEncoderColorAnimationRainbow(encoderID); break;

			//turn off all animations
			case '0': twister.setEncoderAnimationsOff(encoderID); break;

			//set active bank page
			case 'q': twister.setBank(0);break;
			case 'w': twister.setBank(1);break;
			case 'e': twister.setBank(2);break;
			case 'r': twister.setBank(3);break;

			//sequencer control
			case '.': twister.sequencerPlay(); break;
			case ',': twister.sequencerPause(); break;

			case ' ': twister.setSequencerMode(); break;
				
			default:
				break;
		}
	}
}

