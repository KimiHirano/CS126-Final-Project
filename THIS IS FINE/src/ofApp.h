#pragma once

#include "ofMain.h"

#include "box2dplatform.h"
#include "fontloader.h"
#include "ofxBox2d.h"
#include <utility>

class ofApp : public ofBaseApp{
	enum GameState {
		START_SCREEN, 
		IN_PROGRESS, 
		FINISHED
	};

    private:
		GameState current_state_ = START_SCREEN;
		ofxBox2d box2d_;
		shared_ptr<ofxBox2dRect> box_2d_player_;
		vector < shared_ptr<Box2DPlatform>> platforms_;
		Box2DPlatform* current_platform_;

		bool should_update_ = true;
		bool moved_forward_ = false;
		bool player_is_jumping_ = true;

		float original_x_;
		float standing_y_;
		int platform_shift_ = 0;
		int player_x_coordinate_;

		bool title_font_loading_ = false;
		bool title_font_loaded_ = false; 
		FontLoader title_font_loader_;
		ofTrueTypeFont title_font_;
		ofTrueTypeFont title2_font_;
		const float title_font_modifier_ = 10;

		const float player_d_ = 10.0;
		const float player_b_ = 0.0;
		const float player_f_ = 0.1;

		const float platform_d_ = 0.0;
		const float platform_b_ = 0.0;
		const float platform_f_ = 0.5;

		int score_ = 0;

	public:
		ofImage fire_;
		ofImage dog_;
		ofSoundStream soundStream;

		vector<float> in;
		vector <float> left;
		vector <float> right;

		void setup();
		void update();
		void draw();

		//drawing helper funtions
		void drawStart();
		void drawEnd();
		void drawFire();
		void drawDog(float y_surface);	//y_surface: y-coordinate of surface 
										//on which the dog is to be drawn

		void drawTitle(ofTrueTypeFont font, 
			string words,			//words: string of words to be displayed
			float line_height,		//line_height: proportion of original font's line height (0-1)
			float letter_spacing,	//letter_spacing: proportion of original font's letter spacing (0-1)
			int string_num);		//string_num: order number of the string to be displayed

		

		void audioIn(float * input, int bufferSize, int nChannels);

		void addPlatform(float x, float y, float w, float h);
		void addPlatform();	

		void keyPressed(int key);
		void windowResized(int w, int h);

		// this is the function for contacts
		void contactStart(ofxBox2dContactArgs &e);
		void contactEnd(ofxBox2dContactArgs &e);
};
