#pragma once
#include "ofMain.h"
#include "platform.h"

//need something to represent the player  visually probably a circle
//need something to represent the player's position
//need something to represent action for player jump
//something for resizing and player dimensions
class Player {
private:
	int x_coordinate_; //x coordinate of the upper left hand corner
	int y_coordinate_; //y coordinate of the upper  left hand corner
	const int player_width_ = 75;
	const int player_height_ = 75;
	ofRectangle player_body_;
	ofColor color_ = ofColor::aquamarine;

	float jump_height_;
	float jump_increment_ = 10;

	vector<float> jump_coordinates_;
	float acceleration;
	
	const float time_ = 0.001;
	const float gravity_mpss_ = -9.8; //acceleration due to gravity is ~-9.8 m/s^2

public:
	Player();

	bool is_jumping_ = false;
	bool finished_jump_ = false;
	bool curr_direction_up_ = false;
	bool player_dead_ = false;
	
	int window_h_;

	Platform curr_platform_;

	int getXCoordinate();
	int getYCoordinate();
	int getPlayerWidth();
	int getPlayerHeight();
	
	ofColor Player::getColor();
	ofRectangle Player::getBody();
	void setPlayerPosition(Platform current_platform); //to set the player's initial position at the start of the game so that it starts at the right height

	void setNextYCoordinate(); //used for jumps; updates player y-coordinate using the vector up jump coordinates

	vector<float> bigJump();	//fills jump_coordinates with y coordinates for a big jump of max height 250; returns x-diplacements for the platforms
	vector<float> medJump();	//fills jump_coordinates with y-coordinates for a medium jump of max height 165
	vector<float> smallJump();	// fills jump_coordinates with y-coordinates for a small jump of max height 52

	void endJump();

	void jump(float height, int window_height);

	void update();

};
