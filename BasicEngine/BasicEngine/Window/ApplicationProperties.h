/*
Class ApplicationProperties.h

	Parameter list to initialize the window. 
	Se coge del fichero data\Config.xml
*/

#ifndef ApplicationProperties_H
#define ApplicationProperties_H


#include <string>

#include <tinystr.h>
#include <tinyxml.h>

#include <windows.h>

using namespace std;

class cApplicationProperties
{
	//General Application Parameters
	public:
		string macApplicationName;		// Application name and window
		unsigned muiWidth;								// Width of the window
		unsigned muiHeight;								// Height of the window
		unsigned muiBits;									// Bits that will have every pixel in the window. Usually 24 (RGB) or 32 (RGBA) bits per pixel.
		bool mbFullscreen;								// true = Game in FullScreen.
	
	private: 
		string msFilename;  // Resources or Properties file
		TiXmlDocument mDoc;
	

	public:
		bool Init(); 
		bool Deinit(); 

		void SetFilename (char* lsFilename);	
		bool LoadPropertiesXML(const char* lacLevelFile);
			

	private:
		bool LoadTagConfigXML();

	


};



#endif