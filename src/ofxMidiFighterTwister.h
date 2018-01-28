//
//  ofxMidiFighterTwister.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 27/3/15.
//
//

#ifndef __emptyExample__ofxMidiFighterTwister__
#define __emptyExample__ofxMidiFighterTwister__

#include "ofMain.h"
#include "ofxMidi.h"

class ofxMidiFighterTwister: public ofxMidiListener{

public:

	struct EncoderEventArgs{
		int ID;
		int value;
	};

	struct PushSwitchEventArgs{
		int ID;
		int value;
	};

	struct SideButtonEventArgs{
		int buttonID; // [0 .. 5] ; starting bottom left clockwise
	};

	struct SequencerNoteEventArgs{
		int voice; //[0..3] (mapped to the 4 columns of the MFT)
		bool on; //noteOn / noteOff
		int pitch;
		int velocity;
		string toString(){
			return "Note" + string(on?"On":"Off") + " Voice:" + ofToString(voice) + " Pitch: " +
			ofToString(pitch) + " Velocity: " + ofToString(velocity);
		}
	};

	struct SequencerFilterEventArgs{
		int voice; //[0..3]
		float value; // [0..1]
	};

	void setup();

	// for the sequencer feature
	void update(); //send midi clock to MFT, in case you want to use the sequecner feature

	void sequencerPlay(){
		midiOut.sendControlChange(8, 14, 127);
	}

	void sequencerPause(){
		midiOut.sendControlChange(8, 14, 0);
	}

	void draw();

	//light up the ring around the encoders
	void setEncoderRingValue(int encoder, float value); // value[0..1] - 127 values

	//Set the hue of the colored LED segment under each encoder
	//0 is blue, 0.25 is green, 0.5 is yellow, 0.75 is red, 1.0 is purplish
	void setEncoderColor(int encoder, float hue); // hue[0..1] 127 values

	//manually change selected bank (same as pressing middle side buttons)
	void setBank(int bank);  //[0..3] allowed

	void setSequencerMode(){
		midiOut.sendControlChange(4, 0, 127);
		midiOut.sendControlChange(4, 1, 127);
	}

    static int relativeMidi(int midi) {
        return (midi == MIDI_INCREASE) ? 1 : -1;
    }
    
    static float mapMidi(int midi, float targetMin, float targetMax) {
        return ofMap(midi, MIDI_MIN, MIDI_MAX, targetMin, targetMax);
    }

	//Ring Animations
	void setEncoderRingAnimationStrobe(int encoder, unsigned char strobe); //strobe[0..7]  possible values
	void setEncoderRingAnimationPulse(int encoder, unsigned char pulse); //pulse[0..7]  possible values
	void setEncoderRingBrightness(int encoder, float brightness); //brightness[0..1] 30 values

	//Color Animations
	void setEncoderColorAnimationStrobe(int encoder, unsigned char strobe); //strobe[0..7]  possible values
	void setEncoderColorAnimationPulse(int encoder, unsigned char pulse); //pulse[0..7]  possible values
	void setEncoderColorBrightness(int encoder, float brightness); //brightness[0..1] 30 values
	void setEncoderColorAnimationRainbow(int encoder);

	//all animations off
	void setEncoderAnimationsOff(int encoder);

	//listen to User events events
	ofEvent<EncoderEventArgs>		eventEncoder;
	ofEvent<PushSwitchEventArgs>	eventPushSwitch;
	ofEvent<SideButtonEventArgs>	eventSideButton;

	ofEvent<SequencerNoteEventArgs>	eventSequencerNote;
	ofEvent<SequencerFilterEventArgs>	eventSequencerFilter;

    static int const MIDI_DECREASE = 63;
    static int const MIDI_INCREASE = 65;
    static int const MIDI_MIN = 0;
    static int const MIDI_MAX = 127;
    static int const NUM_ENCODERS = 64;

private:

	void newMidiMessage(ofxMidiMessage& msg);

	inline unsigned char clamp(unsigned char val, unsigned char min, unsigned char max);
	ofxMidiIn midiIn;
	ofxMidiOut midiOut;

};

#endif /* defined(__emptyExample__ofxMidiFighterTwister__) */
