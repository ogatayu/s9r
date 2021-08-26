#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

#include "Synth.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		static constexpr int OUTPUT_CHANNELS = 2;

		double wavePhase = 0.0;
		float  frequency = 440.0;

		Synth synth;

		std::mutex    audioMutex;
		ofSoundStream soundStream;
		ofSoundBuffer lastBuffer;
		void audioOut(ofSoundBuffer& outBuffer);

		ofxMidiIn                   midiIn;
		std::vector<ofxMidiMessage> midiMessages;
		std::size_t                 maxMessages = 10; //< max number of messages to keep track of
		void newMidiMessage(ofxMidiMessage& eventArgs);
};
