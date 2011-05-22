/*
File inputConfiguration.h: Contiene un enum con las posibles acciones que tiene
*/

#ifndef INPUT_CONFIGURATION_H
#define INPUT_CONFIGURATION_H

#include "..\Input\InputManager.h"

enum eInputActions {
	eIA_CloseApplication = 0,
	eIA_TurnLeft,
	eIA_TurnRight,
	eIA_Advance,
	eIA_Back,
	eIA_PlayJog,
	eIA_StopJog,
	eIA_PlayWave,
	eIA_StopWave,
	eIA_Count
};

////no va aquí, pero estaba haciendo pruebas por un error de linkado
//tActionMapping kaActionMapping[] = {
//	{ eIA_CloseApplication, eKeyboard, OIS::KC_ESCAPE },
//	{ -1, -1, -1 } // End of the table (Marca el final de la tabla)
//};


#endif