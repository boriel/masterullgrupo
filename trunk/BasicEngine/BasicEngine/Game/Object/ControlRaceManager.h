/*
class cControlRaceManager: Controla la carrera. Orden de los veh�culos en la competici�n.
*/

#ifndef _CONTROL_RACE_MANAGER_H
#define _CONTROL_RACE_MANAGER_H

#include "..\..\Utility\Singleton.h"
#include <vector>

using namespace std;

struct tControlRace
{
	std::string msVehicleModelName; //Identificador del Veh�culo
	unsigned int muiNumLaps; //N�mero de vueltas
	unsigned int muiNumLegs; //N�mero de estapas dentro d euna vuelta
	bool isOut; //True cuando el veh�culo est� fuera de carrera
};

class cControlRaceManager : public cSingleton<cControlRaceManager>
{
	public:	
		bool Init(string lsFilename);
		void Deinit();
		void Render();
		void Update(float lfTimestep);

	private:
		string msFileName;
		tControlRace* mpControlRace;

		void LoadObjectsXml(std::string lsResource);
};

#endif