#include "Game.h"
#include <windows.h>


//Inicializa el juego
bool cGame::Init()
{
	mbFinished = false;

	return true;
}

//Destrucutor del juego
bool cGame::Deinit()
{
	return true;
}


//update del juego
void cGame::Update(float lfTimestep)
{

}


//render del juego
void cGame::Render() 
{
	
		//OutputDebugString ();
}



