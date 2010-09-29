/*
main.cpp
	Parte Principal de nuestro "Game". Aquí comienza todo con la funcion main()

*/

#include <stdio.h>


//La clase Windows.h necesaria para el timeGetTime()
#include <windows.h>
#include <stdlib.h>
#include "Game\Game.h"

//using namespace std;


int WINAPI WinMain (HINSTANCE hInstance,          // Instance
										HINSTANCE hprevInstance,      // Previous Instance
										LPSTR lpCmdLine,              // Command line parameters 
										int nCmdShow                  // Windows Show State
										) 
{

	cGame::Get().Init();  

	unsigned long luiLastTime = timeGetTime();
	while (!cGame::Get().HasFinished())
	{
		//Calculate the time in seconds
		unsigned long luiActualTime = timeGetTime();
		float lfTimestep = ((float)(luiActualTime - luiLastTime) / 1000.0f);
		luiLastTime = luiActualTime;

		//update
		cGame::Get().Update(lfTimestep);

		//Render
		cGame::Get().Render();
	}
	cGame::Get().Deinit();
	

	

	return 0;
}

