/*
Class ApplicationProperties.h

	Parameter list to initialize the window
*/

#ifndef ApplicationProperties_H
#define ApplicationProperties_H

#include <stdio.h>
#include <string>

using namespace std;

struct cApplicationProperties
{
	//General Application Parameters
	string macApplicationName;		// Application name and window
	unsigned muiWidth;								// Width of the window
	unsigned muiHeight;								// Height of the window
	unsigned muiBits;									// Bits that will have every pixel in the window. Usually 24 (RGB) or 32 (RGBA) bits per pixel.
	bool mbFullscreen;								// true = Game in FullScreen.

};



#endif