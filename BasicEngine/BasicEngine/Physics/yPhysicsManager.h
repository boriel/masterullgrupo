/*
class yPhysichsManager

haciendo pruebas con la física, para hacer un manager y usarlo. Por ahora le pongo la "y" porque haremos varios experimentos y depsués la unificaremos.



*/


#ifndef Y_PHYSICS_MANAGER_H
#define Y_PHYSICS_MANAGER_H

#include "..\Utility\Singleton.h"

#include "btBulletDynamicsCommon.h"

#include <iostream>


class ycPhysicsManager : public cSingleton<ycPhysicsManager> 
{
	friend class cSingleton<ycPhysicsManager>;

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
