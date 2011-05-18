/*
Ejemplo de Hello world de la web de http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Hello_World

*/

#ifndef _HELLO_WORLD_DAVID
#define _HELLO_WORLD_DAVID

//#include "GlutStuff.h"
//#include "GLDebugDrawer.h"
#include "btBulletDynamicsCommon.h" //creo que para este ejemplo tampoco hace falta

class cPhysicsCube {
private:
	btDiscreteDynamicsWorld* mpDynamicsWorld; // The world.
	btRigidBody* mpFallRigidBody;
	btRigidBody* mpGroundRigidBody;
	btCollisionShape* mpFallShape;
	btCollisionShape* mpGroundShape;
	btSequentialImpulseConstraintSolver* mpSolver;
	btCollisionDispatcher* mpDispatcher;
	btDefaultCollisionConfiguration* mpCollisionConfiguration;
	btBroadphaseInterface* mpBroadphase;

public:
	void Init(btDiscreteDynamicsWorld* lpDynamicsWorld);
	void Update(float lfTimestep);
	void Deinit(void);
};

#endif