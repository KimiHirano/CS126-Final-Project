#include "ofApp.h"

//TODO: need a way to pause the game right after switching between the start screen and the game screen
//so the player doesn't immediately start moving due to some remnants of the initial screaming lmao

//TODO: add function comments
//TODO: add way to check if player has landed on a platform or has landed in between platforms
//TODO: fix line spacing
//TODO: maybe clean up setup method a lil

//TODO: remove original player and platform stuff
//separate functions

//--------------------------------------------------------------
void ofApp::setup() {
	//ofSetBackgroundColor(255);
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_NOTICE);

	fire_.load("fireboi1.jpg");
	dog_.load("doggo.png");

	//initialize box2d world
	box2d_.init();
	box2d_.enableEvents();   // <-- turn on the event listener
	box2d_.setGravity(0, 10);
	box2d_.createGround();
	box2d_.setFPS(60.0);
	box2d_.registerGrabbing();

	// register the listener so that we get the events
	ofAddListener(box2d_.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(box2d_.contactEndEvents, this, &ofApp::contactEnd);

	//make starting platform
	float w = ofGetWindowWidth() * 0.6;
	float h = ofGetWindowHeight() * 0.5;
	float x = w / 2;
	float y = ofGetWindowHeight() - (0.5*h);
	addPlatform(x, y, w, h);

	//set first platform to current platform
	current_platform_ = platforms_.back().get();

	//add enough platforms to fill the window
	while (platforms_.back().get()->getPosition().x < ofGetWindowWidth()) {
		addPlatforms();
	}

	//addPlayer()?
	box_2d_player_ = std::make_shared<ofxBox2dRect>();
	box_2d_player_.get()->setPhysics(1.0, 0.0, 0.1);
	float player_length = ofGetWindowWidth() * 0.1;
	float player_y = platforms_[0].get()->getPosition().y - player_length;
	box_2d_player_.get()->setup(box2d_.getWorld(), player_x_coordinate_, 100, player_length, player_length);
	original_x_ = box_2d_player_.get()->getPosition().x;

	int bufferSize = 256;

	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);

	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
}



//--------------------------------------------------------------
void ofApp::update() {
	if (!title_font_is_loading_ && !title_font_loaded_) {
		int min_dimension = min(ofGetWindowHeight(), ofGetWindowWidth());
		int title_font_size = min_dimension / title_font_modifier_;

		//font downloaded from:
		//https://fonts.google.com/specimen/Gaegu?selection.family=Gaegu
		title_font_loader_.setup("Gaegu-Bold.ttf", title_font_size);

		title_font_is_loading_ = true;
		title_font_loader_.startThread();

		//check to see if the title font loading thread has finished loading
	} else if (title_font_is_loading_ && !title_font_loader_.isThreadRunning()) { 
		title_font_ = title_font_loader_.font_;
		title_font_loaded_ = true;
		title_font_is_loading_ = false;
		title_font_loader_.stopThread();
	}

	float difference = box_2d_player_.get()->getPosition().x - original_x_;
	if (player_finished_jump_ && difference != 0) {
		box_2d_player_.get()->setPosition(original_x_, box_2d_player_.get()->getPosition().y);

		for (int i = 0; i < platforms_.size(); i++) {
			ofVec2f pos = platforms_[i].get()->getPosition();
			platforms_[i].get()->setPosition(pos.x - difference, pos.y);
		}
		difference = 0;
		original_x_ = box_2d_player_.get()->getPosition().x;
	}

	
	box2d_.update();

	ofRemove(platforms_, Box2DPlatform::shouldRemoveOffScreen);
	while (platforms_.back().get()->getPosition().x < ofGetWindowWidth()) {
		addPlatforms();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetBackgroundColor(255); //white i think
	drawFire();
	if (current_state_ == GameState::START_SCREEN) {
		drawStart();
	}
	else if (current_state_ == GameState::FINISHED) {
		drawEnd();
	}
	else if (current_state_ == GameState::PAUSED) {
		//drawGamePaused
	}
	else {
		//draw platforms
		for (int i = 0; i < platforms_.size(); i++) {
			ofFill();
			ofSetColor(0);
			platforms_[i].get()->draw();
		}

		//draw player
		ofSetColor(255);
		ofVec2f pos = box_2d_player_.get()->getPosition();
		float length = box_2d_player_.get()->getWidth();
		dog_.draw(pos.x - (length / 2), pos.y - (length / 2), length, length);
	}
}

//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {
	if (current_state_ == GameState::IN_PROGRESS) {
		if (e.a != NULL && e.b != NULL) {

			//end game when player collides with the ground
			if ((e.a->GetType() != b2Shape::e_polygon ||
				e.b->GetType() != b2Shape::e_polygon)) {
				current_state_ = GameState::FINISHED;

			//updates current platform when player lands on new platform
			} else if (e.a->GetBody() == box_2d_player_.get()->body) {
				if (e.b->GetBody() != current_platform_->body) {
					current_platform_ = (Box2DPlatform*)e.b;
					score_++;
					cout << "score: " <<score_ << endl;

				}
			} else if (e.b->GetBody() == box_2d_player_.get()->body) {
				if (e.a->GetBody() != current_platform_->body) {
					current_platform_ = (Box2DPlatform*)e.a;
					score_++;
					cout << "score: " << score_ << endl;
				}
			}

			player_finished_jump_ = true;
		}
	}	
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
	//if (e.a != NULL && e.b != NULL) {}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	title_font_loaded_ = false;
	//player_.resize(w, h);

}

