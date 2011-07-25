#include "PhysicsVehicle.h"


#include "..\PhysicsManager.h"
#include "..\..\Graphics\GraphicManager.h"

#include "btBulletDynamicsCommon.h"

//CONSTANTES QUE HAY QUE PASAR A LA CLASE VEHICLE
//
// By default, Bullet Vehicle uses Y as up axis.
// You can override the up axis, for example Z-axis up. Enable this define to see how to:
//#define FORCE_ZAXIS_UP 1
//



#ifdef FORCE_ZAXIS_UP
		int rightIndex = 0; 
		int upIndex = 2; 
		int forwardIndex = 1;
		btVector3 wheelDirectionCS0(0,0,-1);
		btVector3 wheelAxleCS(1,0,0);
#else
		int giRightIndex = 0;
		int giUpIndex = 1;
		int giForwardIndex = 2;
		btVector3 gvbtWheelDirectionCS0(0, -1, 0);
		btVector3 gvbtWheelAxleCS(-1, 0, 0);
#endif



//const int gkiMaxProxies = 32766; //Al parecer no las uso
//const int gkiMaxOverlap = 65535; //Al parecer no las uso

///btRaycastVehicle is the interface for the constraint that implements the raycast vehicle
///notice that for higher-quality slow-moving vehicles, another approach might be better
///implementing explicit hinged-wheel constraints with cylinder collision, rather then raycasts
float	gfEngineForce = 0.f;
float	gfBreakingForce = 0.f;

float	gfMaxEngineForce = 2000.f; //this should be engine/velocity dependent
float	gfMaxBreakingForce = 100.f;

const float gkfAcelerar = 20.f;  //cuando acelera o lo deja presionado
const float gkfDesAcelerar = 5.f;  //cuando suelta el acelerador
const float gkfFrenar = 40.f;

float	gfVehicleSteering = 0.f;
float	gfSteeringIncrement = 0.04f;
float	gfSteeringClamp = 0.3f;
float	gfWheelRadius = 0.5f;
float	gfWheelWidth = 0.4f;
float	gfWheelFriction = 1000; //BT_LARGE_FLOAT;
float	gfSuspensionStiffness = 20.f;
float	gfSuspensionDamping = 2.3f;
float	gfSuspensionCompression = 4.4f;
float	gfRollInfluence = 0.1f;//1.0f;


btScalar gbtSuspensionRestLength(0.6f);

#define CUBE_HALF_EXTENTS 1




//Yorman begin  para borrar, esta puesto por el cubo de pruebas
//#define SCALING 1.
//#define START_POS_X -3
//#define START_POS_Y -1
//#define START_POS_Z 5
//Yorman end





cPhysicsVehicle::cPhysicsVehicle() 
	//: m_carChassis(0), m_cameraHeight(4.f), m_minCameraDistance(3.f), m_maxCameraDistance(10.f), m_indexVertexArrays(0), m_vertices(0)
{ //Constructor con parámetros por defecto
	mpbtVehicle = 0;
	mpbtWheelShape = 0;
	//m_cameraPosition = btVector3(30,30,30);
	mpbtCarChassis = 0;
	//m_cameraHeight = 4.f;
	//m_minCameraDistance(3.f) 
	//m_maxCameraDistance(10.f)
	//m_indexVertexArrays(0)
	//m_vertices(0)
}

