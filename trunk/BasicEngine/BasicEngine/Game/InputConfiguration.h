/*
File inputConfiguration.h: Contiene un enum con las posibles acciones que tiene
*/

#ifndef INPUT_CONFIGURATION_H
#define INPUT_CONFIGURATION_H

#include "..\Input\InputManager.h"

enum eInputActions {
	eIA_CloseApplication = 0,
	eIA_Up,
	eIA_Down,
	eIA_Left,
	eIA_Right,
	eIA_CameraForward,
	eIA_CameraBack,
	eIA_CameraLeft,
	eIA_CameraRight,
	eIA_CameraUp,
	eIA_CameraDown,
	eIA_ChangeMode,
	eIA_PlayJog,
	eIA_StopJog,
	eIA_PlayWave,
	eIA_StopWave,
	eIA_ChangeModeDebug,
	eIA_KeyI,
	eIA_KeyK,
	eIA_KeyJ,
	eIA_KeyL,
	eIA_PlayerForward,
	eIA_PlayerBack,
	eIA_PlayerLeft,
	eIA_PlayerRight,
	eIA_Accept,

	eIA_Count
};

#endif