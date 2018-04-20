#pragma once
#include <random>
#include <ofColor.h>
#include<stdlib.h>

//need something to represent the platforms visually (just rectangles)
//need something to represent the location of the platform
//need at least a left most x coordinate and a right most x coordinate (maybe a range?)
//need a max y coordinate for the platform
//generating new platforms:
	//at the start of the game, generate platforms until there the last platform's rightmost x coordinate is more than the 
//moving the platforms:
	//when the user presses keys/uses voice to move their character, the character doesn't actually move in the x direction only the y direction
	//the platforms are the things that move in the x direction
	//movement represented by subtracting from all the x coordinates for the platforms and updating the screen
class Platform {
private:
	std::mt19937 rand_num_generator_;
	std::uniform_int_distribution<> rand_width_val_;
	std::uniform_int_distribution<> rand_height_val_;
	std::uniform_int_distribution<> rand_dist_between_platforms_;
	int distance_from_prev_platform_;
	int right_x_coordinate_;
	int left_x_coordinate_;
	int width_; //generate random x coordinate within this range: __ (depending on window size and location of this platform's left x coordinate)
	int height_; //generate random y coordinate within this range: __ (depending on window size)
	const ofColor platform_color_ = ofColor::black;

public:
	Platform();
	Platform& operator=(const Platform& other);
	~Platform();
	int getLeftXCoordinate();
	int getRightXCoordinate();
	int getDistanceFromPrevPlatform();
	int getWidth();
	int getHeight();
	ofColor getPlatformColor();
	void setLeftXCoordinate(int x_coordinate);
	bool canShiftLeft(int shift_amount); //returns true if this platform can be shifted and still remain visible in the window
	void shiftLeft(int shift_amount);
	void setWidth(int w);
};