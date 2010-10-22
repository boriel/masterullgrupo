/*
Clase InputManager. Esta clase se encarga de actualizar y leer los dispositivos, y con la información  
			que obtiene de ellos actualiza las acciones correspondientes
*/

#ifndef Input_Manager_H__
#define Input_Manager_H__

#include <vector>
#include "InputAction.h"
#include "InputEntry.h"
#include "KeyBoard.h"
//#include "GenericDevice.h"

#include "..\Utility\Singleton.h"



#define IsPressed (ACTION) cInputManager::Get().GetAction( ACTION ).GetIsPressed()

class OIS::InputManager;


//Identifica los dispositivos de entrada a traves de un enum
enum eDevices
{
	eKeyboard = 0
};


struct tActionMapping
{
	int miAction; //identificador de la accion
	int miDevice; //identificador del dispositivo al que se va a mapear la acción
	int miChannel; //es el canal dentro del dispositivo
};



class cInputManager : public cSingleton<cInputManager>
{
	friend class cSingleton<cInputManager>;

	private:
		std::vector <cInputAction> mActions; //se encarga de mantener el estado de cada una de las acciones. 
		std::vector <cGenericDevice *> mDevices;
		std::vector <std::vector <cInputEntry> > mMapped;

		// Specific OIS vars
		friend class cKeyboard;
		OIS::InputManager* mpOISInputManager;


	public:
		void Init(const tActionMapping laActionMapping[], unsigned luiActionCount);
		void Deinit();
		void Update(const float &lfTimestep);


		inline cInputAction &GetAction(const int &liActionId) { return mActions[liActionId]; }

	protected:
		cInputManager() { ; } // Protected constructor

	private:
		float Check(int liDevice, int liChannel);

};




#endif