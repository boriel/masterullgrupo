#include <assert.h>
#include "Mouse.h"
#include "InputManager.h"


void cMouse::Init(void)
{
	// Clear the input buffer
	memset(mabInputBuffer, 0, kuiMouseButtons);

	assert(cInputManager::Get().mpOISInputManager);
	OIS::InputManager* lpOISInputManager = cInputManager::Get().mpOISInputManager;
	mpOISMouse = (OIS::Mouse*)lpOISInputManager->createInputObject(OIS::OISMouse, true);
	
	mpOISMouse->setEventCallback( this );
	mbIsValid = true;
}


void cMouse::Deinit(void)
{
	assert(cInputManager::Get().mpOISInputManager);
	cInputManager::Get().mpOISInputManager->destroyInputObject(mpOISMouse);
	mpOISMouse = 0;
	mbIsValid = false;
}


bool cMouse::mouseMoved(const OIS::MouseEvent &lArg)
{
	
	return true;
}


bool cMouse::mousePressed(const OIS::MouseEvent &lArg, OIS::MouseButtonID liButton)
{
	assert(liButton < kuiMouseButtons);
	mabInputBuffer[liButton] = true;

	return true;
}

bool cMouse::mouseReleased(const OIS::MouseEvent &lArg, OIS::MouseButtonID liButton)
{
	assert(liButton < kuiMouseButtons);
	mabInputBuffer[liButton] = false;

	return true;
}

float cMouse::Check(unsigned luiEntry)
{
	assert(luiEntry < kuiMouseButtons);
	if (mabInputBuffer[luiEntry])
		return 1.0f;

	return 0.0f;
}

void cMouse::Update(void)
{
	//This fires off buffered events for keyboards
	assert(mpOISMouse);
	mpOISMouse->capture();
}

