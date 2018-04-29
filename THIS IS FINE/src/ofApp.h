#pragma once

#include "ofMain.h"

#include "player.h"
#include "platform.h"
#include "fontloader.h"
#include <utility>

//need something for keeping score
//keep score by counting platforms

class ofApp : public ofBaseApp{
	enum GameState {
		START_SCREEN, //need drawStartScreen() dog on fire meme, press s to start
		IN_PROGRESS, 
		PAUSED, //idk if im gonna implement a paused state
		FINISHED
	};

    private:
		GameState current_state_ = START_SCREEN;
		Player player_;
		std::vector<Platform> platforms_;
		bool should_move_platforms_ = true;
		float amount_moved_;

		vector<float> platform_x_displacements_;

		Platform current_platform_; //the current platform whose left most x-coordinate is at least the value position as the player's x-coordinate
									//updates every time the next platform reaches this value 

		const int player_x_coordinate_ = 50;
		float window_width_;
		float window_height_;

		const int title_font_modifier_ = 10;
		bool title_font_is_loading_ = false;
		bool title_font_loaded_ = false; //for checking to see if the initial font has been loaded or if it has been loaded after the window has been resized
		FontLoader title_font_loader_;
		ofTrueTypeFont title_font_;
		
		ofTrueTypeFont title2_font_;

	public:
		bool should_update_ = true;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void audioIn(float * input, int bufferSize, int nChannels);

		void updatePlayerPosition();

		void updatePlatforms();			//changes all the x-coordinates of the platforms
										//removes platforms whose x-cordinates have gone out of bounds
										//adds enough platforms to fill the window
										//updates current platform if necessary

		void addPlatforms();			//adds enough platforms to platforms_ to fill the window

		void drawStart();
		void drawEnd();
		void drawPaused();
		void drawPlatforms();
		void drawPlayer();

		ofImage fire_;
		ofImage dog_;

		vector <float> left;
		vector <float> right;
		vector <float> volHistory;

		int bufferCounter;
		int drawCounter;

		float smoothedVol;
		float scaledVol;

		ofSoundStream soundStream;
		
};
