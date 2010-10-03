/*
Class GraphicManager.h
*/

#ifndef GraphicManager_H
#define GraphicManager_H

#include "GLHeaders.h"
#include "..\Utility\Singleton.h";
#include "..\Window\Window.h"


//class cWindow;
class cGraphicManager : public cSingleton<cGraphicManager>
{
	
	public:
		bool Init( cWindow * lpWindow );
		bool Deinit();
		void SwapBuffer();

		//For Opengl 
		cWindow* mpWindow;		// Save the pointer to window that we show
		GLuint mPixelFormat;	// Save pixel format
		HGLRC mHRC;						// Handle del contexto de renderizado de OPENGL

	
		friend class cSingleton<cGraphicManager>;

	protected:
		cGraphicManager() { ; } // Protected constructor
	
	
	private:
		bool CreateContext (cWindow * lpWindow);
		void InitializeGLState();
		

};


#endif