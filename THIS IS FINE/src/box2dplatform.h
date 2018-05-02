#pragma once
#include "ofxBox2d.h"
#include <random>

class Box2DPlatform : public ofxBox2dRect {
private:
	std::mt19937 rand_num_generator_;
	std::uniform_real_distribution<> rand_dist_between_platforms_;
	float d_proportion_; // the proportion of the window width that the platform distance_from_prev_platform_ should be
	int distance_to_next_platform_;

	//don't think ill need these but we'll see
	std::uniform_real_distribution<> rand_width_val_;
	std::uniform_real_distribution<> rand_height_val_;
	float w_proportion_; //the proportion of the window width that the platform width should be
	float h_proportion_; //the proportion of the window height that the platform height should be
	int width_;
	int height_;

	int right_x_;
	int left_x_;
	int y_;

	static const ofColor platform_color_;
public:
	//most of the sizing can be done with setup in ofApp
	//need to do distance to next platform

	void initialize(int window_width, int window_height);

	//getters
	//int getLeftXCoordinate();
	//int getRightXCoordinate();
	//int getY();
	int getDistanceToNextPlatform();
	//int getWidth();
	//int getHeight();
	ofColor getPlatformColor();

	//setters
	//void setLeftXCoordinate(int x_coordinate); //not sure if needed
	//void setWidthProportion(float wp, int window_width); //only intended to be used for setting the first platform width

	//probs wont need this
	//bool canShiftLeft(int shift_amount); //returns true if this platform can be shifted and still remain visible in the window
	//void shiftLeft(int shift_amount);
	//void resize(float window_w, float window_h, int prev_right_x, int prev_d);

};
