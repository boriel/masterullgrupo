/*
class KeyBoard.h: Los dispositivos en OIS funcionan en su mayor�a a trav�s de callbacks y el teclado no
									es una excepci�n. Por lo tanto, habr� un callback para cuando se pulsa una tecla y otro
									callback para cuando la tecla se suelta. Por lo tanto, lo que haremos ser� tener un array
									de 256 booleanos y cada vez que recibamos una llamada indicando que se ha pulsado
									una tecla, pondremos el booleano correspondiente a esa tecla a true. Cuando recibamos
									la llamada contraria (tecla soltada), pondremos el booleano correspondiente otra vez a
									false.
*/

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>

#include "GenericDevice.h"

#include "OISInputManager.h"
#include "OISException.h"
#include "OISKeyboard.h"
#include "OISEvents.h"

class cKeyboard : public cGenericDevice, public OIS::KeyListener
{
	public:
		cKeyboard() : mbIsValid(false) { ; }
		void Init();
		void Deinit(void);
		void Update(void);
		float Check(unsigned luiEntry);
		inline bool IsValid(void) { return mbIsValid; }

		// Listeners for the keyboard
		bool keyPressed( const OIS::KeyEvent &lArg );
		bool keyReleased( const OIS::KeyEvent &lArg );

private:
		OIS::Keyboard* mpOISKeyboard;

		static const unsigned kuiInputChanelSize = 256;
		bool mabInputBuffer[kuiInputChanelSize];
		bool mbIsValid;
};

#endif