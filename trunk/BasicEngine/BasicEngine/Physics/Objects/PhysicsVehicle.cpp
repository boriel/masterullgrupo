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
		int rightIndex = 0;
		int upIndex = 1;
		int forwardIndex = 2;
		btVector3 wheelDirectionCS0(0,-1,0);
		btVector3 wheelAxleCS(-1,0,0);
#endif



const int maxProxies = 32766;
const int maxOverlap = 65535;

///btRaycastVehicle is the interface for the constraint that implements the raycast vehicle
///notice that for higher-quality slow-moving vehicles, another approach might be better
///implementing explicit hinged-wheel constraints with cylinder collision, rather then raycasts
float	gEngineForce = 0.f;
float	gBreakingForce = 0.f;

float	maxEngineForce = 1000.f;//this should be engine/velocity dependent
float	maxBreakingForce = 100.f;


float	gVehicleSteering = 0.f;
float	steeringIncrement = 0.04f;
float	steeringClamp = 0.3f;
float	wheelRadius = 0.5f;
float	wheelWidth = 0.4f;
float	wheelFriction = 1000;//BT_LARGE_FLOAT;
float	suspensionStiffness = 20.f;
float	suspensionDamping = 2.3f;
float	suspensionCompression = 4.4f;
float	rollInfluence = 0.1f;//1.0f;


btScalar suspensionRestLength(0.6);

#define CUBE_HALF_EXTENTS 1




//Yorman begin  para borrar
#define SCALING 1.
#define START_POS_X -3
#define START_POS_Y -1
#define START_POS_Z 5
//Yorman end





cPhysicsVehicle::cPhysicsVehicle() 
	//: m_carChassis(0), m_cameraHeight(4.f), m_minCameraDistance(3.f), m_maxCameraDistance(10.f), m_indexVertexArrays(0), m_vertices(0)
{ //Constructor con parámetros por defecto
	m_vehicle = 0;
	m_wheelShape = 0;
	//m_cameraPosition = btVector3(30,30,30);
	m_carChassis = 0;
	m_cameraHeight = 4.f;
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
	int i;
	for (i=lpDynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--) 
	{
		btCollisionObject* obj = lpDynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState()) {
			delete body->getMotionState();
		}
		lpDynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	//delete collision shapes
	for (int luiIndex = 0; luiIndex < mabtCollisionShapes.size(); luiIndex++) 
	{
		btCollisionShape* lbtShape = mabtCollisionShapes[luiIndex];
		delete lbtShape;
	}

	delete m_indexVertexArrays;
	delete m_vertices;

	//delete dynamics world
	delete lpDynamicsWorld;

	delete m_vehicleRayCaster;
	delete m_vehicle;
	delete m_wheelShape;

	//delete solver
	delete m_constraintSolver;

	//delete broadphase
	delete m_overlappingPairCache;

	//delete dispatcher
	delete m_dispatcher;

	delete m_collisionConfiguration;
}


















//Inicializamos la física del vehiculo
void cPhysicsVehicle::Init()
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
	btTransform tr;
	tr.setIdentity();



