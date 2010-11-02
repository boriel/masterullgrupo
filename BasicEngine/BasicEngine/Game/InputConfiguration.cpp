#include "InputConfiguration.h"
#include "..\Input\InputManager.h"
#include "..\Input\Mouse.h"

tActionMapping kaActionMapping[] = {
	{ eIA_CloseApplication, eKeyboard, OIS::KC_ESCAPE },
	{ eIA_CloseApplication, eMouse, eMouse_Button0}, 
	{ -1, -1, -1 } // End of the table (Marca el final de la tabla)
	//{eIA_Up, eKeyboard, VK_UP },
	//{eIA_Down, eKeyboard, VK_DOWN },
	//{eIA_Left, eKeyboard, VK_LEFT },
	//{eIA_Right, eKeyboard, VK_RIGHT },
	//{eIA_Accept, eKeyboard, VK_RETURN}, 

};