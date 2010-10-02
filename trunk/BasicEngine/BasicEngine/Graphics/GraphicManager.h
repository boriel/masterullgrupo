/*
Class GraphicManager.h
*/

#ifndef GraphicManager_H
#define GraphicManager_H

#include "..\Utility\Singleton.h";


//class cWindow;
class cGraphicManager : public cSingleton<cGraphicManager>
{
	
	public:
		bool Init( cWindow * lpWindow );
		bool Deinit();
		void SwapBuffer();
	
		friend class cSingleton<cGraphicManager>;

	protected:
		cGraphicManager() { ; } // Protected constructor
	
	private:

};


#endif