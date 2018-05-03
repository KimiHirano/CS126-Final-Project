#pragma once
#include "ofxBox2d.h"
#include <random>

class Box2DPlatform : public ofxBox2dRect {
private:
	std::mt19937 rand_num_generator_;
	std::uniform_real_distribution<> rand_dist_between_platforms_;

	//proportion of window width that distance_to_next_platform_ should be
	float d_proportion_; 
	int distance_to_next_platform_;

	static const ofColor platform_color_;
public:
	int window_w_;
	void initialize(int window_width, int window_height);
	int getDistanceToNextPlatform();
	ofColor getPlatformColor();
	static bool shouldRemoveOffScreen(shared_ptr<Box2DPlatform> shape);
};
