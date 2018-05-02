# Development

**Problems:**
* :poop: Platform coordinates weren't updating permanently (in updatePlatforms() in ofApp.cpp file)
	* using a for-each loop (ie: `<for (Platform p : platforms_) {...}>`) creates a copy of each platform object and whatever is done in the loop only changes that copy, not any of the actual objects in platforms_ 
	* fixed by changing to a normal for-loop
* does me being dumb count as a problem?
* also my tendency to leave things til the last minute?
	* some people call it "procrastination" i prefer to call it "extreme time management"
	* diamonds are made under pressure
* installing essentia 
	* when installing dependencies, "sudo apt-get install build-essential libyaml-dev libfftw3-dev libavcodec-dev libavformat-dev libavutil-dev libavresample-dev python-dev libsamplerate0-dev libtag1-dev libchromaprint-dev python-six" didn't work
	* had to install libraries individually (libavcodec-dev, libavformat-dev, libavutil-dev, libavresample-dev, and libchromaprint-dev libraries wouldn't install but I don't think I'll need them because they're used mostly for loading/saving audio files and audio fingerprinting)
	* idk if I'll actually end up using this library? we shall see if I have time to get it working but it will mostly just be for extra stuff
* was having problems with the openFrameworks sound subsystem (using ofSoundStream to check for audio input from the mic)
	* apparently this is mostly only a problem on windows because small parts of the way ofSoundStream works are platform specific
	* in ofRtAudioSoundStream.cpp, line 106 - changed from:
  `<audio = shared_ptr<RtAudio>(new RtAudio());>` to `<audio = shared_ptr<RtAudio>(new RtAudio(RtAudio::Api::WINDOWS_DS));>`
* when I was trying to load and draw images the images would show up as a black rectangle unless I wrote `<ofSetColor(255);>` on the line before
* calling ofSetBackgroundColor once won't permanently change the background color
	* have to keep calling it in draw() I think because the background gets cleared automatically before the draw() command apparently
* I was trying to make it so that the title screen font resizes when the window resizes, but that means I have to reload the font with a different size, and when it did this a black rectangle would appear over the area where the font was supposed to appear
	* made a seperate font loading thread for loading the fonts
	* idk if this was super necessary though? or what kind of implications this might have on the running of the game? it shouldn't be too bad though because it's only for the title screen
* Getting the player to jump properly:
	* at first instead of jumping, the player would sink because I had the coordinate system backwards whoops
		* top left corner is (0,0)!!!
	* the platforms not moving during the player's jump
	* need a way to figure out whether the player made it onto a platform or fell between the platforms
	* probably going to use ofxBox2D to help with jumping motion
* compiling errors when trying to use ofxBox2D for the character's movements
	* need to use stable branch
	* error in the stable branch: in ofxBox2DPolygonUtils.h, line 115, change `<int mk[n];>` to `<int* mk = new int[n];>`
* using to help with the movements for the player
	* using an ofxBox2dRect to represent the player so (at least not that I know of) I can't directly use it with ofImage so the player will just be a box instead of the dog
	* when drawing the player, instead of drawing the actual ofxBox2dRect I can just draw the ofImage at the same coordinates as the ofxBox2dRect using getPosition()
	* had to refactor player class so that it extends ofxBox2dRect
	* had to do some physics magic to make sure when the player jumps it stays at the same x-position
	* nvm it wasn't that complicated actually
* removed `<ofSetFrameRate(12);>` from main.cpp because it was too slow
* ofRemove would remove platforms before they were completely out of the screen
	* had to override shouldRemoveOffScreen
* platforms would get knocked over instead of being fixed to the ground
	* when initializing the platforms with setPhysics, set density to 0 and/or set the type to static:
		* `<box_2d_platforms_.back().get()->body->SetType(b2_staticBody);>`
* playing around with different values for best result right now
* when adding score_ to the string that displays the final score at the end screen, have to do `<std::to_string(score_)>`
* scores not updating properly