cPhysicsVehicle::~cPhysicsVehicle() 
{
	//btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	btDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();

	//cleanup in the reverse order of creation/initialization

	//remove the rigidbodies from the dynamics world and delete them
	
	for (int luiIndex = lpDynamicsWorld->getNumCollisionObjects() - 1; luiIndex >= 0 ; luiIndex--) 
	{
		btCollisionObject* lbtObject = lpDynamicsWorld->getCollisionObjectArray()[luiIndex];
		btRigidBody* lbtRigidBody = btRigidBody::upcast(lbtObject);

		if (lbtRigidBody && lbtRigidBody->getMotionState()) 
			delete lbtRigidBody->getMotionState();
		
		lpDynamicsWorld->removeCollisionObject( lbtObject );
		delete lbtObject;
	}

	//delete collision shapes
	for (int luiIndex = 0; luiIndex < mabtCollisionShapes.size(); luiIndex++) 
	{
		btCollisionShape* lbtShape = mabtCollisionShapes[luiIndex];
		delete lbtShape;
	}

	delete mpbtIndexVertexArrays;
	delete mpbtVertices;

	//delete dynamics world
	delete lpDynamicsWorld;

	delete mpbtVehicleRayCaster;
	delete mpbtVehicle;
	delete mpbtWheelShape;

	//delete solver
	delete mpbtConstraintSolver;

	//delete broadphase
	delete mpbtOverlappingPairCache;

	//delete dispatcher
	delete mpbtDispatcher;

	delete mpbtCollisionConfiguration;
}

//Inicializamos la física del vehiculo
void cPhysicsVehicle::Init(cVec3 lPosition)
{

	
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	//btDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	//lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();


#ifdef FORCE_ZAXIS_UP
	//m_cameraUp = btVector3(0,0,1);
	//m_forwardAxis = 1;
	miForwardAxis = 1;
#endif

	btCollisionShape* groundShape = new btBoxShape(btVector3(50,3,50)); //Figura del suelo
	//m_collisionShapes.push_back(groundShape);
	//cPhysicsManager::mabtCollisionShapes.push_back(groundShape);
	//cPhysicsManager::Get().AddCollisionShape(groundShape);
	mabtCollisionShapes.push_back(groundShape);

	/*
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
	m_overlappingPairCache = new btAxisSweep3(worldMin,worldMax);
	m_constraintSolver = new btSequentialImpulseConstraintSolver();
	lpDynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_overlappingPairCache,m_constraintSolver,m_collisionConfiguration);
  */	
#ifdef FORCE_ZAXIS_UP
	//m_dynamicsWorld->setGravity(btVector3(0,0,-10));
	lpDynamicsWorld->setGravity(btVector3(0, 0, -10));
#endif 


	//m_dynamicsWorld->setGravity(btVector3(0,0,0));
	btTransform lbtTransform;
	lbtTransform.setIdentity();

#ifdef FORCE_ZAXIS_UP
//   indexRightAxis = 0; 
//   indexUpAxis = 2; 
//   indexForwardAxis = 1; 
	btCollisionShape* chassisShape = new btBoxShape(btVector3(1.f,2.f, 0.5f));
	btCompoundShape* compound = new btCompoundShape();
	btTransform localTrans;
	localTrans.setIdentity();
	//localTrans effectively shifts the center of mass with respect to the chassis
	localTrans.setOrigin(btVector3(0,0,1));
#else
	btCollisionShape* lbtChassisShape = new btBoxShape( btVector3 (1.f, 0.5f, 2.f) );
	//cPhysicsManager::Get().AddCollisionShape(chassisShape);
	mabtCollisionShapes.push_back( lbtChassisShape );

	btCompoundShape* lbtCompoundShape = new btCompoundShape();
	//cPhysicsManager::Get().AddCollisionShape(compound);
	mabtCollisionShapes.push_back( lbtCompoundShape );
	btTransform lbtLocalTransform;
	lbtLocalTransform.setIdentity();
	//localTrans effectively shifts the center of mass with respect to the chassis
	lbtLocalTransform.setOrigin(btVector3(0,1,0));
#endif

	lbtCompoundShape->addChildShape(lbtLocalTransform, lbtChassisShape);

	lbtTransform.setOrigin(btVector3(lPosition.x, lPosition.y, lPosition.z));
	

	mpbtCarChassis = LocalCreateRigidBody(800, lbtTransform, lbtCompoundShape); //chassisShape);
	//m_carChassis->setDamping(0.2,0.2);
	
	mpbtWheelShape = new btCylinderShapeX(btVector3(gfWheelWidth, gfWheelRadius, gfWheelRadius));
	
	//clientResetScene();

	/// create vehicle
	{
		
		mpbtVehicleRayCaster = new btDefaultVehicleRaycaster(lpDynamicsWorld);
		
		mpbtVehicle = new btRaycastVehicle(mbtTuning, mpbtCarChassis, mpbtVehicleRayCaster);
		
		///never deactivate the vehicle
		mpbtCarChassis->setActivationState(DISABLE_DEACTIVATION);

		
		//btRigidBody* lbtrb =  m_vehicle->getRigidBody();


		lpDynamicsWorld->addVehicle(mpbtVehicle);

		float lfConnectionHeight = 1.2f;

	
		bool lbIsFrontWheel=true;

		//choose coordinate system
		mpbtVehicle->setCoordinateSystem(giRightIndex, giUpIndex, giForwardIndex);

#ifdef FORCE_ZAXIS_UP
		btVector3 connectionPointCS0(CUBE_HALF_EXTENTS-(0.3*wheelWidth),2*CUBE_HALF_EXTENTS-wheelRadius, connectionHeight);
#else
		btVector3 connectionPointCS0(CUBE_HALF_EXTENTS-(0.3f * gfWheelWidth), lfConnectionHeight, 2.0f * CUBE_HALF_EXTENTS - gfWheelRadius);
#endif

		mpbtVehicle->addWheel (connectionPointCS0, gvbtWheelDirectionCS0, gvbtWheelAxleCS, gbtSuspensionRestLength, gfWheelRadius, mbtTuning, lbIsFrontWheel);
#ifdef FORCE_ZAXIS_UP
		connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(0.3*wheelWidth),2*CUBE_HALF_EXTENTS-wheelRadius, connectionHeight);
#else
		connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(0.3f * gfWheelWidth), lfConnectionHeight, 2 * CUBE_HALF_EXTENTS - gfWheelRadius);
