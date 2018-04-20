#pragma once

#include "ofMain.h"
#include "player.h"
#include "platform.h"
#include <utility>

class ofApp : public ofBaseApp{
	enum GameState {
		IN_PROGRESS = 0,
		PAUSED,
		FINISHED
	};

    private:
		GameState current_state_ = IN_PROGRESS;
		Player player_;
		std::vector<Platform> platforms_;
		bool should_move_platforms_ = true;
		int amount_moved_;

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

		void updatePlatforms();
		void addPlatforms();
		
};
