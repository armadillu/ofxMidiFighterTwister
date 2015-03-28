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

	void setup();

	void update();
	void draw();

	//light up the ring around the encoders
	void setEncoderRingValue(int encoder, float value); // value[0..1] - 127 values

	//Set the hue of the colored LED segment under each encoder
	//0 is blue, 0.25 is green, 0.5 is yellow, 0.75 is red, 1.0 is purplish
	void setEncoderColor(int encoder, float hue); // hue[0..1] 127 values

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

private:

	void newMidiMessage(ofxMidiMessage& msg);

	inline unsigned char clamp(unsigned char val, unsigned char min, unsigned char max);
	ofxMidiIn midiIn;
	ofxMidiOut midiOut;

};

#endif /* defined(__emptyExample__ofxMidiFighterTwister__) */