#endif

		mpbtVehicle->addWheel (connectionPointCS0, gvbtWheelDirectionCS0, gvbtWheelAxleCS, gbtSuspensionRestLength, gfWheelRadius, mbtTuning, lbIsFrontWheel);
#ifdef FORCE_ZAXIS_UP
		connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(0.3*wheelWidth),-2*CUBE_HALF_EXTENTS+wheelRadius, connectionHeight);
#else
		connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(0.3f * gfWheelWidth), lfConnectionHeight, -2 * CUBE_HALF_EXTENTS + gfWheelRadius);
#endif //FORCE_ZAXIS_UP
		lbIsFrontWheel = false;
		mpbtVehicle->addWheel (connectionPointCS0, gvbtWheelDirectionCS0, gvbtWheelAxleCS, gbtSuspensionRestLength, gfWheelRadius, mbtTuning, lbIsFrontWheel);
#ifdef FORCE_ZAXIS_UP
		connectionPointCS0 = btVector3(CUBE_HALF_EXTENTS-(0.3*wheelWidth),-2*CUBE_HALF_EXTENTS+wheelRadius, connectionHeight);
#else
		connectionPointCS0 = btVector3(CUBE_HALF_EXTENTS-(0.3f * gfWheelWidth), lfConnectionHeight, -2 * CUBE_HALF_EXTENTS + gfWheelRadius);
