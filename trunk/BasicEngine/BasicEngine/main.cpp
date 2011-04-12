/*
main.cpp
	Parte Principal de nuestro "Game". Aquí comienza todo con la funcion main()


*/

#include <stdio.h>


//La clase Windows.h necesaria para el timeGetTime()
#include <windows.h>
#include <stdlib.h>
#include "Game\Game.h"
#include "Utility\Debug.h"
#include "Lua\LuaManager.h"
#include "Character\CharacterManager.h"


int WINAPI WinMain (HINSTANCE hInstance,          // Instance
										HINSTANCE hprevInstance,      // Previous Instance
										LPSTR lpCmdLine,              // Command line parameters 
										int nCmdShow                  // Windows Show State
										) 
{
	// Inicializa la clase cDebug (si se compila en modo Debug)
	DEBUG_INIT();
	DEBUG_MSG("Inicializando cGame");
	
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

	DEBUG_MSG("Deinicializando la clase cGame");
	cGame::Get().Deinit();

	DEBUG_DEINIT();

	return 0;
}

