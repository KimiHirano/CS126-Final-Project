#pragma once

#include "ofMain.h"

#include "player.h"
#include "platform.h"
#include "box2dplayer.h"
#include "box2dplatform.h"
#include "fontloader.h"
#include "ofxBox2d.h"
#include <utility>

//need something for keeping score
//keep score by counting platforms
//TODO: add draw end screen and pause screen
//TODO: make check google style guide

class ofApp : public ofBaseApp{
	enum GameState {
		START_SCREEN, //need drawStartScreen() dog on fire meme, press s to start
		IN_PROGRESS, 
		PAUSED,		//idk if im gonna implement a paused state
					//NAH BITCH IMPLEMENT THAT SHIT
		FINISHED
	};

    private:
		GameState current_state_ = START_SCREEN;
		Player player_;
		bool should_move_platforms_ = true;
		float amount_moved_;

		const int player_x_coordinate_ = 100;

		const int title_font_modifier_ = 10; //what this for
		bool title_font_is_loading_ = false;
		bool title_font_loaded_ = false; //for checking to see if the initial font has been loaded or if it has been loaded after the window has been resized
		FontLoader title_font_loader_;
		ofTrueTypeFont title_font_;
		ofTrueTypeFont title2_font_;

		int score_ = 0;

	public:
		bool should_update_ = true;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void windowResized(int w, int h);

		void audioIn(float * input, int bufferSize, int nChannels);

		//void updatePlatforms();			//changes all the x-coordinates of the platforms
										//removes platforms whose x-cordinates have gone out of bounds
										//adds enough platforms to fill the window
										//updates current platform if necessary

		void addPlatforms();			//adds enough platforms to platforms_ to fill the window

		void drawStart();
		void drawEnd();
		void drawPaused();
		void drawPlatforms();
		void drawPlayer();

		void drawTitle(ofTrueTypeFont font, string words, 
			float line_height, float letter_spacing, int string_num);

		void drawFire();
		void drawDog(float y_surface); //y_surface is the y-coordinate of the surface on which the dog is supposed to be drawn


		//does it make sense for these to be public
		//also does it make sense for dog_ to be here intead of being in the player class
		ofImage fire_;
		ofImage dog_;
		ofSoundStream soundStream;

		//i dont think ill need these anymore
		//maybe just one vector<float> for the total volume
		vector<float> in;
		vector <float> left;
		vector <float> right;

		ofxBox2d box2d_;
		shared_ptr<ofxBox2dRect> box_2d_player_;
		bool player_moved_forward_ = false;
		float original_x_;
		bool player_is_jumping_ = false;
		bool player_finished_jump_ = false;
		vector < shared_ptr<Box2DPlatform>> platforms_;
		ofxBox2dEdge edge_line_;
		Box2DPlatform* current_platform_;
		void addPlatform(float x, float y, float w, float h);
		float standing_y_;

		// this is the function for contacts
		void contactStart(ofxBox2dContactArgs &e);
		void contactEnd(ofxBox2dContactArgs &e);
};