#endif
		mpbtVehicle->addWheel (connectionPointCS0, gvbtWheelDirectionCS0, gvbtWheelAxleCS, gbtSuspensionRestLength, gfWheelRadius, mbtTuning, lbIsFrontWheel);
		
		for (int liIndex=0; liIndex < mpbtVehicle->getNumWheels(); liIndex++)
		{
			btWheelInfo& lbtWheelInfo = mpbtVehicle->getWheelInfo(liIndex);
			lbtWheelInfo.m_suspensionStiffness = gfSuspensionStiffness;
			lbtWheelInfo.m_wheelsDampingRelaxation = gfSuspensionDamping;
			lbtWheelInfo.m_wheelsDampingCompression = gfSuspensionCompression;
			lbtWheelInfo.m_frictionSlip = gfWheelFriction;
			lbtWheelInfo.m_rollInfluence = gfRollInfluence;
		}
	}

		
	//setCameraDistance(26.f);





	// --> Yorman comienzo pruebas
	/*
	btCollisionShape* colShape = new btBoxShape(btVector3(SCALING * 1, SCALING * 1, SCALING * 1));
	//btCollisionShape* colShape = new btSphereShape(btScalar(1.));
	//m_collisionShapes.push_back(colShape);
	//cPhysicsManager::Get().AddCollisionShape(colShape);
	mabtCollisionShapes.push_back(colShape);

	btScalar mass(1.f);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0,0,0);
	if (isDynamic)
		colShape->calculateLocalInertia(mass, localInertia);

	float start_x = START_POS_X;
	float start_y = START_POS_Y;
	float start_z = START_POS_Z;

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	startTransform.setOrigin(SCALING * btVector3(btScalar(2.0 + start_x), btScalar(20 + 2.0 + start_y), btScalar(2.0 + start_z)));
			
	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
	
	btRigidBody* body = new btRigidBody(rbInfo);
					
	//m_dynamicsWorld->addRigidBody(body);
	lpDynamicsWorld->addRigidBody(body);
	*/
	// --> Yorman fin pruebas






}

/*
void cPhysicsVehicle::Update(void) 
{ //Update

	btTransform lbtTransform;
	mpbtVehicle->getRigidBody()->getMotionState()->getWorldTransform(lbtTransform);
	
	//mpbtRigidBody->getMotionState()->getWorldTransform(trans);
 
	std::cout << "Vehicle: (" << lbtTransform.getOrigin().getX() << "," <<  lbtTransform.getOrigin().getY() << "," << lbtTransform.getOrigin().getZ() << ")" << std::endl;
}
*/




//Obtenemos la posicion central del objeto
cVec3 cPhysicsVehicle::GetPosition ()
{
	cVec3 lPosition;

	btTransform lbtTransform;
	//mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform);
	mpbtVehicle->getRigidBody()->getMotionState()->getWorldTransform(lbtTransform);


	lPosition.x = lbtTransform.getOrigin().getX();
	lPosition.y = lbtTransform.getOrigin().getY();
	lPosition.z = lbtTransform.getOrigin().getZ();

	return lPosition;
}



cQuaternion cPhysicsVehicle::GetQuatRotation()
{
	//cVec3 lVecRotation;
	cQuaternion lQuatRotation;

	btTransform lbtTransform;
	//mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform);
	mpbtVehicle->getRigidBody()->getMotionState()->getWorldTransform(lbtTransform);

	btQuaternion lbtQuaternion =  lbtTransform.getRotation();
	
	lQuatRotation.x = lbtQuaternion.getX();
	lQuatRotation.y = lbtQuaternion.getY();
	lQuatRotation.z = lbtQuaternion.getZ();
	lQuatRotation.w = lbtQuaternion.getW();


	return lQuatRotation;
}


/*
void cPhysicsVehicle::RenderObjectVehicleDebug()
{

	
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);


	btTransform lbtTransform; 
	//mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform); 
	m_vehicle->getRigidBody()->getMotionState()->getWorldTransform(lbtTransform);


	//Pintando los ejes de coordenadas
	RenderTransformDebug(lbtTransform, 1.0);




	
	////Detectando todos los Shapes
	//for (unsigned int luiIndex = 0; luiIndex < m_collisionShapes.size(); luiIndex++) 
	//{
	//	btCollisionShape* lbtCollisionShape = m_collisionShapes[luiIndex];
	//	const btBoxShape* lbtBoxShape = static_cast<const btBoxShape*>(lbtCollisionShape);
	//	btVector3 lbtHalfExtents = lbtBoxShape->getHalfExtentsWithMargin();
	//	btVector3 lbtColor(0.0f, 1.0f, 0.0f); //si se pasa por parametro a lo mejor podemos dibujar cosas de muchos colores
	//	RenderBoxDebug(- lbtHalfExtents, lbtHalfExtents, lbtTransform, lbtColor);
	//}

	//btCollisionShape* lbtShape = m_vehicle->getRigidBody()->getCollisionShape();
	

	

	
	

	////Dibujando un cubo, sacado de btCollisionWorld.cpp 1217 (despues de mucho buscar y seguir codigo ...)
	////btCollisionShape* lbtShape = mpbtRigidBody->getCollisionShape();
	//btCollisionShape* lbtShape = m_vehicle->getRigidBody()->getCollisionShape();
	//const btBoxShape* lbtBoxShape = static_cast<const btBoxShape*>(lbtShape);
	//btVector3 lbtHalfExtents = lbtBoxShape->getHalfExtentsWithMargin();
	//btVector3 lbtColor(1.0f, 0.0f, 0.0f); //si se pasa por parametro a lo mejor podemos dibujar cosas de muchos colores
	//RenderBoxDebug(- lbtHalfExtents, lbtHalfExtents, lbtTransform, lbtColor);

}
*/




