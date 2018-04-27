#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(255); //white i think
	srand(static_cast<unsigned>(time(0)));
	Platform first_platform;
	first_platform.setLeftXCoordinate(0);
	platforms_.push_back(first_platform);
	addPlatforms();
	player_.setPlayerPosition(first_platform);
	soundStream.printDeviceList();

	fire.load("fireboi1.jpg");
	dog.load("doggo.png");

	ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(54, 54, 54);

	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)

	//if you want to set a different device id 
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.

	int bufferSize = 256;


	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);

	bufferCounter = 0;
	drawCounter = 0;
	smoothedVol = 0.0;
	scaledVol = 0.0;

	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

}

//--------------------------------------------------------------
void ofApp::update(){
	if (amount_moved_ > 0) {
		updatePlatforms();
		draw();
		amount_moved_ = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(255); //white

	ofSetColor(255);
	fire.draw(0, 400, 1024, 400);
	
	ofSetColor(255);
	dog.draw(player_.getXCoordinate(), player_.getYCoordinate(), 75, 75);

	/*ofSetColor(player_.getColor());
	ofDrawRectangle(player_.getXCoordinate(), player_.getYCoordinate(), player_.getPlayerWidth(), player_.getPlayerHeight());
*/
	for (Platform p : platforms_) {
		ofSetColor(p.getPlatformColor());
		ofDrawRectangle(p.getLeftXCoordinate(), 1024 - p.getHeight(), p.getWidth(), p.getHeight());
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_RIGHT) {
		amount_moved_ += 100;
		update();
		amount_moved_ = 0;
	}
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

void ofApp::updatePlatforms()
{
	for (int i = 0; i < platforms_.size(); i++) {
		
		platforms_.at(i).shiftLeft(amount_moved_);
	}
	/*for (Platform p : platforms_) {
		std::cout << p.getLeftXCoordinate() << ",";
		p.shiftLeft(amount_moved_);
		std::cout << p.getLeftXCoordinate() << std::endl;

	}*/
	addPlatforms();
}

void ofApp::addPlatforms()
{
	int last_right_x_coordinate = platforms_.at(platforms_.size() - 1).getRightXCoordinate();
	while (last_right_x_coordinate < 1024) {
		std::cout << "p" << std::endl;

		Platform next_platform;
		next_platform.setLeftXCoordinate(last_right_x_coordinate + next_platform.getDistanceFromPrevPlatform());
		platforms_.push_back(next_platform);
		last_right_x_coordinate = next_platform.getRightXCoordinate();
	}
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels)
{
	float curVol = 0.0;

	// samples are "interleaved"
	int numCounted = 0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++) {
		left[i] = input[i * 2] * 0.5;
		right[i] = input[i * 2 + 1] * 0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted += 2;
	}

	if (curVol > 2.0) {
		amount_moved_ += 0.5;
		updatePlatforms();
	}
}


