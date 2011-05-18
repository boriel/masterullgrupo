/*
class cPhysichsManager
haciendo pruebas con la física, para hacer un manager y usarlo. 
*/


#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "..\Utility\Singleton.h"
#include "btBulletDynamicsCommon.h"
#include <iostream> //TODO para quitar, sólo está para debug
#include "PhysicsCube.h"

class cPhysicsManager : public cSingleton<cPhysicsManager> {
	friend class cSingleton<cPhysicsManager>;

	public:
		bool Init();
		bool Deinit();
		void Update(float lfTimestep); // Function to update the world
		btDiscreteDynamicsWorld* GetDynamicsWorld(void) { return mpDynamicsWorld;}

	private:
		btDiscreteDynamicsWorld* mpDynamicsWorld;
		btBroadphaseInterface* mpBroadphase;
		btDefaultCollisionConfiguration* mpCollisionConfiguration;
		btCollisionDispatcher* mpDispatcher;
		btSequentialImpulseConstraintSolver* mpSolver;

		cPhysicsCube *lpTemp; //TODO para quitar
};

#endif
