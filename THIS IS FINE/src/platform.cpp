#include "platform.h"

Platform::Platform()
{
	rand_num_generator_ = std::mt19937(rand());
	rand_width_val_ = std::uniform_int_distribution<>(100,500);
	rand_height_val_ = std::uniform_int_distribution<>(200, 400);
	rand_dist_between_platforms_ = std::uniform_int_distribution<>(50,200);
	width_ = rand_width_val_(rand_num_generator_);
	height_ = rand_height_val_(rand_num_generator_);
	distance_from_prev_platform_ = rand_dist_between_platforms_(rand_num_generator_);

}

Platform & Platform::operator=(const Platform & other)
{
	// TODO: insert return statement here
	right_x_coordinate_ = other.right_x_coordinate_;
	left_x_coordinate_ = other.left_x_coordinate_;
	width_ = other.width_;
	height_ = other.height_;
	distance_from_prev_platform_ = distance_from_prev_platform_;
	return *this;
}

Platform::~Platform()
{
}

int Platform::getLeftXCoordinate()
{
	return left_x_coordinate_;
}

int Platform::getRightXCoordinate()
{
	return right_x_coordinate_;
}

int Platform::getDistanceFromPrevPlatform()
{
	return distance_from_prev_platform_;
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
	left_x_coordinate_ = x_coordinate;
	right_x_coordinate_ = left_x_coordinate_ + width_;
}

bool Platform::canShiftLeft(int shift_amount)
{
	return (right_x_coordinate_ - shift_amount) > 0;
}

void Platform::shiftLeft(int shift_amount)
{
	left_x_coordinate_ -= shift_amount;
	right_x_coordinate_ -= shift_amount;
}

void Platform::setWidth(int w)
{
	width_ = w;
}
