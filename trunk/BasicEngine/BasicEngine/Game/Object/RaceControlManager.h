/*
class cControlRaceManager: Controla la carrera. Orden de los veh�culos en la competici�n.
*/

#ifndef _CONTROL_RACE_MANAGER_H
#define _CONTROL_RACE_MANAGER_H

#include "..\..\Utility\Singleton.h"
#include "..\..\MathLib\Vec\Vec3.h"
#include <vector>

using namespace std;

struct tVehicleControl
{
	std::string msModelName; //Identificador del Veh�culo
	unsigned int muiNumLaps; //N�mero de vueltas
	unsigned int muiNumLegs; //N�mero de estapas dentro d euna vuelta
	bool isOut; //True cuando el veh�culo est� fuera de carrera
	unsigned int muiOrder;
};

struct tLegControl
{
	unsigned int muiID;
	cVec3 mvPoint1;
	cVec3 mvPoint2;
};

class cRaceControlManager : public cSingleton<cRaceControlManager>
{
	public:	
		bool Init(string lsFileName);
		void Deinit();
		void Render();
		void Update(float lfTimestep);

	private:
		string msFileName;
		unsigned int muiMaxLaps;
		typedef std::vector<tVehicleControl *> cVehicleList;
		cVehicleList mVehicles;
		typedef std::vector<tLegControl *> cLegList;
		cLegList mLegs;

		bool LoadXml(void);
		void Tokenize(const string& str, vector<string>& tokens,  const string& delimiters);
};

#endif