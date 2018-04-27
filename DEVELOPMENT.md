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
