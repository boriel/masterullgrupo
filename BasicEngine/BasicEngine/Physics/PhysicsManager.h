/*
Clase con la que controlar el motor físico. 

Actualmente usamos Bullet Physics

Wiki: http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Documentation
Referencia: http://bulletphysics.com/Bullet/BulletFull/
Manual de usuario: http://bulletphysics.com/ftp/pub/test/physics/Bullet_User_Manual.pdf
*/

#pragma once

#include "..\..\Utility\Singleton.h"
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"

#include <stdlib.h>
#include <math.h>

#include "LinearMath/btVector3.h"
#include "LinearMath/btMatrix3x3.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btQuickprof.h"
#include "LinearMath/btAlignedObjectArray.h"

//Yorman begin
#define SCALING 1.
#define START_POS_X -3
#define START_POS_Y -1
#define START_POS_Z 5
//Yorman end

class cPhysicsManager : public cSingleton<cPhysicsManager> {
friend class cSingleton<cPhysicsManager>;
public:
	// Variables necesarias del motor
	btRigidBody* m_carChassis;
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
	class btBroadphaseInterface*	m_overlappingPairCache;
	class btCollisionDispatcher*	m_dispatcher;
	class btConstraintSolver*	m_constraintSolver;
	class btDefaultCollisionConfiguration* m_collisionConfiguration;
	class btTriangleIndexVertexArray*	m_indexVertexArrays;

	///this is the most important class
	btDynamicsWorld*		m_dynamicsWorld;

	btVector3*	m_vertices;
	
	btRaycastVehicle::btVehicleTuning	m_tuning;
	btVehicleRaycaster*	m_vehicleRayCaster;
	btRaycastVehicle*	m_vehicle;
	btCollisionShape*	m_wheelShape;

	//Otras variables
	bool	m_stepping;
	bool m_singleStep;
	bool m_idle;
	int m_lastKey;
	bool			m_enableshadows;
	btVector3		m_sundirection;
	btScalar		m_defaultContactProcessingThreshold;

	// Funciones 
	cPhysicsManager(void);
	~cPhysicsManager(void);
	void initPhysics();
	bool Deinit();
	void clientResetScene();
	void update(float lfTimestep);
	btDynamicsWorld* getDynamicsWorld()
	{
		return m_dynamicsWorld;
	}
	btRigidBody*	localCreateRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape);

private:
};