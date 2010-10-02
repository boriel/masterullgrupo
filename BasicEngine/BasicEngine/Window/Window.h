/*
Class Window.h

	In this Window will run our game.

Notes:
	- Cuando se crea una aplicación en Windows, el sistema operativo crea un objeto que contiene la información asociada a la 
		ejecución de nuestra aplicación. Podemos acceder a esa información a través de un manejador o handle del tipo HINSTANCE.
	- Por otro lado, cuando se crea una ventana Windows, el sistema operativo almacena un objeto que representa a la ventana. 
		Podemos acceder a ese objeto a través de un handledel tipo HWND.
	- Por último, cuando tenemos la ventana y queremos “pintar” algo sobre ella, debemos acceder a su Contexto de Dispositivo 
		o HDC. A través de este contexto podremosrenderizar OpenGL más tarde.

*/


#ifndef Window_H
#define Window_H

#include <Windows.h>

#include "..\Utility\Singleton.h"
#include "ApplicationProperties.h"


class cWindow : public cSingleton<cWindow>
{
	//private variables
		HINSTANCE mInstance;  // Holds the instance of the application
		HWND mWnd;						// Holds our windows handle
		HDC mDC;							// Private GDI Device context

		cApplicationProperties mProperties;
		bool mbCloseApplication;

		friend class cSingleton<cWindow>;

	//public functions
	public:
		bool Init (cApplicationProperties &lProperties);
		void Update();
		bool Deinit();

		inline HWND GetHWND() { return mWnd; }
		inline bool GetCloseApplication () { return mbCloseApplication; }

		static LRESULT CALLBACK WndProc( HWND lWnd, UINT lMsg, WPARAM lWParam, LPARAM lLParam);

};



#endif