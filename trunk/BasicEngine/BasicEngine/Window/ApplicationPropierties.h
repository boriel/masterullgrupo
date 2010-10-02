/*
Class ApplicationPropierties.h

	Parameter list to initialize the window
*/

#ifndef ApplicationPropierties_H
#define ApplicationPropierties_H

#include <stdio.h>

struct cApplicationPropierties
{
	//General Application Parameters
	std::string macApplicationName;		// Application name and window
	unsigned muiWidth;								// Width of the window
	unsigned muiHeight;								// Height of the window
	unsigned muiBits;									// Bits that will have every pixel in the window. Usually 24 (RGB) or 32 (RGBA) bits per pixel.
	bool mbFullScreen;								// true = Game in FullScreen.

};



#endif