#include "box2dplayer.h"
//
//Box2DPlayer::Box2DPlayer()
//{
//}
//
//void Box2DPlayer::initialize(int window_width, int window_height, int y)
//{
//}

void Box2DPlayer::initialize(ofImage image)
{
	image_ = image;
}

void Box2DPlayer::draw()
{
	ofSetColor(255);
	ofVec2f pos = getPosition();
	float length = getWidth();
	image_.draw(pos.x - (length / 2), pos.y - (length / 2), length, length);
}
