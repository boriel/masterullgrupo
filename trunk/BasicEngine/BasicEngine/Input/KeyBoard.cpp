#include <assert.h>

#include "KeyBoard.h"
#include "InputManager.h"



//Inicialicaci�n
//Lo primero que se hace es inicializar el array de booleanos a false. Despu�s se crea el objeto teclado y por �ltimo se registran los callbacks
void cKeyboard::Init()
{
	

	// Clear the input buffer
	memset(mabInputBuffer, 0, kuiInputChanelSize);

	assert(cInputManager::Get().mpOISInputManager);
	OIS::InputManager* lpOISInputManager = cInputManager::Get().mpOISInputManager;
	mpOISKeyboard = (OIS::Keyboard*)lpOISInputManager->createInputObject(OIS::OISKeyboard, true);
	
	mpOISKeyboard->setEventCallback( this );
	mbIsValid = true;
}


//Destrucci�n
//Simplemente se destruye el objeto y resetean los valores de las variables
void cKeyboard::Deinit(void)
{
	assert(cInputManager::Get().mpOISInputManager);
	cInputManager::Get().mpOISInputManager->destroyInputObject(mpOISKeyboard);
	mpOISKeyboard = 0;
	mbIsValid = false;
}


//Funciones de callbak
bool cKeyboard::keyPressed( const OIS::KeyEvent &lArg )
{
	mabInputBuffer[lArg.key] = true;
	return true;
}

//Funciones de callbak
bool cKeyboard::keyReleased( const OIS::KeyEvent &lArg )
{
	mabInputBuffer[lArg.key] = false;
	return true;
}


float cKeyboard::Check(unsigned luiEntry)
{
	if (mabInputBuffer[luiEntry])
		return 1.0f;
	return 0.0f;
}

void cKeyboard::Update(void)
{
	//This fires off buffered events for keyboards
	assert(mpOISKeyboard);
	mpOISKeyboard->capture();
}