//void VehicleDemo::specialKeyboard(int key, int x, int y)
void cPhysicsVehicle::SpecialKeyboard(const unsigned int luiKey)
{
	
	switch (luiKey)
	{
		case eIA_Up:  //arriba
			//gfEngineForce = gfMaxEngineForce;
			if (gfEngineForce < gfMaxEngineForce)
				gfEngineForce += gkfAcelerar;
			gfBreakingForce = 0.f;
			
			break;

		case eIA_Down: //abajo
			gfBreakingForce = gfMaxBreakingForce; 
			gfEngineForce = 0.f;
			//gfEngineForce -= gkfAcelerar;
			//gEngineForce = -maxEngineForce;
			//gBreakingForce = 0.f;
			
			break;

		case eIA_Left:  //izquierda
			gfVehicleSteering += gfSteeringIncrement;
			if (gfVehicleSteering > gfSteeringClamp)
				gfVehicleSteering = gfSteeringClamp;
			
			break;

		case eIA_Right: //derecha
			gfVehicleSteering -= gfSteeringIncrement;
			if (gfVehicleSteering < -gfSteeringClamp)
				gfVehicleSteering = -gfSteeringClamp;
			
			break;

	}

	ClientMoveAndDisplay();

	//printf ("Key = %i\n", luiKey);
//	printf("key = %i x=%i y=%i\n",key,x,y);

	

/*
    switch (key) 
    {
    case GLUT_KEY_LEFT : 
		{
			gVehicleSteering += steeringIncrement;
			if (	gVehicleSteering > steeringClamp)
					gVehicleSteering = steeringClamp;

		break;
		}
    case GLUT_KEY_RIGHT : 
		{
			gVehicleSteering -= steeringIncrement;
			if (	gVehicleSteering < -steeringClamp)
					gVehicleSteering = -steeringClamp;

		break;
		}
    case GLUT_KEY_UP :
		{
			gEngineForce = maxEngineForce;
			gBreakingForce = 0.f;
		break;
		}
	case GLUT_KEY_DOWN :
		{			
			gBreakingForce = maxBreakingForce; 
			gEngineForce = 0.f;
		break;
		}
	default:
		DemoApplication::specialKeyboard(key,x,y);
        break;
    }

//	glutPostRedisplay();hasta
*/

}


