#pragma once
#include "ofMain.h"
#include "platform.h"

//TODO: add necessary comments to some of the functions
//TODO: gotta start writing tests for these gurl
//TODO: remove debugging statements/unecessary commented out code
//TODO: clean up jump/update logic
//TODO: maybe move getters and setters to h file?
class Player {
private:
	static const float player_proportion_;	//the proportion of the window size the player will be
											//(multiply this number by the avg of the window height/width to get player width/height)
											//or maybe multiply by the min of  the window height/width??

	float player_w_; 
	float player_h_;
	int x_coord_ = 50; //x coordinate of the upper left hand corner
	int y_coord_; //y coordinate of the upper  left hand corner

	//ofRectangle player_body_;
	//ofColor color_ = ofColor::aquamarine;

	const float jump_height_proportion_ = 1;	//TODO: play with different numbers for this value
	const float jump_increment_proportion = 1;	//TODO: play with different numbers for this value
	float jump_height_;
	float jump_increment_;


public:
	void initialize(int window_width, int window_height, int y);

	//does it make sense for these variables to be public?
	bool is_jumping_ = false;
	bool finished_jump_ = false;
	bool curr_direction_up_ = false;
	bool player_dead_ = false;
	
	int window_h_; //TODO: get rid of this probably
	Platform curr_platform_; //TODO: get rid of this too i think? will probably do any platform/player comparisons in ofApp

	//getters
	int getXCoordinate();
	int getYCoordinate();
	int getPlayerWidth();
	int getPlayerHeight();
	//ofColor Player::getColor();
	//ofRectangle Player::getBody();

	//setters
	//void setPlayerPosition(Platform current_platform);	//to set the player's initial position at the start of the game so that it starts at the right height
														//can probably just do this in an initialization method tho later
	void setNextYCoordinate();	//used for jumps; updates player y-coordinate using the vector up jump coordinates
								//might get rid of this bc updatePosition and jump shoud take care of this

	void jump(float height, int window_height); //sets up initial conditions for a jump based on current window height and the volume of the user's yell
	void updatePosition(); //updates player's position if the player is currently jumping
	void resize(float window_height, float window_width); //resizes width/height/y-coordinate/(maybe x_coordinate but not as important) based on the new window dimensions

};

