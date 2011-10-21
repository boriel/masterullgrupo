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

		btRigidBody* mpbtCarChassis;

		//btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
		//btAlignedObjectArray<btCollisionShape*> mabtCollisionShapes;


		//No estoy del todo convencido de que etas clases y el vector de vertices haga algo
		class btBroadphaseInterface*	mpbtOverlappingPairCache;
		class btCollisionDispatcher*	mpbtDispatcher;
		class btConstraintSolver*	mpbtConstraintSolver;
		class btDefaultCollisionConfiguration* mpbtCollisionConfiguration;
		class btTriangleIndexVertexArray*	mpbtIndexVertexArrays;

		btVector3*	mpbtVertices;

	
		btRaycastVehicle::btVehicleTuning	mbtTuning;
		btVehicleRaycaster*	mpbtVehicleRayCaster;
		btRaycastVehicle*	mpbtVehicle;
		btCollisionShape*	mpbtWheelShape;
		int miForwardAxis;

		//No hace falta la camara
		//float	m_cameraHeight;
		//float	m_minCameraDistance;
		//float	m_maxCameraDistance;


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
		void Init(cVec3 lPosition, cQuaternion lRotationInicial);
		//void Update(void);
		void MostrarInfo ();

		cVec3 GetPosition ();
		void SetPosition (cVec3 lvPosition, cQuaternion lRotation);
		cQuaternion GetQuatRotation();
		//void RenderObjectVehicleDebug();

		void SpecialKeyboardRelease(const unsigned int luiKey);
		void SpecialKeyboard(const unsigned int luiKey);
		void ClientMoveAndDisplay();

#ifdef USE_BT_CLOCK
	btClock mbtClock;
#endif //USE_BT_CLOCK



	btScalar	GetDeltaTimeMicroseconds()
	{
#ifdef USE_BT_CLOCK
		btScalar lbtDeltaTime = (btScalar)mbtClock.getTimeMicroseconds();
		mbtClock.reset();
		return lbtDeltaTime;
#else
		return btScalar(16666.);
#endif
	}

	void CentrandoRuedas();
	void DesAcelerar();

	private:
		bool mbQuitarGiroRueda;  //para saber si el coche ha girado las ruedas
		bool mbAcelerando;


};




#endif