#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	wavePhase = 0;

	// start the sound stream with a sample rate of 44100 Hz, and a buffer
	// size of 512 samples per audioOut() call
	ofSoundStreamSettings settings;

	auto devices = soundStream.getDeviceList(ofSoundDevice::Api::MS_DS);
	settings.setOutDevice(devices[1]);

	settings.numOutputChannels = 2;
	settings.sampleRate = 44100;
	settings.bufferSize = 512;
	settings.numBuffers = 4;
	settings.setOutListener(this);
	soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

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
