#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	srand(static_cast<unsigned>(time(0)));
	Platform first_platform;
	first_platform.setLeftXCoordinate(0);
	platforms_.push_back(first_platform);
	addPlatforms();
	player_.setPlayerPosition(first_platform);
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
	ofSetColor(player_.getColor());
	ofDrawRectangle(player_.getXCoordinate(), player_.getYCoordinate(), player_.getPlayerWidth(), player_.getPlayerHeight());

	for (Platform p : platforms_) {
		ofSetColor(p.getPlatformColor());
		ofDrawRectangle(p.getLeftXCoordinate(), 1024 - p.getHeight(), p.getWidth(), p.getHeight());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_RIGHT) {
		std::cout << "k" << std::endl;
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


