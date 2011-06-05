/*
class cPhysichsManager
haciendo pruebas con la física, para hacer un manager y usarlo. 
*/

#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "..\Utility\ResourceManager.h"
#include "..\Utility\Singleton.h"
#include "btBulletDynamicsCommon.h"
#include "Objects\PhysicsCube.h"
#include "PhysicObjectType.h"
#include "..\MathLib\MathLib.h"


class cPhysicsManager : public cResourceManager, public cSingleton<cPhysicsManager> 
{
	friend class cSingleton<cPhysicsManager>;

	public:
		bool Init();
		bool Deinit();
		void Update(float lfTimestep); // Function to update the world

		btDiscreteDynamicsWorld* GetDynamicsWorld(void) { return mpDynamicsWorld;}
		void LoadObjectsXmlCollision();

		void AddCollisionShape (btCollisionShape* lbtCollShape) { mabtCollisionShapes.push_back(lbtCollShape); }
		void InitAllPhysics();
		cPhysicsObject*	GetPhysicsObjectPtr (const string lsType, const string lsModelName);

	private:
		btDiscreteDynamicsWorld* mpDynamicsWorld;
		btBroadphaseInterface* mpBroadphase;
		btDefaultCollisionConfiguration* mpCollisionConfiguration;
		btCollisionDispatcher* mpDispatcher;
		btSequentialImpulseConstraintSolver* mpSolver;

		btAlignedObjectArray<btCollisionShape*> mabtCollisionShapes; 

		typedef std::vector<cPhysicsObject *> cPhysicsObjectList;
		cPhysicsObjectList mPhysicsObject;  //Objetos en general que no se donde clasificarlos por ahora ....
		cPhysicsObjectList mPhysicsPlayer;
		cPhysicsObjectList mPhysicsPista;
		cPhysicsObjectList mPhysicsVehicle;  

		std::string msFilename;  // Resources or Properties file

//Sería interesante poner una lista de fisica asi como tenemos estrucurada la lista de objectos??

};

#endif
