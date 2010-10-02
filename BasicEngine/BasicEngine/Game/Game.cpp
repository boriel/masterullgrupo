#include <windows.h>


#include "Game.h"
#include "..\Utility\Console.h"


//Inicializa el juego
bool cGame::Init()
{
	mbFinished = false;
	mbCloseApplication = false;

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
	//std::string lsTime = "aaa";

	//hacer el contador de 5 segundos

	//OutputDebugString (lsTime.c_str());
	
}


//render del juego
void cGame::Render() 
{
	
	//Mostrar el contador
	
}



