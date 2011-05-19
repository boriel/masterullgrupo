/*
Ejemplo de Hello world de la web de http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Hello_World

*/

#ifndef PHYSICS_CUBE_H
#define PHYSICS_CUBE_H

#include "..\PhysicsObject.h"
#include "btBulletDynamicsCommon.h" //creo que para este ejemplo tampoco hace falta

class cPhysicsCube : public cPhysicsObject {
private:
	btRigidBody* mpFallRigidBody;
	btRigidBody* mpGroundRigidBody;
	btCollisionShape* mpFallShape;
	btCollisionShape* mpGroundShape;

public:
    void Init( const std::string &lacNameID);
	void Update(void);
	void Deinit(void);
};

#endif