void cPhysicsVehicle::ClientMoveAndDisplay()
{

	//david quitar: glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	
	{			
		int liWheelIndex = 2;
		mpbtVehicle->applyEngineForce( gfEngineForce, liWheelIndex );
		mpbtVehicle->setBrake( gfBreakingForce, liWheelIndex );
		liWheelIndex = 3;
		mpbtVehicle->applyEngineForce( gfEngineForce, liWheelIndex );
		mpbtVehicle->setBrake( gfBreakingForce, liWheelIndex );


		liWheelIndex = 0;
		mpbtVehicle->setSteeringValue( gfVehicleSteering, liWheelIndex );
		liWheelIndex = 1;
		mpbtVehicle->setSteeringValue( gfVehicleSteering, liWheelIndex );

	}


	float lfDeltaTime = GetDeltaTimeMicroseconds() * 0.000001f;
	
	if (lpDynamicsWorld)
	{
		//during idle mode, just run 1 simulation step maximum
		//int maxSimSubSteps = m_idle ? 1 : 2;
		//if (m_idle)
		//	dt = 1.0/420.f;

		lfDeltaTime = 1.0f / 420.f;

		int maxSimSubSteps = 1; //temp a mano
		int numSimSteps = lpDynamicsWorld->stepSimulation(lfDeltaTime, maxSimSubSteps);
		

//#define VERBOSE_FEEDBACK
#ifdef VERBOSE_FEEDBACK
		if (!numSimSteps)
			printf("Interpolated transforms\n");
		else
		{
			if (numSimSteps > maxSimSubSteps)
			{
				//detect dropping frames
				printf("Dropped (%i) simulation steps out of %i\n",numSimSteps - maxSimSubSteps,numSimSteps);
			} else
			{
				printf("Simulated (%i) steps\n",numSimSteps);
			}
		}
#endif //VERBOSE_FEEDBACK

	}

	
	




#ifdef USE_QUICKPROF 
        btProfiler::beginBlock("render"); 
#endif //USE_QUICKPROF 


	//renderme(); 

	//optional but useful: debug drawing
	//if (lpDynamicsWorld)
	//	lpDynamicsWorld->debugDrawWorld();

#ifdef USE_QUICKPROF 
        btProfiler::endBlock("render"); 
#endif 
	

	glFlush();
	//glutSwapBuffers();

}

void cPhysicsVehicle::MostrarInfo ()
{

	btTransform lbtTransform;
	mpbtVehicle->getRigidBody()->getMotionState()->getWorldTransform(lbtTransform);
	//std::cout << "Vehicle: (" << lbtTransform.getOrigin().getX() << "," <<  lbtTransform.getOrigin().getY() << "," << lbtTransform.getOrigin().getZ() << ")" << std::endl;

	/*
	cout << "--------------------" << endl;
	cout << "giRightIndex : " << giRightIndex  << endl;
	cout << "giUpIndex : " << giUpIndex << endl;
	cout << "giForwardIndex : " << giForwardIndex  << endl;
	cout << "gvbtWheelDirectionCS0 : " << gvbtWheelDirectionCS0.getX() << "," << gvbtWheelDirectionCS0.getY() << "," << gvbtWheelDirectionCS0.getZ() << endl;
	cout << "gvbtWheelAxleCS : " << gvbtWheelAxleCS.getX() << "," << gvbtWheelAxleCS.getY() << "," << gvbtWheelAxleCS.getZ() << endl;
	*/

	//cout << "--------------------" << endl;
	//cout << "gfEngineForce: " << gfEngineForce << " - gfBreakingForce: " << gfBreakingForce << endl ;
	//cout << "gfMaxEngineForce: " << gfMaxEngineForce << " - gfMaxBreakingForce: " << gfMaxBreakingForce << endl ;
	//cout << "gfVehicleSteering: " << gfVehicleSteering << " - gfSteeringIncrement: " << gfSteeringIncrement << " - gfSteeringClamp: " << gfSteeringClamp  << endl ;
	//cout << "gfWheelRadius: " << gfWheelRadius << " - gfWheelWidth: " << gfWheelWidth << " - gfWheelFriction: " << gfWheelFriction  << endl ;
	//cout << "getLinearVelocity: " << mpbtVehicle->getRigidBody()->getLinearVelocity().getX() << "," << mpbtVehicle->getRigidBody()->getLinearVelocity().getY() << "," << mpbtVehicle->getRigidBody()->getLinearVelocity().getZ() << endl;
	//cout << "getTotalForce: " << mpbtVehicle->getRigidBody()->getTotalForce().getX() << "," << mpbtVehicle->getRigidBody()->getTotalForce().getY() << "," << mpbtVehicle->getRigidBody()->getTotalForce().getZ() << endl;
	//cout << "getTotalTorque: " << mpbtVehicle->getRigidBody()->getTotalTorque().getX() << "," << mpbtVehicle->getRigidBody()->getTotalTorque().getY() << "," << mpbtVehicle->getRigidBody()->getTotalTorque().getZ() << endl;
	

	

}