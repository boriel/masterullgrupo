/*
class cControlRaceManager: Controla la carrera. Orden de los vehículos en la competición.
*/

#ifndef _CONTROL_RACE_MANAGER_H
#define _CONTROL_RACE_MANAGER_H

#include "..\..\Utility\Singleton.h"
#include "..\..\MathLib\Vec\Vec3.h"
#include <vector>
#include "..\..\..\bullet-2.78\src\BulletCollision\CollisionDispatch\btGhostObject.h"
#include "btBulletDynamicsCommon.h" 
#include "..\..\Sound\SoundManager.h"
#include "..\..\MathLib\MathLib.h"

using namespace std;

enum eTipoPartida{
	eContrarreloj,
	e2Jugadores,
	e4Jugadores,
	eCampana
};

struct tVehicleControl
{
	std::string msModelName; //Identificador del Vehículo
	unsigned int muiNumLaps; //Número de vueltas
	unsigned int muiNextLeg; //Número de estapas dentro de una vuelta
	bool isOut; //True cuando el vehículo está fuera de carrera
	unsigned int muiOrder;
	unsigned int muiKm;
	btRigidBody *mRigidbody;
	bool isPlayer; // True si es el coche que mueve el usuario
	bool AumentaVuelta; // Esto se usará para que solo se aumente una vuelta cuando atravesamos la meta.		
	unsigned int mTickUltimaVuelta; // Esto irá dentro de cada coche.
	unsigned int muiPuntoControlActual; // Con esto sabremos cuál fue el último punto de control por el que pasó
	cVec3 PosicionPtoControl; // Guardaremos la posición que tuvo el coche la ultima vez que paso por un punto de control
	cQuaternion RotacionPtoControl; // También guardaremos la dirección
};

struct tLegControl
{
	unsigned int muiID;
	cVec3 mvPoint1;
	cVec3 mvPoint2;
};

struct tPuntoControl{
	string Nombre;
	string Tipo;
	int PosX;
	int PosZ;
	btPairCachingGhostObject* Ghost;
};

class cRaceControlManager : public cSingleton<cRaceControlManager>
{
		typedef std::vector<tPuntoControl> cControles; 
		
	public:	
		bool Init(string lsFileName);
		void Deinit();
		void Render();
		void Update(float lfTimestep);
		void SonidosGolpes();
//		inline void AddControl(btRigidBody *lControl){mRaceControls.push_back(lControl);}
		void AddPuntoControl(string lNombre, string lTipo, int lPosX, int lPosZ, btPairCachingGhostObject* lGhost);
		void PasoMeta();
		int GetRaceActualLap();
		inline int GetRaceTotalLaps(){return muiMaxLaps;}
		inline int GetRaceTime(){return muiTemporizador;}
		inline void SetTipoPartida(eTipoPartida lTipoPartida){mTipoPartida=lTipoPartida;}
		inline int GetTipoPartida(){return mTipoPartida;}
		inline bool isRaceRunning(){return mRaceRunning;}
		inline int GetCuentaAtras(){return mCuentaAtras;}
		inline bool isFinalRace(){return mIsFinalRace;}
		int GetPuntoControlFromCar(string lNombreCoche);
		cVec3 GetPositionPuntoControl(int lPtoControl);
		inline cControles *GetPuntosControl(){return &mRaceControls;}
		void ComprobarColision(unsigned lCocheIndice);
		void VaciarObjetos();
		void EndRace(bool lVictoria);
		void StartRace(); // Coloca a los coches en sus posiciones y pone cuenta atrás.
		char *millisecondsToString(int time);
		cQuaternion GetPtoControlRotationFromCar(string lNombreCoche);
		cVec3 GetPtoControlPositionFromCar(string lNombreCoche);
		bool GetVictoria(){return mVictoria;}
	private:
		string msFileName;
		unsigned int muiMaxLaps;
		typedef std::vector<tVehicleControl *> cVehicleList;
		cVehicleList mVehicles;
		tVehicleControl *mPlayerVehicle; // Esto lo usaremos para tener un acceso directo al coche del jugador 
		typedef std::vector<tLegControl *> cLegList;
		cLegList mLegs;
		unsigned int muiTemporizador; // Con esto tendremos un contador de tiempo para los tiempos de las vueltas.
		bool mVictoria; // Con esto sabremos si se ha ganado o a perdido la partida.
		cControles mRaceControls;
		int mCuentaAtras;
		eTipoPartida mTipoPartida;
		bool mIsFinalRace;
		bool mRaceRunning;
		bool LoadXml(void);
		void Tokenize(const string& str, vector<string>& tokens,  const string& delimiters);

		Sound *mPasoMeta;
		Sound *mSoundVictoria;
		Sound *mSoundDerrota;
		mSoundBank mGolpes_SoundBank;
};

#endif