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
	const int player_width_ = 40;
	const int player_height_ = 40;
	ofRectangle player_body_;
	ofColor color_ = ofColor::aquamarine;

public:
	Player();
	int getXCoordinate();
	int getYCoordinate();
	int getPlayerWidth();
	int getPlayerHeight();
	ofColor Player::getColor();
	ofRectangle Player::getBody();
	void setPlayerPosition(Platform current_platform);
};
