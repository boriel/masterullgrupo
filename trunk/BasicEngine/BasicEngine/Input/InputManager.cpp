#include <windows.h>
#include <iostream>
#include <sstream>

#include "InputManager.h"
#include "../Window/Window.h"

//#include "Keyboard.h"


//Inicialización
void cInputManager::Init(const tActionMapping laActionMapping[], unsigned luiActionCount) 
{

	// Initializing the OIS library
	OIS::ParamList pl;

	std::ostringstream wnd;
	wnd << (size_t)cWindow::Get().GetHWND();
	
	pl.insert(std::make_pair( std::string("WINDOW"), wnd.str() ));

	//Default mode is foreground exclusive..but, we want to show mouse -	so nonexclusive
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	
	//This never returns null.. it will raise an exception on errors
	mpOISInputManager = OIS::InputManager::createInputSystem(pl);
	
	//Lets enable all addons that were compiled in:
	mpOISInputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);


	//inicializamos devices
	cGenericDevice *lpKeyboard = new cKeyboard;
	cGenericDevice *lpMouse = new cMouse;

	lpKeyboard->Init();
	lpMouse->Init();

	//this needs to match with the enum eDevices
	//eKeyboard = 0 -> keyboard in the index 0 of the vector
	mDevices.push_back(lpKeyboard);
	mDevices.push_back(lpMouse);

	//initializing the actions vector
	mActions.resize(luiActionCount);

	//initializing the mapping structure
	mMapped.resize(luiActionCount);
	int liIndex = 0;
	while (laActionMapping[liIndex].miAction >= 0)
	{
		cInputEntry lEntry;
		lEntry.muiDevice = laActionMapping[liIndex].miDevice;
		lEntry.muiChannel = laActionMapping[liIndex].miChannel;
		mMapped[laActionMapping[liIndex].miAction].push_back(lEntry);

		++liIndex;
	}
}

//destruir los inicializado por la clase
void cInputManager::Deinit()
{
	int liTamVector = mActions.size();
	for (int i = 0; i < liTamVector; i++)
		mActions[i].Deinit();
	mActions.resize(0);
	
	mMapped.resize(0);

	liTamVector = mDevices.size();
	for (int i = 0; i < liTamVector; i++) 
	{
		mDevices[i]->Deinit();
		delete(mDevices[i]);
	}
	mDevices.resize(0);

	if( mpOISInputManager )
	{
		OIS::InputManager::destroyInputSystem(mpOISInputManager);
		mpOISInputManager = NULL;
	}
	

}

//update
void cInputManager::Update(const float &lfTimestep)
{
	//actualizando los dispositivos
	int liSize = mDevices.size();
	for (int liDeviceId = 0; liDeviceId < liSize; liDeviceId++)
	{
		if (mDevices[liDeviceId] != NULL)
			mDevices[liDeviceId]->Update();
	}


	//para cada accion
	liSize = mMapped.size();
	for (int liActionId = 0; liActionId < liSize; liActionId++)
	{
		//para cada mapa
		int liMapSize = mMapped[liActionId].size();
		float lfValue = 0.0f;
		for (int liMapId = 0; liMapId < liMapSize; liMapId++)
		{
			//calcular el valor del input
			const cInputEntry& lEntry = mMapped[liActionId][liMapId];
			lfValue += Check(lEntry.muiDevice, lEntry.muiChannel);
		}

		//set the value in the action
		mActions[liActionId].Update(lfTimestep, lfValue);

	}
}


//Comprueba el estado del dispositivo
float cInputManager::Check(int liDevice, int liChannel) 
{
	if (mDevices[liDevice] != NULL && mDevices[liDevice]->IsValid())
		return (mDevices[liDevice]->Check(liChannel));
	return 0.0f;
}