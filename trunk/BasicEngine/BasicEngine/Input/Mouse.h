#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <Windows.h>
#include "GenericDevice.h"

#include "OISInputManager.h"
#include "OISException.h"
#include "OISMouse.h"
#include "OISEvents.h"

enum eMouse
{
   // Buttons
   eMouse_Button0 = 0,
   eMouse_Button1,
   eMouse_Button2,
   eMouse_Button3,
   eMouse_Button4,
   eMouse_Button5,
   eMouse_Button6,
   eMouse_Button7,

   eMouse_ButtonLeft = eMouse_Button0,
   eMouse_ButtonMiddle = eMouse_Button1,
   eMouse_ButtonRight = eMouse_Button2,

   eMouse_ButtonLast = eMouse_Button7, // Puede ser necesario ponero a ButtonRight

   eMouse_Total
};


class cMouse : public cGenericDevice, public OIS::MouseListener
{
public:
    cMouse() : mbIsValid(false) { ; }
    void Init(void);
    void Deinit(void);
    void Update(void);
    float Check(unsigned luiEntry);
    inline bool IsValid(void) { return mbIsValid; }

    // Listeners for the Mouse
    bool buttonPressed(const OIS::MouseEvent &lArg, OIS::MouseButtonID liButton);
    bool buttonReleased(const OIS::MouseEvent &lArg, OIS::MouseButtonID liButton);

private:
	static const unsigned kuiMouseButtons = 8;
	bool mabInputBuffer[kuiMouseButtons];
	bool mbIsValid;

    OIS::Mouse* mpOISMouse;
};


#endif