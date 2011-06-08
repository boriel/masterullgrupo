#include "InputConfiguration.h"
#include "..\Input\InputManager.h"
#include "..\Input\Mouse.h"

tActionMapping kaActionMapping[] = {
	{ eIA_CloseApplication, eKeyboard, OIS::KC_ESCAPE },
	{ eIA_CloseApplication, eMouse, eMouse_Button1}, // Se sale con el bot�n izquierdo
	{ eIA_Advance, eKeyboard, OIS::KC_UP },
	{ eIA_Back, eKeyboard, OIS::KC_DOWN },
	{ eIA_TurnLeft, eKeyboard, OIS::KC_LEFT },
	{ eIA_TurnRight, eKeyboard, OIS::KC_RIGHT },
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