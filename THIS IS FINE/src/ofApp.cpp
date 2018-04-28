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

	fire_.load("fireboi1.jpg");
	dog_.load("doggo.png");

	ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(54, 54, 54);

	int bufferSize = 256;


	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);

	bufferCounter = 0;
	drawCounter = 0;
	smoothedVol = 0.0;
	scaledVol = 0.0;

	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

}

//--------------------------------------------------------------
void ofApp::update(){
	if (!title_font_is_loading_ && !title_font_loaded_) {
		int min_dimension = min(ofGetWindowHeight(), ofGetWindowWidth());
		int title_font_size = min_dimension / title_font_modifier_;
		title_font_loader_.setup("Gaegu-Bold.ttf", title_font_size); //font downloaded from https://fonts.google.com/specimen/Gaegu?selection.family=Gaegu

		title_font_is_loading_ = true;
		title_font_loader_.startThread();
	}
	else if(title_font_is_loading_ && !title_font_loader_.isThreadRunning()) { //check to see if the title font loading thread has finished loading
		title_font_ = title_font_loader_.font_;
		title_font_loaded_ = true;
		title_font_is_loading_ = false;
	}


	if (should_update_) {
		//check if the player is either jumping and above the height of the next/current rectangle
		//or is currently on the platform
		//or has landed from a jump - update score
		//or has died
		//current_state_ = FINISHED;
	}
	should_update_ = true;
	should_update_ = true;
	if (platform_x_displacements_.size() > 0) {
		updatePlatforms();
		updatePlayerPosition();
		draw();
	}
	else if(amount_moved_ > 0){
		updatePlatforms();
		draw();
		amount_moved_ = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (current_state_ == GameState::START_SCREEN) {
		drawStart();
	}
	else if (current_state_ == GameState::FINISHED) {
		//drawEnd();
	}
	else if (current_state_ == GameState::PAUSED) {

	}

	//drawPlayer();
	//drawPlatforms();
	ofSetBackgroundColor(255); //white

	//ofSetColor(255);
	//fire_.draw(0, 400, 1024, 400);
	//
	//ofSetColor(255);
	//dog_.draw(player_.getXCoordinate(), player_.getYCoordinate(), 75, 75);

	//for (Platform p : platforms_) {
	//	ofSetColor(p.getPlatformColor());
	//	ofDrawRectangle(p.getLeftXCoordinate(), 1024 - p.getHeight(), p.getWidth(), p.getHeight());
	//}

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
	title_font_loaded_ = false;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::updatePlatforms()
{
	if (platform_x_displacements_.size() > 0) {
		for (int i = 0; i < platforms_.size(); i++) {
			platforms_.at(i).shiftLeft(platform_x_displacements_.at(0));
		}
		addPlatforms();
		platform_x_displacements_.erase(platform_x_displacements_.begin());
	}
	else if (amount_moved_ > 0){
		for (int i = 0; i < platforms_.size(); i++) {
			platforms_.at(i).shiftLeft(amount_moved_);
		}
		addPlatforms();
	}
	
}

void ofApp::addPlatforms()
{
	int last_right_x_coordinate = platforms_.at(platforms_.size() - 1).getRightXCoordinate();
	while (last_right_x_coordinate < 1024) {

		Platform next_platform;
		next_platform.setLeftXCoordinate(last_right_x_coordinate + next_platform.getDistanceFromPrevPlatform());
		platforms_.push_back(next_platform);
		last_right_x_coordinate = next_platform.getRightXCoordinate();
	}
}

void ofApp::drawStart()
{
	ofSetColor(255);
	fire_.draw(0, ofGetWindowHeight() / 2, ofGetWindowWidth(), ofGetWindowHeight()/2);

	ofRectangle platform;
	float platform_height = ofGetWindowHeight() * 0.4;
	float platform_width = ofGetWindowWidth() * 0.3;
	float platform_x = (ofGetWindowWidth() / 2) - (platform_width / 2);
	float platform_y = ofGetWindowHeight() - platform_height;
	platform.setSize(platform_width, platform_height);
	platform.setPosition(platform_x, platform_y);
	ofSetColor(ofColor::black);
	ofDrawRectangle(platform);

	float dog_width = ofGetWindowWidth() * 0.15;
	float dog_height = dog_width;
	float dog_x = (ofGetWindowWidth() / 2) - (dog_width / 2);
	float dog_y = platform_y - dog_height;
	ofSetColor(255);
	dog_.draw(dog_x, dog_y, dog_width, dog_height);

	if (title_font_loaded_) {
		ofSetColor(ofColor::black);
		string title = "THIS IS FINE.";
		ofRectangle title_box = title_font_.getStringBoundingBox(title, 0, title_font_.getLineHeight());
		int xpos = (ofGetWindowWidth() / 2) - (title_box.getWidth() / 2);
		title_font_.drawStringAsShapes(title, xpos, title_font_.getLineHeight());

		string title2 = "a voice controlled game\n  (scream to start)";
		title2_font_ = title_font_;
		title2_font_.setLetterSpacing(0.7);
		title2_font_.setLineHeight(title_font_.getLineHeight() / 2);
		ofRectangle title2_box = title2_font_.getStringBoundingBox(title2, 0, title2_font_.getLineHeight());
		int xpos2 = (ofGetWindowWidth() / 2) - (title2_box.getWidth() / 2);
		int ypos2 = title_font_.getLineHeight() * 2;
		title2_font_.drawStringAsShapes(title2, xpos2, ypos2);

		
	}
	
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels)
{

	float small_jump_vol = 7;
	float med_jump_vol = 10;
	float big_jump_vol = 13;
	float curVol = 0.0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	//copied from the openFrameworks audioIn example
	for (int i = 0; i < bufferSize; i++) {
		left[i] = input[i * 2] * 0.5;
		right[i] = input[i * 2 + 1] * 0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
	}


	if (!player_.getIsJumping()) {
		if (curVol > 2.0) {
			amount_moved_ += 0.5;

			/*if (curVol > big_jump_vol) {
				platform_x_displacements_ = player_.bigJump();
			}
			else if (curVol > med_jump_vol) {
				platform_x_displacements_ = player_.medJump();
			}
			else if (curVol > small_jump_vol) {
				platform_x_displacements_ = player_.smallJump();
			}*/

		}
		updatePlatforms();

	}	
}

void ofApp::updatePlayerPosition()
{
	player_.setNextYCoordinate();
}


