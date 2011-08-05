
#include "PhysicsManager.h"
#include "..\Game\Object\ObjectManager.h"
#include "PhysicsObject.h"
#include "Objects\PhysicsPlayer.h"
#include "Objects\PhysicsPista.h"
#include "Objects\PhysicsVehicle.h"

//para pintar el render
#include "GlutStuff.h"
//#include "GLDebugDrawer.h"



bool cPhysicsManager::Init () 
{

	//========================
	//Creando el mundo f�sico
	mpBroadphase = new btDbvtBroadphase(); // Build the broadphase

	// Set up the collision configuration and dispatcher
	mpCollisionConfiguration = new btDefaultCollisionConfiguration();
	mpDispatcher = new btCollisionDispatcher(mpCollisionConfiguration);
	
	mpSolver = new btSequentialImpulseConstraintSolver; // The actual physics solver
 
/* configracion del vehicle
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
	m_overlappingPairCache = new btAxisSweep3(worldMin,worldMax);
	m_constraintSolver = new btSequentialImpulseConstraintSolver();
	lpDynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_overlappingPairCache,m_constraintSolver,m_collisionConfiguration);
*/



	// The world.
	mpbtDynamicsWorld = new btDiscreteDynamicsWorld(mpDispatcher, mpBroadphase, mpSolver, mpCollisionConfiguration);
	//mpbtDynamicsWorld = new btDynamicsWorld(mpDispatcher, mpBroadphase, mpSolver, mpCollisionConfiguration);
	mpbtDynamicsWorld->setGravity(btVector3(0,-10,0));


	//GLDebugDrawer*	gDebugDrawer = new GLDebugDrawer;
	mpbtDebugDrawer = new GLDebugDrawer;


	miDebugMode = 0;  //0 = Sin debug (solo render), //1 = Debug + Render, //2 = Debug Only (F9, F10, F11)
	//mbDebugMode = false;
	(*mpbtDebugDrawer).setDebugMode(miDebugMode);

	//m_debugMode |= btIDebugDraw::DBG_DrawWireframe;
	mpbtDynamicsWorld->setDebugDrawer(mpbtDebugDrawer);
	

	mpShapeDrawer = new GL_ShapeDrawer ();
	mpShapeDrawer->enableTexture(true);
	mEnableshadows = false;


	//msFilename = (".\\Data\\" + std::string("Resources.xml"));
	//LoadObjectsXmlCollision();
	
	/*
	//metiendo a mano el vehicle por ahora
	//la llamada se hace en InitAllPhysics
	cPhysicsObject* lPhysicsObjectPtr = new cPhysicsVehicle;
	//lPhysicsObjectPtr->CreateBoxShape(lVec3);
	(*lPhysicsObjectPtr).SetTypeObject ("Vehicle");
	(*lPhysicsObjectPtr).SetModelName("VehicleVacioInitAMano");
	mPhysicsVehicle.push_back(lPhysicsObjectPtr);
	*/

	/*
	//metiendo a mano un player de ejemplo
	cPhysicsObject* lPhysicsObjectPtr2 = new cPhysicsPlayer;
	(lPhysicsObjectPtr2)->CreateBoxShape(cVec3(1.0f, 1.0f, 1.0f));
	(*lPhysicsObjectPtr2).SetTypeObject ("Player");
	(*lPhysicsObjectPtr2).SetModelName("PlayerAAmano");
	mPhysicsPlayer.push_back(lPhysicsObjectPtr2);
	*/


	return true;	
}

bool cPhysicsManager::Deinit () 
{
	delete mpbtDynamicsWorld;
	delete mpSolver;
	delete mpDispatcher;
	delete mpCollisionConfiguration;
	delete mpBroadphase;
 


	return true;
}

//update
void cPhysicsManager::Update(float lfTimestep) 
{ 
	//Actualizamos todos el mundo f�sicos
	//mpDynamicsWorld->stepSimulation(1/60.f,10);
	mpbtDynamicsWorld->stepSimulation(lfTimestep, 10); //Actualizamos el mundo



	/*
	for (unsigned luiIndex = 0; luiIndex < mPhysicsPista.size(); ++luiIndex ) 
		mPhysicsPista[luiIndex]->Update();

	for (unsigned luiIndex = 0; luiIndex < mPhysicsPlayer.size(); ++luiIndex ) 
		mPhysicsPlayer[luiIndex]->Update();

	for (unsigned luiIndex = 0; luiIndex < mPhysicsVehicle.size(); ++luiIndex ) 
		mPhysicsVehicle[luiIndex]->Update();
	*/
}

//Renderizando la parte de debug de las collision
void cPhysicsManager::Render() 
{

	
	//for (unsigned luiIndex = 0; luiIndex < mPhysicsVehicle.size(); ++luiIndex ) 
	//	mPhysicsVehicle[luiIndex]->RenderWorldDebug(); 
	

	
	
	//btCollisionWorld::debugDrawWorld;

	//btCollisionWorld bt = btCollisionWorld.debugDrawWorld;

	//mpbtDynamicsWorld->debugDrawWorld();
	//m_dynamicsWorld->debugDrawWorld();

	
	//RenderWorldDebug(); //mio en nuestro motor


	//btCollisionWorld lbCollisionWorld = btCollisionWorld();
	//void	btCollisionWorld::debugDrawWorld()
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld(); 
	//lpDynamicsWorld->debugDrawWorld();
	RenderMe();
	if (mpbtDynamicsWorld)
		mpbtDynamicsWorld->debugDrawWorld();
}

