#pragma once
class Platform
{
	//collective of platforms?
	//some kind of platform vector to hold all the platforms that are visible on the screen
	//when the right most x coordinate of the platform goes out of bounds, get rid of the platform
	//generating new platforms:
		//random y coordinate between ()
		//random x coordinate within () from the right most x coordinate of its preceding platform
		//need to check the right most x coordinate of the last platform in the vector
		//if the x coordinate is less than the total window length, then generate a new platform
	//moving the platforms:
		//moves when the player moves (player's x coordinate doesnt actually change, just the y coordinate
		//the platforms are the things that move in the x direction
		//key presses:
			//duration of the key press relative to amount x direction moved for the platforms
			//use up arrow for jumping?
			//one right key press means move () spaces - 
				//update all the platforms in the vector (all the x coordinates) by () spaces to the left
			//holding the key down for at least () seconds will make the player jump (longer key press means longer jump
		//when i incorporate the sound:
			//sounds within () volume will correspond to the single key press
			//need to define different volume levels for the different jumping heights
			//any sound will move the platforms by a fixed relative amount based on the duration of the sound
			//loudness of the sound defines how high the player jumps
	//
public:
	int left_x_coordinate;
	int right_x_coordinate;
	Platform();
	~Platform();
};

