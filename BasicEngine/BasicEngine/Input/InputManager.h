/*
Clase InputManager. Esta clase se encarga de actualizar y leer los dispositivos, y con la informaci�n  
			que obtiene de ellos actualiza las acciones correspondientes
*/

#ifndef Input_Manager_H__
#define Input_Manager_H__

#include <vector>
#include "InputAction.h"
#include "InputEntry.h"
#include "KeyBoard.h"
#include "Pad.h"
#include "Mouse.h"
//#include "GenericDevice.h"

#include "..\Utility\Singleton.h"

#define IsPressed(ACTION) cInputManager::Get().GetAction( ACTION ).GetIsPressed()
#define BecomePressed(ACTION) cInputManager::Get().GetAction( ACTION ).GetBecomePressed()
#define BecomeReleased(ACTION) cInputManager::Get().GetAction( ACTION ).GetBecomeReleased()

class OIS::InputManager;


//Identifica los dispositivos de entrada a traves de un enum
enum eDevices
{
	eKeyboard = 0,
	eMouse = 1
};


struct tActionMapping
{
	int miAction; //identificador de la accion
	int miDevice; //identificador del dispositivo al que se va a mapear la acci�n
	int miChannel; //es el canal dentro del dispositivo
};



class cInputManager : public cSingleton<cInputManager>
{
	
	public:
		void Init(const tActionMapping laActionMapping[], unsigned luiActionCount);
		void Deinit();
		void Update(const float &lfTimestep);


		inline cInputAction &GetAction(const int &liActionId) { return mActions[liActionId]; };

		friend class cSingleton<cInputManager>;

	protected:
		cInputManager() { ; } // Protected constructor

	private:
		float Check(int liDevice, int liChannel);

		std::vector <cInputAction> mActions; //se encarga de mantener el estado de cada una de las acciones. 
		std::vector <cGenericDevice *> mDevices;
		std::vector <std::vector <cInputEntry> > mMapped;

		// Specific OIS vars
		friend class cKeyboard;
		friend class cPad;
		friend class cMouse;
		OIS::InputManager* mpOISInputManager;
};




#endif