void cPhysicsManager::MyInit(void)
{

	GLfloat light_ambient[] = { btScalar(0.2), btScalar(0.2), btScalar(0.2), btScalar(1.0) };
	GLfloat light_diffuse[] = { btScalar(1.0), btScalar(1.0), btScalar(1.0), btScalar(1.0) };
	GLfloat light_specular[] = { btScalar(1.0), btScalar(1.0), btScalar(1.0), btScalar(1.0 )};
	/*	light_position is NOT default value	*/
	GLfloat light_position0[] = { btScalar(1.0), btScalar(10.0), btScalar(1.0), btScalar(0.0 )};
	GLfloat light_position1[] = { btScalar(-1.0), btScalar(-10.0), btScalar(-1.0), btScalar(0.0) };
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);


	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LESS);

	glClearColor(btScalar(0.7),btScalar(0.7),btScalar(0.7),btScalar(0));
	
}

void cPhysicsManager::Disable(void){
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);


	//glDisable(GL_DEPTH_TEST);
}

void cPhysicsManager::RenderScene(int liPass)
{
	btScalar	m[16];
	btMatrix3x3	rot;rot.setIdentity();
	const int	numObjects = mpbtDynamicsWorld->getNumCollisionObjects();
	btVector3 wireColor(1,0,0);
	for(int i=0;i<numObjects;i++)
	{
		btCollisionObject* colObj = mpbtDynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body=btRigidBody::upcast(colObj);
		if(body&&body->getMotionState())
		{
			btDefaultMotionState* myMotionState = (btDefaultMotionState*)body->getMotionState();
			myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(m);
			rot=myMotionState->m_graphicsWorldTrans.getBasis();
		}
		else
		{
			colObj->getWorldTransform().getOpenGLMatrix(m);
			rot=colObj->getWorldTransform().getBasis();
		}
		btVector3 wireColor(1.f,1.0f,0.5f); //wants deactivation
		if(i&1) wireColor=btVector3(0.f,0.0f,1.f);
		///color differently for active, sleeping, wantsdeactivation states
		if (colObj->getActivationState() == 1) //active
		{
			if (i & 1)
			{
				wireColor += btVector3 (1.f,0.f,0.f);
			}
			else
			{			
				wireColor += btVector3 (.5f,0.f,0.f);
			}
		}
		if(colObj->getActivationState()==2) //ISLAND_SLEEPING
		{
			if(i&1)
			{
				wireColor += btVector3 (0.f,1.f, 0.f);
			}
			else
			{
				wireColor += btVector3 (0.f,0.5f,0.f);
			}
		}

		btVector3 aabbMin,aabbMax;
		mpbtDynamicsWorld->getBroadphase()->getBroadphaseAabb(aabbMin,aabbMax);
		
		aabbMin-=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
		aabbMax+=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
//		printf("aabbMin=(%f,%f,%f)\n",aabbMin.getX(),aabbMin.getY(),aabbMin.getZ());
//		printf("aabbMax=(%f,%f,%f)\n",aabbMax.getX(),aabbMax.getY(),aabbMax.getZ());
//		m_dynamicsWorld->getDebugDrawer()->drawAabb(aabbMin,aabbMax,btVector3(1,1,1));

		
		//mpShapeDrawer->drawOpenGL(m,colObj->getCollisionShape(), wireColor, GetDebugMode(), aabbMin, aabbMax); 

		if ((GetDebugMode() & btIDebugDraw::DBG_DrawWireframe))
		{
			switch(liPass)
			{

			case	0:	
				// EL ERROR DE  QUE AL DARLE A F9 LAS LETRAS NO SE VEAN ES POR ESTA LINEA
				mpShapeDrawer->drawOpenGL(m, colObj->getCollisionShape(), wireColor, GetDebugMode(), aabbMin, aabbMax); 
				break;
			//case	1:	mpShapeDrawer->drawShadow(m,m_sundirection*rot,colObj->getCollisionShape(),aabbMin,aabbMax);break;
			//case	2:	mpShapeDrawer->drawOpenGL(m,colObj->getCollisionShape(),wireColor*btScalar(0.3),0,aabbMin,aabbMax);break;
			}
		}
		
	}
}



void  cPhysicsManager::RenderMe()
{
	MyInit();
	RenderScene(0);
}


void cPhysicsManager::CambiarDebugMode()
{

	if (miDebugMode == 0)
	{
		miDebugMode = 1;
		(*mpbtDebugDrawer).setDebugMode(miDebugMode);
	}
	else
	{
		miDebugMode = 0;
		Disable();
		(*mpbtDebugDrawer).setDebugMode(miDebugMode);
	}
}
