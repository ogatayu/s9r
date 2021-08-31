#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	// load settings
	config_ = ofLoadJson("config.json");

	// Setup screen
	ofSetVerticalSync(true);
	ofBackground(255, 255, 255);

#ifdef _DEBUG
	ofSetLogLevel(OF_LOG_VERBOSE);
#endif

	// Sound stream
	ofSoundStreamSettings settings;

	auto devices = soundStream.getDeviceList(ofSoundDevice::Api::MS_DS);
	int out_dev_id = getConfig(config_["audio.outputDeviceId"], 0);
	settings.setOutDevice(devices[out_dev_id]);

	settings.numOutputChannels = OUTPUT_CHANNELS;
	settings.sampleRate = getConfig(config_["audio.sampleRate"], 44100);
	settings.bufferSize = getConfig(config_["audio.bufferSize"], 512);
	settings.numBuffers = 0;
	settings.setOutListener(this);
	soundStream.setup(settings);

	// Midi
#ifdef _DEBUG
	midiIn.listInPorts();     // print input ports to console
	midiIn.setVerbose(true);
#endif

	midiIn.openPort(getConfig(config_["midi.inputDevice"], 0));
	//midiIn.openPort("iRig KEYS 25 17");
	midiIn.ignoreTypes(false, false, false);
	midiIn.addListener(this);
}

//--------------------------------------------------------------
void ofApp::update(){
	lastBufferMutex.lock();
	
	waveform_.clear();
	
	for (size_t i = 0; i < lastBuffer.getNumFrames(); i++) {
		float sample = lastBuffer.getSample(i, 0);
		float x = ofMap(i, 0, lastBuffer.getNumFrames(), 0, ofGetWidth());
		float y = ofMap(sample, -1, 1, 0, ofGetHeight());
		waveform_.addVertex(x, y);
	}
	
	rms = lastBuffer.getRMSAmplitude();

	lastBufferMutex.unlock();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::black);
	ofSetColor(ofColor::white);
	ofSetLineWidth(1 + (rms * 30.));
	waveform_.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& outBuffer) {
	synthMutex.lock();
	for (size_t i = 0; i < outBuffer.getNumFrames(); i++) {
		float val = synth.signalProcess(0);  // @@@ WIP
		for (size_t ch = 0; ch < OUTPUT_CHANNELS; ch++) {
			outBuffer.getSample(i, ch) = val;
		}
	}
	synthMutex.unlock();

	lastBufferMutex.lock();
	lastBuffer = outBuffer;
	lastBufferMutex.unlock();
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
	synthMutex.lock();
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
	synthMutex.unlock();
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