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

//#include "GlutStuff.h"
#include "GL_ShapeDrawer.h"
#include "GLDebugDrawer.h"



class cPhysicsManager : public cResourceManager, public cSingleton<cPhysicsManager> 
{
	friend class cSingleton<cPhysicsManager>;

	public:
		bool Init();
		bool Deinit();
		void Update(float lfTimestep); // Function to update the world
		void Render(); //para renderizar los collision shape
		//void RenderObjectDebug(const btTransform& worldTransform, const btCollisionShape* shape, const btVector3& color);

		btDiscreteDynamicsWorld* GetDynamicsWorld(void) { return mpbtDynamicsWorld;}
		//btDynamicsWorld* GetDynamicsWorld(void) { return mpbtDynamicsWorld;}
		//void LoadObjectsXmlCollision();


		//inline void SetDebugMode (bool lbDebugMode) { mbDebugMode = lbDebugMode; }
		//inline bool GetDebugMode () { return mbDebugMode; }

		//void AddCollisionShape (btCollisionShape* lbtCollShape) { mabtCollisionShapes.push_back(lbtCollShape); }
		//void InitAllPhysics();
		//cPhysicsObject*	GetPhysicsObjectPtr (const string lsType, const string lsModelName);

		inline int GetDebugMode() { return miDebugMode; }
		inline void SetDebugMode (int liDebugMode) { miDebugMode = liDebugMode; }
		void CambiarDebugMode();

		//bool	GetIdle() const { return	mbIdle;	}
		//void	SetIdle(bool lbIdle) { mbIdle = lbIdle;	}


	private:
		btDiscreteDynamicsWorld* mpbtDynamicsWorld;
		//btDynamicsWorld* mpbtDynamicsWorld;
		btBroadphaseInterface* mpBroadphase;
		btDefaultCollisionConfiguration* mpCollisionConfiguration;
		btCollisionDispatcher* mpDispatcher;
		btSequentialImpulseConstraintSolver* mpSolver;

		int miDebugMode;
		//bool mbDebugMode;
		GL_ShapeDrawer* mpShapeDrawer;
		bool mEnableshadows;
		GLDebugDrawer* mpbtDebugDrawer;
		//bool mbIdle;

		//btAlignedObjectArray<btCollisionShape*> mabtCollisionShapes; 

		//typedef std::vector<cPhysicsObject *> cPhysicsObjectList;
		//cPhysicsObjectList mPhysicsObject;  //Objetos en general que no se donde clasificarlos por ahora ....
		//cPhysicsObjectList mPhysicsPlayer;
		//cPhysicsObjectList mPhysicsPista;
		//cPhysicsObjectList mPhysicsVehicle;  

		//std::string msFilename;  // Resources or Properties file

		void RenderWorldDebug();

		void MyInit();
		void RenderMe();
		void RenderScene(int liPass);



//Sería interesante poner una lista de fisica asi como tenemos estrucurada la lista de objectos??

};

#endif
