#pragma once
#include <ofThread.h>
#include <ofTrueTypeFont.h>

class FontLoader : public ofThread {
public:
	void setup(string filename, int fontsize);
	void threadedFunction();

	int fontsize_;
	string font_filename_;
	ofTrueTypeFont font_;
};
