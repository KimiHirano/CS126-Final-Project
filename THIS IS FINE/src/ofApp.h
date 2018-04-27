#pragma once

#include "ofMain.h"

#include "player.h"
#include "platform.h"
#include <utility>

//need something for keeping score
//keep score by counting platforms

class ofApp : public ofBaseApp{
	enum GameState {
		START_SCREEN, //need drawStartScreen() dog on fire meme, press s to start
		IN_PROGRESS = 0, 
		PAUSED, //idk if im gonna implement a paused state
		FINISHED
	};

    private:
		GameState current_state_ = START_SCREEN;
		Player player_;
		std::vector<Platform> platforms_;
		bool should_move_platforms_ = true;
		float amount_moved_;

	public:
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

		void updatePlatforms();
		void addPlatforms();

		void drawStart();
		void drawEnd();
		void drawPaused();

		ofImage fire;
		ofImage dog;

		vector <float> left;
		vector <float> right;
		vector <float> volHistory;

		int bufferCounter;
		int drawCounter;

		float smoothedVol;
		float scaledVol;

		ofSoundStream soundStream;
		
};
