# Development

**Problems:**
* :poop: Platform coordinates weren't updating permanently (in updatePlatforms() in ofApp.cpp file)
  * using a for-each loop (ie: for (Platform p : platforms_) {...}) creates a copy of each platform object and whatever is done in the loop only changes that copy, not any of the actual objects in platforms_ 
  * fixed by changing to a normal for-loop
* does me being dumb count as a problem?
* also my tendency to leave things til the last minute?
  * some people call it "procrastination" i prefer to call it "extreme time management"
  * diamonds are made under pressure
* installing essentia 
  * when installing dependencies, "sudo apt-get install build-essential libyaml-dev libfftw3-dev libavcodec-dev libavformat-dev libavutil-dev libavresample-dev python-dev libsamplerate0-dev libtag1-dev libchromaprint-dev python-six" didn't work
  * had to install libraries individually (libavcodec-dev, libavformat-dev, libavutil-dev, libavresample-dev, and libchromaprint-dev libraries wouldn't install but I don't think I'll need them because they're used mostly for loading/saving audio files and audio fingerprinting)