/*

// HACIENDO EL SUELO y triangulándolo
//either use heightfield or triangle mesh
#define  USE_TRIMESH_GROUND 1
#ifdef USE_TRIMESH_GROUND
	int i;

	const float TRIANGLE_SIZE=20.f;

	//create a triangle-mesh ground
	int vertStride = sizeof(btVector3);
	int indexStride = 3*sizeof(int);

	const int NUM_VERTS_X = 20;
	const int NUM_VERTS_Y = 20;
	const int totalVerts = NUM_VERTS_X*NUM_VERTS_Y;
	
	const int totalTriangles = 2*(NUM_VERTS_X-1)*(NUM_VERTS_Y-1);

	m_vertices = new btVector3[totalVerts];
	int*	gIndices = new int[totalTriangles*3];

	

	for ( i=0;i<NUM_VERTS_X;i++)
	{
		for (int j=0;j<NUM_VERTS_Y;j++)
		{
			float wl = .2f;
			//height set to zero, but can also use curved landscape, just uncomment out the code
			float height = 0.f;//20.f*sinf(float(i)*wl)*cosf(float(j)*wl);
#ifdef FORCE_ZAXIS_UP
			m_vertices[i+j*NUM_VERTS_X].setValue(
				(i-NUM_VERTS_X*0.5f)*TRIANGLE_SIZE,
				(j-NUM_VERTS_Y*0.5f)*TRIANGLE_SIZE,
				height
				);

#else
			m_vertices[i+j*NUM_VERTS_X].setValue(
				(i-NUM_VERTS_X*0.5f)*TRIANGLE_SIZE,
				height,
				(j-NUM_VERTS_Y*0.5f)*TRIANGLE_SIZE);
#endif

		}
	}

	int index=0;
	for ( i=0;i<NUM_VERTS_X-1;i++)
	{
		for (int j=0;j<NUM_VERTS_Y-1;j++)
		{
			gIndices[index++] = j*NUM_VERTS_X+i;
			gIndices[index++] = j*NUM_VERTS_X+i+1;
			gIndices[index++] = (j+1)*NUM_VERTS_X+i+1;

			gIndices[index++] = j*NUM_VERTS_X+i;
			gIndices[index++] = (j+1)*NUM_VERTS_X+i+1;
			gIndices[index++] = (j+1)*NUM_VERTS_X+i;
		}
	}
	
	m_indexVertexArrays = new btTriangleIndexVertexArray(totalTriangles,
		gIndices,
		indexStride,
		totalVerts,(btScalar*) &m_vertices[0].x(),vertStride);

	bool useQuantizedAabbCompression = true;
	groundShape = new btBvhTriangleMeshShape(m_indexVertexArrays,useQuantizedAabbCompression);
	
	tr.setOrigin(btVector3(0,-4.5f,0));

#else
	//testing btHeightfieldTerrainShape
	int width=128;
	int length=128;
	unsigned char* heightfieldData = new unsigned char[width*length];
	{
		for (int i=0;i<width*length;i++)
		{
			heightfieldData[i]=0;
		}
	}

	char*	filename="heightfield128x128.raw";
	FILE* heightfieldFile = fopen(filename,"r");
	if (!heightfieldFile)
	{
		filename="../../heightfield128x128.raw";
		heightfieldFile = fopen(filename,"r");
	}
	if (heightfieldFile)
	{
		int numBytes =fread(heightfieldData,1,width*length,heightfieldFile);
		//btAssert(numBytes);
		if (!numBytes)
		{
			printf("couldn't read heightfield at %s\n",filename);
		}
		fclose (heightfieldFile);
	}
	

	btScalar maxHeight = 20000.f;
	
	bool useFloatDatam=false;
	bool flipQuadEdges=false;

	btHeightfieldTerrainShape* heightFieldShape = new btHeightfieldTerrainShape(width,length,heightfieldData,maxHeight,upIndex,useFloatDatam,flipQuadEdges);;
	groundShape = heightFieldShape;
	
	heightFieldShape->setUseDiamondSubdivision(true);

	btVector3 localScaling(20,20,20);
	localScaling[upIndex]=1.f;
	groundShape->setLocalScaling(localScaling);

	tr.setOrigin(btVector3(0,-64.5f,0));

#endif //

	//m_collisionShapes.push_back(groundShape);
	cPhysicsManager::Get().AddCollisionShape(groundShape);

	//create ground object
	LocalCreateRigidBody(0, tr, groundShape); //YORMAN ESTA FUNCION PUEDE ESTAR INTERESANTE

*/







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
	btCollisionShape* chassisShape = new btBoxShape(btVector3(1.f,0.5f,2.f));
	//cPhysicsManager::Get().AddCollisionShape(chassisShape);
	mabtCollisionShapes.push_back(chassisShape);

	btCompoundShape* compound = new btCompoundShape();
	//cPhysicsManager::Get().AddCollisionShape(compound);
	mabtCollisionShapes.push_back(compound);
	btTransform localTrans;
	localTrans.setIdentity();
	//localTrans effectively shifts the center of mass with respect to the chassis
	localTrans.setOrigin(btVector3(0,1,0));
#endif

	compound->addChildShape(localTrans,chassisShape);

	tr.setOrigin(btVector3(0,0.f,0));

	m_carChassis = LocalCreateRigidBody(800,tr,compound);//chassisShape);
	//m_carChassis->setDamping(0.2,0.2);
	
	m_wheelShape = new btCylinderShapeX(btVector3(wheelWidth,wheelRadius,wheelRadius));
	
	//clientResetScene();

	/// create vehicle
	{
		
		m_vehicleRayCaster = new btDefaultVehicleRaycaster(lpDynamicsWorld);
		
		m_vehicle = new btRaycastVehicle(m_tuning,m_carChassis,m_vehicleRayCaster);
		
		///never deactivate the vehicle
		m_carChassis->setActivationState(DISABLE_DEACTIVATION);

		
		//btRigidBody* lbtrb =  m_vehicle->getRigidBody();


		lpDynamicsWorld->addVehicle(m_vehicle);

		float connectionHeight = 1.2f;

	
		bool isFrontWheel=true;

		//choose coordinate system
		m_vehicle->setCoordinateSystem(rightIndex,upIndex,forwardIndex);

#ifdef FORCE_ZAXIS_UP
		btVector3 connectionPointCS0(CUBE_HALF_EXTENTS-(0.3*wheelWidth),2*CUBE_HALF_EXTENTS-wheelRadius, connectionHeight);
#else
		btVector3 connectionPointCS0(CUBE_HALF_EXTENTS-(0.3*wheelWidth),connectionHeight,2*CUBE_HALF_EXTENTS-wheelRadius);
#endif

		m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
#ifdef FORCE_ZAXIS_UP
		connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(0.3*wheelWidth),2*CUBE_HALF_EXTENTS-wheelRadius, connectionHeight);
