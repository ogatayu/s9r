#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(255, 255, 255);

#ifdef _DEBUG
	ofSetLogLevel(OF_LOG_VERBOSE);
#endif

	// Variable
	wavePhase = 0;

	// Sound stream
	ofSoundStreamSettings settings;

	auto devices = soundStream.getDeviceList(ofSoundDevice::Api::MS_DS);
	settings.setOutDevice(devices[1]);

	settings.numOutputChannels = OUTPUT_CHANNELS;
	settings.sampleRate = 44100;
	settings.bufferSize = 512;
	settings.numBuffers = 4;
	settings.setOutListener(this);
	soundStream.setup(settings);

	// Midi
#ifdef _DEBUG
	midiIn.listInPorts();     // print input ports to console
	midiIn.setVerbose(true);
#endif

	midiIn.openPort(17);
	//midiIn.openPort("iRig KEYS 25 17");
	midiIn.ignoreTypes(false, false, false);
	midiIn.addListener(this);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::exit() {
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& outBuffer) {
	for (size_t i = 0; i < outBuffer.getNumFrames(); i++) {
		float val = synth.signalProcess(0);  // @@@ WIP
		for (size_t ch = 0; ch < OUTPUT_CHANNELS; ch++) {
			outBuffer.getSample(i, ch) = val;
		}
	}
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
	switch (msg.status)
	{
	case MIDI_NOTE_ON:
		synth.onNote(msg.pitch, msg.velocity);
		break;

	case MIDI_NOTE_OFF:
		synth.offNote(msg.pitch);
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}