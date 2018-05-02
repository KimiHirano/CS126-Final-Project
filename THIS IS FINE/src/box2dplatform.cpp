#include "box2dplatform.h"

const ofColor Box2DPlatform::platform_color_ = ofColor::black;


void Box2DPlatform::initialize(int window_width, int window_height)
{
	rand_num_generator_ = std::mt19937(rand());
	rand_dist_between_platforms_ = std::uniform_real_distribution<>(.05, .2);
	d_proportion_ = rand_dist_between_platforms_(rand_num_generator_);
	distance_to_next_platform_ = d_proportion_ * window_width;
	setRotationFriction(3000.0);

}

int Box2DPlatform::getDistanceToNextPlatform()
{
	return distance_to_next_platform_;
}

ofColor Box2DPlatform::getPlatformColor()
{
	return platform_color_;
}

bool Box2DPlatform::shouldRemoveOffScreen(shared_ptr<Box2DPlatform> shape)
{
	float x = shape.get()->getPosition().x;
	float width = shape.get()->getWidth();
	return ((x + width + 10) < 0);
}