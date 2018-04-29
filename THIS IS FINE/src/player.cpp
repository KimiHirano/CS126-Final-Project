#include "player.h"

Player::Player()
{
	player_body_.setSize(75,75);	
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

void Player::setNextYCoordinate()
{
	y_coordinate_ = jump_coordinates_.at(0);
	jump_coordinates_.erase(jump_coordinates_.begin());
}

//vector<float> Player::jump(float initial_velocity)
//{
//	float x_velocity = 10;
//	vector<float> platform_displacements;
//	float y_pos = y_coordinate_;
//	float x_pos = 0;
//	while (y_pos > 0) {
//		y_pos = y_pos + (initial_velocity * time_) + (0.5 * gravity_mpss_ * time_ * time_);
//		x_pos += (time_ * x_velocity);
//		jump_coordinates_.push_back(y_pos);
//		platform_displacements.push_back(x_pos);
//	}
//	is_jumping_ = true;
//	finished_jump_ = false;
//	return platform_displacements;
//}

//vector<float> Player::bigJump()
//{
//	float initial_velocity = 70; //max height will be 250
//	return jump(initial_velocity);
//}
//
//vector<float> Player::medJump()
//{
//	float initial_velocity = 57; //max height will be 165
//	return jump(initial_velocity);
//}
//
//vector<float> Player::smallJump()
//{
//	float initial_velocity = 32; //max height will be 52
//	return jump(initial_velocity);
//}
//
//void Player::endJump()
//{
//	is_jumping_ = false;
//	finished_jump_ = true;
//}

void Player::jump(float height, int window_height)
{
	is_jumping_ = true;
	finished_jump_ = false;
	jump_height_ = y_coordinate_ - height;
	curr_direction_up_ = true;
	window_h_ = window_height;
}

void Player::update()
{
	if (is_jumping_) {
		if (curr_direction_up_) {
			if (y_coordinate_ > jump_height_) {
				cout << "goin up" << endl;
				y_coordinate_ -= jump_increment_;
			} else {
				cout << "hit max" << endl;

				curr_direction_up_ = false;
				y_coordinate_ += jump_increment_;
			}
		} else {
			cout << "goin down" << endl;

			//check if player has reached next platform
			float distance_to_platform = curr_platform_.getHeight() - (y_coordinate_ + player_height_);
			float jump_amount = min(distance_to_platform, jump_increment_);
			y_coordinate_ += jump_increment_;
			/*if (distance_to_platform > 0) {
				
				y_coordinate_ -= jump_amount;
			} else {

			}*/
			if (y_coordinate_ + player_height_ >= (window_h_ - curr_platform_.getHeight())) {
				y_coordinate_ = window_h_ - curr_platform_.getHeight() - player_height_;
				is_jumping_ = false;
				finished_jump_ = true;
			}

		}
	}
}



