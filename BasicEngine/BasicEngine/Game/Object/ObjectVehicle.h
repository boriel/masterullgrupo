/*
Class ObjectVehicle:

*/


#ifndef OBJECT_VEHICLE_H
#define OBJECT_VEHICLE_H

#include <string>

#include "ObjectAgent.h"
#include "..\..\MathLib\MathLib.h"
#include "..\..\Physics\Objects\PhysicsVehicle.h"
#include "..\..\Sound\SoundManager.h"

class cObjectVehicle : public cObjectAgent
{

	public: 
		cObjectVehicle () {}
		cObjectVehicle (cObjectAgent lObject);

		virtual void Update (float lfTimestep);
		//virtual void Render (cMatrix &lWorld);
		virtual void Render ();

		//virtual void InitPhysics();

		void StopSounds();
		void Reload ();

        cPhysicsVehicle* mpPhysicsObject;
		inline void SetPtrPhysicsVehicle (cPhysicsVehicle* lPhysicsObject) { mpPhysicsObject = lPhysicsObject; }
		inline cPhysicsVehicle* GetPtrPhysicsVehicle () {return mpPhysicsObject; }
		void SetBehaviour();
        virtual void Init();

	//private:
		// Sonidos
	    Sound *mSoundAcelerar;
		Sound *mSoundFrenar;
		Sound *mSoundCorriendo;
		Sound *mSoundMarchaAtras;

		bool mbSuena; // Se usar� para que solo suene una vez la marcha artas      
};






#endif