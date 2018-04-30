#include "player.h"

const float Player::player_proportion_ = 0.1;

void Player::initialize(int window_width, int window_height, int platform_y_coord)
{
	player_w_ = min(window_width, window_height) * player_proportion_;
	player_h_ = player_w_;
	player_body_.setSize(player_w_, player_h_);
	y_coord_ = platform_y_coord - player_h_;
}

int Player::getXCoordinate()
{
	return x_coord_;
}

int Player::getYCoordinate()
{
	return y_coord_;
}

int Player::getPlayerWidth()
{
	return player_w_;
}

int Player::getPlayerHeight()
{
	return player_h_;
}

ofColor Player::getColor()
{
	return color_;
}

ofRectangle Player::getBody()
{
	return player_body_;
}

//void Player::setPlayerPosition(Platform current_platform)
//{
//	y_coord_ = 1024 - (current_platform.getHeight() + player_body_.getHeight());
//}

void Player::setNextYCoordinate()
{
}

void Player::jump(float height, int window_height)
{
	is_jumping_ = true;
	finished_jump_ = false;
	jump_height_ = y_coord_ - height;
	curr_direction_up_ = true;
	window_h_ = window_height;
}

void Player::updatePosition()
{
	if (is_jumping_) {
		if (curr_direction_up_) {
			if (y_coord_ > jump_height_) {
				cout << "goin up" << endl;
				y_coord_ -= jump_increment_;
			} else {
				cout << "hit max" << endl;

				curr_direction_up_ = false;
				y_coord_ += jump_increment_;
			}
		} else {
			cout << "goin down" << endl;

			//check if player has reached next platform
			float distance_to_platform = curr_platform_.getHeight() - (y_coord_ + player_h_);
			float jump_amount = min(distance_to_platform, jump_increment_);
			y_coord_ += jump_increment_;
			
			if (y_coord_ + player_h_ >= (window_h_ - curr_platform_.getHeight())) {
				y_coord_ = window_h_ - curr_platform_.getHeight() - player_h_;
				is_jumping_ = false;
				finished_jump_ = true;
			}
		}
	}
}

void Player::resize(float window_width, float window_height)
{
	float original_height = player_h_;
	player_w_ = (window_height + window_width) / 2 * 0.1;
	player_h_ = player_w_;
	//new y coordinate should be so that the bottom y-cordinate is at the same location as it was before resize
	
	y_coord_ = y_coord_ + (original_height - player_h_);
}



