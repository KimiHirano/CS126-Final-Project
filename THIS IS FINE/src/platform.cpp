#include "platform.h"

const ofColor Platform::platform_color_ = ofColor::black;

void Platform::initialize(int window_width, int window_height, int x)
{
	rand_num_generator_ = std::mt19937(rand());
	rand_width_val_ = std::uniform_real_distribution<>(0.1, 0.4);
	rand_height_val_ = std::uniform_real_distribution<>(.2, .4);
	rand_dist_between_platforms_ = std::uniform_real_distribution<>(.05, .2);

	w_proportion_ = rand_width_val_(rand_num_generator_);
	h_proportion_ = rand_height_val_(rand_num_generator_);
	d_proportion_ = rand_dist_between_platforms_(rand_num_generator_);

	width_ = w_proportion_ * window_width;
	height_ = h_proportion_ * window_height;
	distance_to_next_platform_ = d_proportion_ * window_width;

	left_x_ = x;
	right_x_ = left_x_ + width_;
	y_ = window_height - height_;
}

int Platform::getLeftXCoordinate()
{
	return left_x_;
}

int Platform::getRightXCoordinate()
{
	return right_x_;
}

int Platform::getY()
{
	return y_;
}

int Platform::getDistanceToNextPlatform()
{
	return distance_to_next_platform_;
}

int Platform::getWidth()
{
	return width_;
}

int Platform::getHeight()
{
	return height_;
}

ofColor Platform::getPlatformColor()
{
	return platform_color_;
}

void Platform::setLeftXCoordinate(int x_coordinate)
{
	left_x_ = x_coordinate;
	right_x_ = left_x_ + width_;
}

bool Platform::canShiftLeft(int shift_amount)
{
	return (right_x_ - shift_amount) > 0;
}

void Platform::shiftLeft(int shift_amount)
{
	left_x_ -= shift_amount;
	right_x_ -= shift_amount;
}

void Platform::setWidthProportion(float wp, int window_width)
{
	w_proportion_ = wp;
	width_ = w_proportion_ * window_width;
	right_x_ = left_x_ + width_;
}

void Platform::resize(float window_w, float window_h, int prev_right_x, int prev_d)
{
	width_ = window_w * w_proportion_;
	height_ = window_h * h_proportion_;
	distance_to_next_platform_ = window_w * d_proportion_;

	y_ = window_h - height_;
	left_x_ = prev_right_x + prev_d;
	right_x_ = left_x_ + width_;
}
