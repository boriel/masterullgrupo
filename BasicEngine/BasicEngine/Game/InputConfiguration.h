/*
File inputConfiguration.h: Contiene un enum con las posibles acciones que tiene
*/

#ifndef INPUT_CONFIGURATION_H
#define INPUT_CONFIGURATION_H

#include "..\Input\InputManager.h"

enum eInputActions {
	eIA_CloseApplication = 0,
	eIA_Advance,
	eIA_Back,
	eIA_TurnLeft,
	eIA_TurnRight,
	eIA_ChangeMode,
	eIA_PlayJog,
	eIA_StopJog,
	eIA_PlayWave,
	eIA_StopWave,
	eIA_ChangeModeDebug,
	eIA_Count
};

#endif