#else
		connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(0.3*wheelWidth),connectionHeight,2*CUBE_HALF_EXTENTS-wheelRadius);
#endif

		m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
#ifdef FORCE_ZAXIS_UP
		connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(0.3*wheelWidth),-2*CUBE_HALF_EXTENTS+wheelRadius, connectionHeight);
#else
		connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(0.3*wheelWidth),connectionHeight,-2*CUBE_HALF_EXTENTS+wheelRadius);
#endif //FORCE_ZAXIS_UP
		isFrontWheel = false;
		m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
#ifdef FORCE_ZAXIS_UP
		connectionPointCS0 = btVector3(CUBE_HALF_EXTENTS-(0.3*wheelWidth),-2*CUBE_HALF_EXTENTS+wheelRadius, connectionHeight);
#else
		connectionPointCS0 = btVector3(CUBE_HALF_EXTENTS-(0.3*wheelWidth),connectionHeight,-2*CUBE_HALF_EXTENTS+wheelRadius);
#endif
		m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
		
		for (int i=0;i<m_vehicle->getNumWheels();i++)
		{
			btWheelInfo& wheel = m_vehicle->getWheelInfo(i);
			wheel.m_suspensionStiffness = suspensionStiffness;
			wheel.m_wheelsDampingRelaxation = suspensionDamping;
			wheel.m_wheelsDampingCompression = suspensionCompression;
			wheel.m_frictionSlip = wheelFriction;
			wheel.m_rollInfluence = rollInfluence;
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

void cPhysicsVehicle::Update(void) 
{ //Update

	btTransform trans;
	m_vehicle->getRigidBody()->getMotionState()->getWorldTransform(trans);
	
	//mpbtRigidBody->getMotionState()->getWorldTransform(trans);
 
	std::cout << "Vehicle: (" << trans.getOrigin().getX() << "," <<  trans.getOrigin().getY() << "," << trans.getOrigin().getZ() << ")" << std::endl;
}



//Obtenemos la posicion central del objeto
cVec3 cPhysicsVehicle::GetPosition ()
{
	cVec3 lPosition;

	btTransform lbtTransform;
	//mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform);
	m_vehicle->getRigidBody()->getMotionState()->getWorldTransform(lbtTransform);


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
	m_vehicle->getRigidBody()->getMotionState()->getWorldTransform(lbtTransform);

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
		case eIA_KeyI:  //arriba
			gEngineForce = maxEngineForce;
			gBreakingForce = 0.f;
			//ApplyImpulse(cVec3(0,0,0), cVec3 (0,0,0));
			
			break;

		case eIA_KeyK: //abajo
			//gBreakingForce = maxBreakingForce; 
			//gEngineForce = 0.f;
			gEngineForce = -maxEngineForce;
			gBreakingForce = 0.f;
			
			break;

		case eIA_KeyJ:  //izquierda
			gVehicleSteering += steeringIncrement;
			if (gVehicleSteering > steeringClamp)
				gVehicleSteering = steeringClamp;
			
			break;

		case eIA_KeyL: //derecha
			gVehicleSteering -= steeringIncrement;
			if (gVehicleSteering < -steeringClamp)
				gVehicleSteering = -steeringClamp;
			
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	
	{			
		int wheelIndex = 2;
		m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
		m_vehicle->setBrake(gBreakingForce,wheelIndex);
		wheelIndex = 3;
		m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
		m_vehicle->setBrake(gBreakingForce,wheelIndex);


		wheelIndex = 0;
		m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
		wheelIndex = 1;
		m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);

	}


	float dt = getDeltaTimeMicroseconds() * 0.000001f;
	
	if (lpDynamicsWorld)
	{
		//during idle mode, just run 1 simulation step maximum
		//int maxSimSubSteps = m_idle ? 1 : 2;
		//if (m_idle)
		//	dt = 1.0/420.f;

		dt = 1.0/420.f;

		int maxSimSubSteps = 1; //temp a mano
		int numSimSteps = lpDynamicsWorld->stepSimulation(dt, maxSimSubSteps);
		

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