void ofApp::addPlatform(float x, float y, float w, float h)
{
	platforms_.push_back(shared_ptr<Box2DPlatform>(new Box2DPlatform));
	platforms_.back().get()->setPhysics(0, 0.5, 0.5);
	platforms_.back().get()->setup(box2d_.getWorld(), x, y, w, h);
	platforms_.back().get()->initialize(ofGetWindowWidth(), ofGetWindowHeight());
	platforms_.back().get()->body->SetType(b2_staticBody);
}

void ofApp::addPlatforms()
{
	float width_proportion = ofRandom(0.1, 0.4);
	float height_proportion = ofRandom(0.2, 0.4);

	float w = ofGetWindowWidth() * width_proportion;
	float h = ofGetWindowHeight() * height_proportion;
	float y = ofGetWindowHeight() - (0.5*h);
	float x = platforms_.back().get()->getPosition().x +
		platforms_.back().get()->getWidth() +
		platforms_.back().get()->getDistanceToNextPlatform() /*+ w / 2*/;
	addPlatform(x, y, w, h);
}

void ofApp::drawStart()
{
	drawFire();

	ofRectangle platform;
	float platform_height = ofGetWindowHeight() * 0.4;
	float platform_width = ofGetWindowWidth() * 0.3;
	float platform_x = (ofGetWindowWidth() / 2) - (platform_width / 2);
	float platform_y = ofGetWindowHeight() - platform_height;
	platform.setSize(platform_width, platform_height);
	platform.setPosition(platform_x, platform_y);
	ofSetColor(ofColor::black);
	ofDrawRectangle(platform);

	drawDog(platform_y);

	if (title_font_loaded_) {
		string title1 = "THIS IS FINE.";
		drawTitle(title_font_, title1, 1, 1, 1);

		string title2 = "a voice controlled game\n   (scream to start)";
		drawTitle(title_font_, title2, 0.5, 0.7, 2);
	}
}

void ofApp::drawEnd()
{
	drawFire();
	drawDog(ofGetWindowHeight());

	if (title_font_loaded_) {
		string title = "THIS IS FIN";
		drawTitle(title_font_, title, 1, 1, 1);

		string score_title = "final score: " + std::to_string(score_);
		drawTitle(title_font_, score_title, 0.5, 0.7, 2);
	}
}

void ofApp::drawTitle(ofTrueTypeFont font, string words, 
	float line_height, float letter_spacing, int string_num)
{
	font.setLineHeight(font.getLineHeight() * line_height);
	font.setLetterSpacing(font.getLetterSpacing() * letter_spacing);
	ofSetColor(ofColor::black);
	float y = font.getLineHeight();
	ofRectangle t_box = font.getStringBoundingBox(words, 0, y);
	int xpos = (ofGetWindowWidth() / 2) - (t_box.getWidth() / 2);
	int ypos = title_font_.getLineHeight() * string_num;
	font.drawStringAsShapes(words, xpos, ypos);
}

void ofApp::drawFire()
{
	ofSetColor(255);
	float fire_w = ofGetWindowWidth();
	float fire_h = ofGetWindowHeight() / 2;
	fire_.draw(0, fire_h, fire_w, fire_h);
}

void ofApp::drawDog(float y_surface)
{
	float dog_width = ofGetWindowWidth() * 0.15;
	float dog_height = dog_width;
	float dog_x = (ofGetWindowWidth() / 2) - (dog_width / 2);
	float dog_y = y_surface - dog_height;
	ofSetColor(255);
	dog_.draw(dog_x, dog_y, dog_width, dog_height);
}

//TODO: should probably set a max for the height that a volume can produce
//TODO: clean up logic
//TODO: figure out how to make platforms move when player is jumping
void ofApp::audioIn(float * input, int bufferSize, int nChannels)
{
	float screaming = 30;
	float curVol = 0.0;
	float max_vol = 30.0; //tested
	float non_jump = 13.0; //max volume for movement that isn't a full jump
	float min_vol = 3; //to account for ambient noise not created by the user

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	//from the openFrameworks audioIn example
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
		//if (!player_is_jumping_) {
		if (curVol < 20 && curVol > min_vol) {
			//cout << curVol << endl;

			ofVec2f pos(box_2d_player_.get()->getPosition());
			ofVec2f amt(0.0, min(curVol, max_vol));

			box_2d_player_.get()->addImpulseForce(pos, amt);
			player_finished_jump_ = false;
		}
		//}
	}
}