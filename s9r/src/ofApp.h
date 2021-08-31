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
		
		ofJson config_;
		template<typename T>
		T getConfig(ofJson node, const T& default_value) {
			if (node.is_null()) {
				return default_value;
			}
			return node;
		}

		std::string getConfig(ofJson node, const char* defaultValue) {
			return getConfig<std::string>(node, defaultValue);
		}

		static constexpr int OUTPUT_CHANNELS = 2;

		double wavePhase = 0.0;
		float  tuning_ = 440.0;

		Synth      synth;
		std::mutex synthMutex;

		ofSoundStream soundStream;
		void audioOut(ofSoundBuffer& outBuffer);

		ofxMidiIn midiIn;
		void newMidiMessage(ofxMidiMessage& eventArgs);

		std::mutex    lastBufferMutex;
		ofSoundBuffer lastBuffer;
		ofPolyline    waveform_;
		float         rms;
};
