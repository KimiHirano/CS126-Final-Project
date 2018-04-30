#include "ofApp.h"

//TODO: need a way to pause the game right after switching between the start screen and the game screen
//so the player doesn't immediately start moving due to some remnants of the initial screaming lmao

//TODO: add function comments
//TODO: add way to check if player has landed on a platform or has landed in between platforms
//TODO: fix line spacing
//TODO: maybe clean up setup method a lil

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetBackgroundColor(255); //white i think
	
	srand(static_cast<unsigned>(time(0)));

	Platform first_platform;
	first_platform.initialize(ofGetWindowWidth(), ofGetWindowHeight(), 0);
	first_platform.setWidthProportion(0.6, ofGetWindowWidth());

	current_platform_ = first_platform;
	platforms_.push_back(first_platform);

	addPlatforms();

	player_.initialize(ofGetWindowWidth(), ofGetWindowHeight(), first_platform.getY());
	//soundStream.printDeviceList();

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
	//does it make more sense to put this in the window resized method?
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
		title_font_loader_.stopThread();
	}


	if (should_update_) {
		//check if the player is either jumping and above the height of the next/current rectangle
		//or is currently on the platform
		//or has landed from a jump - update score

		//or has died
		//current_state_ = FINISHED;
	}
	should_update_ = true;
	player_.updatePosition();
	/*if (platform_x_displacements_.size() > 0) {
		updatePlatforms();
		updatePlayerPosition();
		draw();
	}
	else*/ if(amount_moved_ > 0){
		updatePlatforms();
		draw();
		amount_moved_ = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(255); //white i think

	if (current_state_ == GameState::START_SCREEN) {
		drawStart();
	}
	else if (current_state_ == GameState::FINISHED) {
		//drawEnd();
	}
	else if (current_state_ == GameState::PAUSED) {
		//drawGamePaused
	}
	else {
		//drawPlatforms();

		//drawPlayer();

	ofSetColor(255);
	fire_.draw(0, ofGetWindowHeight() / 2, ofGetWindowWidth(), ofGetWindowHeight() / 2);
	
	ofSetColor(255);
	dog_.draw(player_.getXCoordinate(), player_.getYCoordinate(), player_.getPlayerWidth(), player_.getPlayerHeight());

	for (Platform p : platforms_) {
		ofSetColor(0);
		ofDrawRectangle(p.getLeftXCoordinate(), ofGetWindowHeight() - p.getHeight(), p.getWidth(), p.getHeight());
	}
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
	title_font_loaded_ = false;
	player_.resize(w, h);

	int prev_right_x;	//the right most coordinate of the previous platform
	int prev_d;		//the distance between the previous platform and the current platform
	for (int i = 0; i < platforms_.size(); i++) {

		//prev_right_x and prev_d are added to get the value of the current platform's left x-coordinate
		//so for the first platform, we can just keep it's left coordinate at its original position 
		if (i == 0) {
			prev_right_x = platforms_.at(i).getLeftXCoordinate();
			prev_d = 0;

		}
		platforms_.at(i).resize(w, h, prev_right_x, prev_d);
		prev_right_x = platforms_.at(i).getRightXCoordinate();
		prev_d = platforms_.at(i).getDistanceToNextPlatform();
	}
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::updatePlatforms()
{/*
	if (platform_x_displacements_.size() > 0) {
		for (int i = 0; i < platforms_.size(); i++) {
			platforms_.at(i).shiftLeft(platform_x_displacements_.at(0));
		}
		addPlatforms();
		platform_x_displacements_.erase(platform_x_displacements_.begin());
	}
	else*/ if (amount_moved_ > 0){
		for (int i = 0; i < platforms_.size(); i++) {
			platforms_.at(i).shiftLeft(amount_moved_);
			if (platforms_.at(i).getLeftXCoordinate() < player_x_coordinate_ &&
				platforms_.at(i).getLeftXCoordinate() + platforms_.at(i).getWidth() > player_x_coordinate_) {
				current_platform_ = platforms_.at(i);
			}
		}
		addPlatforms();
	}
}

void ofApp::addPlatforms()
{
	int last_right_x_coordinate = platforms_.at(platforms_.size() - 1).getRightXCoordinate();
	int dist_between_platforms = platforms_.at(platforms_.size() - 1).getDistanceToNextPlatform();
	while (last_right_x_coordinate < ofGetWindowWidth()) {

		Platform next_platform;
		int x = last_right_x_coordinate + dist_between_platforms;
		next_platform.initialize(ofGetWindowWidth(), ofGetWindowHeight(), x);
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

		string title2 = "a voice controlled game\n   (scream to start)";
		title2_font_ = title_font_;
		title2_font_.setLetterSpacing(0.7);
		title2_font_.setLineHeight(title_font_.getLineHeight() / 2);
		ofRectangle title2_box = title2_font_.getStringBoundingBox(title2, 0, title2_font_.getLineHeight());
		int xpos2 = (ofGetWindowWidth() / 2) - (title2_box.getWidth() / 2);
		int ypos2 = title_font_.getLineHeight() * 2;
		title2_font_.drawStringAsShapes(title2, xpos2, ypos2);		
	}
}

//TODO: should probably set a max for the height that a volume can produce
//TODO: clean up logic
//TODO: figure out how to make platforms move when player is jumping
void ofApp::audioIn(float * input, int bufferSize, int nChannels)
{
	float screaming = 20;
	float curVol = 0.0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	//copied from the openFrameworks audioIn example
	//TODO: don't think i need to do the splitting into left and right even though they did this in the example (try to see if it works the same if you get rid of it)
	for (int i = 0; i < bufferSize; i++) {
		left[i] = input[i * 2] * 0.5;
		right[i] = input[i * 2 + 1] * 0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
	}

	if (current_state_ == GameState::START_SCREEN) {
		if (curVol > screaming) {
			current_state_ = GameState::IN_PROGRESS;
		}
	}
	else if (current_state_ == GameState::IN_PROGRESS) {
		if (!player_.is_jumping_) {
			if (curVol > 10) {
				player_.jump((curVol * 10), ofGetWindowHeight());
				player_.curr_platform_ = current_platform_;
			}
		}

		if (curVol > 3.0) {
			amount_moved_ += 0.5;

		}
		updatePlatforms();

	}		
}

void ofApp::updatePlayerPosition()
{
	player_.setNextYCoordinate();
}


