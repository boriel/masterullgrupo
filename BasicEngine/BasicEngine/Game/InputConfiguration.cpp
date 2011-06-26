#include "InputConfiguration.h"
#include "..\Input\InputManager.h"
#include "..\Input\Mouse.h"

tActionMapping kaActionMapping[] = {
	{ eIA_CloseApplication, eKeyboard, OIS::KC_ESCAPE },
	{ eIA_CloseApplication, eMouse, eMouse_Button1}, // Se sale con el botón izquierdo
	{ eIA_Up, eKeyboard, OIS::KC_UP },
	{ eIA_Down, eKeyboard, OIS::KC_DOWN },
	{ eIA_Left, eKeyboard, OIS::KC_LEFT },
	{ eIA_Right, eKeyboard, OIS::KC_RIGHT },
	{ eIA_PlayerForward, eKeyboard, OIS::KC_UP },
	{ eIA_PlayerBack, eKeyboard, OIS::KC_DOWN },
	{ eIA_PlayerLeft, eKeyboard, OIS::KC_LEFT },
	{ eIA_PlayerRight, eKeyboard, OIS::KC_RIGHT },
	{ eIA_CameraForward, eKeyboard, OIS::KC_W },
	{ eIA_CameraBack, eKeyboard, OIS::KC_S },
	{ eIA_CameraLeft, eKeyboard, OIS::KC_A },
	{ eIA_CameraRight, eKeyboard, OIS::KC_D },
	{ eIA_CameraUp, eKeyboard, OIS::KC_R },
	{ eIA_CameraDown, eKeyboard, OIS::KC_F },
	{ eIA_ChangeMode, eKeyboard, OIS::KC_F1 },
	{ eIA_PlayJog, eKeyboard, OIS::KC_Q },
	{ eIA_StopJog, eKeyboard, OIS::KC_W },
	{ eIA_PlayWave, eKeyboard, OIS::KC_E },
	{ eIA_StopWave, eKeyboard, OIS::KC_R },
	{ eIA_ChangeModeDebug, eKeyboard, OIS::KC_F9 },
	{ eIA_KeyI, eKeyboard, OIS::KC_I },
	{ eIA_KeyK, eKeyboard, OIS::KC_K },
	{ eIA_KeyJ, eKeyboard, OIS::KC_J },
	{ eIA_KeyL, eKeyboard, OIS::KC_L },


	{ -1, -1, -1 } // End of the table (Marca el final de la tabla)
};