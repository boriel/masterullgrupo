/*
class cControlRaceManager: Controla la carrera. Orden de los vehículos en la competición.
*/

#ifndef _CONTROL_RACE_MANAGER_H
#define _CONTROL_RACE_MANAGER_H

#include "..\..\Utility\Singleton.h"
#include <vector>

using namespace std;

struct tControlRace
{
	std::string msVehicleModelName; //Identificador del Vehículo
	unsigned int muiNumLaps; //Número de vueltas
	unsigned int muiNumLegs; //Número de estapas dentro d euna vuelta
	bool isOut; //True cuando el vehículo está fuera de carrera
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