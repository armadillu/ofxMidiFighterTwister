#pragma once

#include "ofMain.h"
#include "ofxMidiFighterTwister.h"

class InstrumentKit{

public:
	void loadFromFolder(string folder){
		ofDirectory d;
		d.allowExt("wav");
		d.listDir(folder);
		for(int i = 0; i < d.size(); i++){
			ofSoundPlayer p;
			string path = d.getPath(i);
			ofLog() << "loading " << path;
			p.loadSound(path);
			p.setMultiPlay(true);
			instruments.push_back(p);
		}
	}

	int getNumInstruments(){
		return instruments.size();
	}

	ofSoundPlayer& getInstrumentAtIndex(int index){
		return instruments[index];
	}

private:
	vector<ofSoundPlayer> instruments;
};


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		ofxMidiFighterTwister twister;

		void onEncoderUpdate(ofxMidiFighterTwister::EncoderEventArgs &);
		void onPushSwitchUpdate(ofxMidiFighterTwister::PushSwitchEventArgs &);
		void onSideButtonPressed(ofxMidiFighterTwister::SideButtonEventArgs &);

		void onSequencerNote(ofxMidiFighterTwister::SequencerNoteEventArgs &);
		void onSequencerFilter(ofxMidiFighterTwister::SequencerFilterEventArgs &);

		InstrumentKit kits[4];

	int framerate;
};
