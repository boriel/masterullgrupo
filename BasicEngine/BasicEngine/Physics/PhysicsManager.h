/*
class cPhysichsManager

haciendo pruebas con la física, para hacer un manager y usarlo. 



*/


#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "..\Utility\Singleton.h"

#include "btBulletDynamicsCommon.h"

#include <iostream>


class cPhysicsManager : public cSingleton<cPhysicsManager> 
{
	friend class cSingleton<cPhysicsManager>;

	public:
		bool Init();
		bool Deinit();


	public:

		btDiscreteDynamicsWorld* mDynamicsWorld;

	private:
		btBroadphaseInterface* mBroadphase;
		btDefaultCollisionConfiguration* mCollisionConfiguration;
		btCollisionDispatcher* mDispatcher;
		btSequentialImpulseConstraintSolver* mSolver;


};

#endif
