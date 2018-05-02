#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Box2DPlayer : public ofxBox2dRect {
private:
	ofImage image_;
//private:
//	static const float player_proportion_;
//
//	float player_w_;
//	float player_h_;
//	int x_coord_ = 50; //x coordinate of the upper left hand corner
//	int y_coord_; //y coordinate of the upper  left hand corner
//
//public:
//	Box2DPlayer();
//	void initialize(int window_width, int window_height, int y);
//	void draw();
//	void resize();
//
//	bool finished_jump_ = false;
//
//	int window_h_;
public:
	void initialize(ofImage image);
	void draw();
};