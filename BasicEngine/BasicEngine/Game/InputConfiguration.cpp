#include "InputConfiguration.h"
#include "..\Input\InputManager.h"
#include "..\Input\Mouse.h"

tActionMapping kaActionMapping[] = {
	{ eIA_CloseApplication, eKeyboard, OIS::KC_ESCAPE },
	{ eIA_CloseApplication, eMouse, eMouse_Button1}, // Se sale con el botón izquierdo
	{ eIA_Advance, eKeyboard, OIS::KC_UP },
	{ eIA_Back, eKeyboard, OIS::KC_DOWN },
	{ eIA_MoveLeft, eKeyboard, OIS::KC_LEFT },
	{ eIA_MoveRight, eKeyboard, OIS::KC_RIGHT },
	{ eIA_MoveUp, eKeyboard, OIS::KC_A },
	{ eIA_MoveDown, eKeyboard, OIS::KC_Z },
	{ eIA_TurnLeft, eKeyboard, OIS::KC_O },
	{ eIA_TurnRight, eKeyboard, OIS::KC_P },
	{ eIA_PlayJog, eKeyboard, OIS::KC_Q },
	{ eIA_StopJog, eKeyboard, OIS::KC_W },
	{ eIA_PlayWave, eKeyboard, OIS::KC_E },
	{ eIA_StopWave, eKeyboard, OIS::KC_R },
	{ -1, -1, -1 } // End of the table (Marca el final de la tabla)
};