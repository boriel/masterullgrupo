#ifndef PHYSICS_VEHICLE_H
#define PHYSICS_VEHICLE_H


//Imagino que serán clases neserarias para la configuración del vehicle Propias del Bullet
class btVehicleTuning;
struct btVehicleRaycaster;
class btCollisionShape;

#include "BulletDynamics/Vehicle/btRaycastVehicle.h"

#include "..\PhysicsObject.h"


#include "..\..\Game\InputConfiguration.h"




class cPhysicsVehicle : public cPhysicsObject 
{

	public:

		btRigidBody* m_carChassis;

		//btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
		btAlignedObjectArray<btCollisionShape*> mabtCollisionShapes;

		class btBroadphaseInterface*	m_overlappingPairCache;

		class btCollisionDispatcher*	m_dispatcher;

		class btConstraintSolver*	m_constraintSolver;

		class btDefaultCollisionConfiguration* m_collisionConfiguration;

		class btTriangleIndexVertexArray*	m_indexVertexArrays;

		btVector3*	m_vertices;

	
		btRaycastVehicle::btVehicleTuning	m_tuning;
		btVehicleRaycaster*	m_vehicleRayCaster;
		btRaycastVehicle*	m_vehicle;
		btCollisionShape*	m_wheelShape;
		int miForwardAxis;

		float	m_cameraHeight;

		float	m_minCameraDistance;
		float	m_maxCameraDistance;


		cPhysicsVehicle();

		virtual ~cPhysicsVehicle();

		//virtual void clientMoveAndDisplay();

		//virtual void	clientResetScene();

		//virtual void displayCallback();
	
		///a very basic camera following the vehicle
		//virtual void updateCamera();

		//virtual void specialKeyboard(int key, int x, int y);

		//virtual void specialKeyboardUp(int key, int x, int y);

		//void renderme();

		//void initPhysics();
		void Init();
		void Update(void);

		cVec3 GetPosition ();
		cQuaternion GetQuatRotation();
		//void RenderObjectVehicleDebug();

		void SpecialKeyboard(const unsigned int luiKey);

};




#endif