#include "player.h"

Player::Player()
{
	player_body_.setSize(40,40);	
	x_coordinate_ = 50;
}

int Player::getXCoordinate()
{
	return x_coordinate_;
}

int Player::getYCoordinate()
{
	return y_coordinate_;
}

int Player::getPlayerWidth()
{
	return player_width_;
}

int Player::getPlayerHeight()
{
	return player_height_;
}

ofColor Player::getColor()
{
	return color_;
}

ofRectangle Player::getBody()
{
	return player_body_;
}

void Player::setPlayerPosition(Platform current_platform)
{
	y_coordinate_ = 1024 - (current_platform.getHeight() + player_body_.getHeight());
}
