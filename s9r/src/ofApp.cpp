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

	settings.numOutputChannels = 2;
	settings.sampleRate = 44100;
	settings.bufferSize = 512;
	settings.numBuffers = 4;
	settings.setOutListener(this);
	soundStream.setup(settings);

	// Midi

	// print input ports to console
#ifdef _DEBUG
	midiIn.listInPorts();
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
	float frequency = 440.0;
	float wavePhaseStep = (frequency / outBuffer.getSampleRate()) * TWO_PI;

	for (size_t i = 0; i < outBuffer.getNumFrames(); i++) {
		float sample = sin(wavePhase) * 0.3;

		outBuffer.getSample(i, 0) = sample;
		outBuffer.getSample(i, 1) = sample;

		wavePhase += wavePhaseStep;
	}

	unique_lock<mutex> lock(audioMutex);
	lastBuffer = outBuffer;
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


//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while (midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}