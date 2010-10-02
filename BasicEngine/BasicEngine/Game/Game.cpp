#include <windows.h>


#include "Game.h"
#include "..\Utility\Console.h"
#include "..\Window\Window.h"


//Inicializa el juego
bool cGame::Init()
{
	mbFinish = false;
	
	
	mProperties.macApplicationName = "Test 1";
	mProperties.mbFullscreen = false;
	mProperties.muiBits = 16;
	mProperties.muiWidth = 640;
	mProperties.muiHeight = 480;
	
	bool lbResult = cWindow::Get().Init( mProperties );

	return lbResult;
}

//Destrucutor del juego
bool cGame::Deinit()
{
	bool lbResult = cWindow::Get().Deinit();
	
	return lbResult;
}


//update del juego
void cGame::Update(float lfTimestep)
{
	//std::string lsTime = "aaa";

	//hacer el contador de 5 segundos

	//OutputDebugString (lsTime.c_str());
	
	cWindow::Get().Update();
	// Check if we need to close the application

	mbFinish = mbFinish || cWindow::Get().GetCloseApplication();
	if (mbFinish)
		return;
	


}


//render del juego
void cGame::Render() 
{
	
	//Mostrar el contador
	
}



