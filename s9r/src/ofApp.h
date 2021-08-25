#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void audioOut(ofSoundBuffer& outBuffer);

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

		double wavePhase;

		std::mutex audioMutex;
		ofSoundStream soundStream;
		ofSoundBuffer lastBuffer;


		ofxMidiIn midiIn;
		std::vector<ofxMidiMessage> midiMessages;
		std::size_t maxMessages = 10; //< max number of messages to keep track of
		void newMidiMessage(ofxMidiMessage& eventArgs);
};
