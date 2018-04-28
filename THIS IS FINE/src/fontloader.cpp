#include "fontloader.h"

void FontLoader::setup(string filename, int fontsize)
{
	font_filename_ = filename;
	fontsize_ = fontsize;
}

void FontLoader::threadedFunction()
{
	font_.load(font_filename_, fontsize_, true, true, true);
}
