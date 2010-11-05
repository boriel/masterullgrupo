#include <assert.h>
#include "Mouse.h"
#include "InputManager.h"
#include "..\Utility\Debug.h"

void cMouse::Init(void)
{
	// Clear the input buffer
	memset(mabInputBuffer, 0, kuiMouseButtons);
	memset(mafInput, 0, eMouse_Total * sizeof(mafInput[0]));

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
//	mpOISMouse->mState.w

	X += (float)lArg.state.X.rel;
	if (X < 0) X = 0;
	if (X > (float)lArg.state.width)
		X = (float)lArg.state.width;

	Y += (float)lArg.state.Y.rel;
	if (Y < 0) Y = 0;
	if (Y > (float)lArg.state.height)
		Y = (float)lArg.state.height;

	Z += (float)lArg.state.Z.rel;
	if (Z < 0) Z = 0;
	if (Z > (float)lArg.state.Z.abs)
		Z = (float)lArg.state.Z.abs;


	mafInput[eMouse_AxisX] = (float)(X / lArg.state.width);
	mafInput[eMouse_AxisY] = (float)(Y / lArg.state.height);
	mafInput[eMouse_AxisZ] = (float)(Z / lArg.state.Z.abs);

	DEBUG_MSG("X: %f, Y: %f, Z: %f", mafInput[eMouse_AxisX], mafInput[eMouse_AxisY], mafInput[eMouse_AxisZ]);
	return true;
}


bool cMouse::mousePressed(const OIS::MouseEvent &lArg, OIS::MouseButtonID liButton)
{
	if (liButton <= eMouse_ButtonLast) {
		mafInput[liButton] = 1.0f;
    }

	return true;
}


bool cMouse::mouseReleased(const OIS::MouseEvent &lArg, OIS::MouseButtonID liButton)
{
	if (liButton <= eMouse_ButtonLast) {
		mafInput[liButton] = 0.0f;
    }

	return true;
}

float cMouse::Check(unsigned luiEntry)
{
	if (luiEntry < eMouse_Total)
		return mafInput[luiEntry];

	return 0.0f;
}

void cMouse::Update(void)
{
	//This fires off buffered events for keyboards
	assert(mpOISMouse);
	mpOISMouse->capture();
}

