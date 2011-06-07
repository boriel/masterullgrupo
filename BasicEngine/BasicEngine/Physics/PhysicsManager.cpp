
#include "PhysicsManager.h"
#include "..\Game\Object\ObjectManager.h"
#include "PhysicsObject.h"
#include "Objects\PhysicsPlayer.h"
#include "Objects\PhysicsPista.h"
#include "Objects\PhysicsVehicle.h"

//para pintar el render
#include "GlutStuff.h"
#include "GLDebugDrawer.h"



bool cPhysicsManager::Init () 
{

	//========================
	//Creando el mundo físico
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

	GLDebugDrawer*	gDebugDrawer = new GLDebugDrawer;
	miDebugMode = 0;  //0 = Sin debug
	(*gDebugDrawer).setDebugMode(miDebugMode);

	//m_debugMode |= btIDebugDraw::DBG_DrawWireframe;
	mpbtDynamicsWorld->setDebugDrawer(gDebugDrawer);

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
	//Actualizamos todos el mundo físicos
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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(btScalar(0.7),btScalar(0.7),btScalar(0.7),btScalar(0));

	//  glEnable(GL_CULL_FACE);
	//  glCullFace(GL_BACK);
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

		
		mpShapeDrawer->drawOpenGL(m,colObj->getCollisionShape(), wireColor, GetDebugMode(), aabbMin, aabbMax); 

		if (!(GetDebugMode() & btIDebugDraw::DBG_DrawWireframe))
		{
			switch(liPass)
			{

			case	0:	
				mpShapeDrawer->drawOpenGL(m,colObj->getCollisionShape(), wireColor, GetDebugMode(), aabbMin, aabbMax); 
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

	//updateCamera();

	if (mpbtDynamicsWorld)
	{	
		/*
		if(m_enableshadows)
		{
			glClear(GL_STENCIL_BUFFER_BIT);
			glEnable(GL_CULL_FACE);
			renderscene(0);

			glDisable(GL_LIGHTING);
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_LEQUAL);
			glEnable(GL_STENCIL_TEST);
			glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
			glStencilFunc(GL_ALWAYS,1,0xFFFFFFFFL);
			glFrontFace(GL_CCW);
			glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);
			renderscene(1);
			glFrontFace(GL_CW);
			glStencilOp(GL_KEEP,GL_KEEP,GL_DECR);
			renderscene(1);
			glFrontFace(GL_CCW);

			glPolygonMode(GL_FRONT,GL_FILL);
			glPolygonMode(GL_BACK,GL_FILL);
			glShadeModel(GL_SMOOTH);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glEnable(GL_LIGHTING);
			glDepthMask(GL_TRUE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			glEnable(GL_CULL_FACE);
			glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

			glDepthFunc(GL_LEQUAL);
			glStencilFunc( GL_NOTEQUAL, 0, 0xFFFFFFFFL );
			glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
			glDisable(GL_LIGHTING);
			renderscene(2);
			glEnable(GL_LIGHTING);
			glDepthFunc(GL_LESS);
			glDisable(GL_STENCIL_TEST);
			glDisable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
			renderscene(0);
		}
*/

/*
		glDisable(GL_CULL_FACE);
		renderscene(0);

		int	xOffset = 10;
		int yStart = 20;
		int yIncr = 20;


		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);

		if ((m_debugMode & btIDebugDraw::DBG_NoHelpText)==0)
		{
			setOrthographicProjection();

			showProfileInfo(xOffset,yStart,yIncr);

#ifdef USE_QUICKPROF

		
			if ( getDebugMode() & btIDebugDraw::DBG_ProfileTimings)
			{
				static int counter = 0;
				counter++;
				std::map<std::string, hidden::ProfileBlock*>::iterator iter;
				for (iter = btProfiler::mProfileBlocks.begin(); iter != btProfiler::mProfileBlocks.end(); ++iter)
				{
					char blockTime[128];
					sprintf(blockTime, "%s: %lf",&((*iter).first[0]),btProfiler::getBlockTime((*iter).first, btProfiler::BLOCK_CYCLE_SECONDS));//BLOCK_TOTAL_PERCENT));
					glRasterPos3f(xOffset,yStart,0);
					GLDebugDrawString(BMF_GetFont(BMF_kHelvetica10),blockTime);
					yStart += yIncr;

				}

			}
#endif //USE_QUICKPROF


			

			resetPerspectiveProjection();
		}

		glDisable(GL_LIGHTING);

		*/
	}

	//updateCamera();
	


	glDisable(GL_CULL_FACE);
	RenderScene(0);

}








/*
//Hay que sacar la rotacion y posicion inicial del objeto
void cPhysicsManager::InitAllPhysics ()
{
	
	for (unsigned luiIndex = 0; luiIndex < mPhysicsPista.size(); ++luiIndex ) 
	{
		cVec3 lPosition = cObjectManager::Get().GetPosition(mPhysicsPista[luiIndex]->GetTypeObject(), mPhysicsPista[luiIndex]->GetModelName());
		cQuaternion lRotacionInicial = cObjectManager::Get().GetRotacionInicial(mPhysicsPista[luiIndex]->GetTypeObject(), mPhysicsPista[luiIndex]->GetModelName());
		//cObjectManager::Get().GetPosition(mPhysicsPista[luiIndex]->GetTypeObject(), mPhysicsPista[luiIndex]->GetModelName());
		((cPhysicsPista*)mPhysicsPista[luiIndex])->Init(lPosition, lRotacionInicial);
	}

	for (unsigned luiIndex = 0; luiIndex < mPhysicsPlayer.size(); ++luiIndex ) 
	{
		cVec3 lPosition = cObjectManager::Get().GetPosition(mPhysicsPlayer[luiIndex]->GetTypeObject(), mPhysicsPlayer[luiIndex]->GetModelName());
		cQuaternion lRotacionInicial = cObjectManager::Get().GetRotacionInicial(mPhysicsPlayer[luiIndex]->GetTypeObject(), mPhysicsPlayer[luiIndex]->GetModelName());
		//cObjectManager::Get().GetPosition(mPhysicsPista[luiIndex]->GetTypeObject(), mPhysicsPista[luiIndex]->GetModelName());
		((cPhysicsPlayer*)mPhysicsPlayer[luiIndex])->Init(lPosition, lRotacionInicial);
	}

	for (unsigned luiIndex = 0; luiIndex < mPhysicsVehicle.size(); ++luiIndex ) 
		((cPhysicsVehicle*)mPhysicsVehicle[luiIndex])->Init();

}
*/
/*
cPhysicsObject* cPhysicsManager::GetPhysicsObjectPtr(const string lsType, const string lsModelName)
{
	if (lsType == "Pista")
	{
		for (unsigned luiIndex = 0; luiIndex < mPhysicsPista.size(); ++luiIndex ) 
			if (mPhysicsPista[luiIndex]->GetModelName() == lsModelName)
				return mPhysicsPista[luiIndex];
	}

	else if (lsType == "Player")
	{
		for (unsigned luiIndex = 0; luiIndex < mPhysicsPlayer.size(); ++luiIndex ) 
			if (mPhysicsPlayer[luiIndex]->GetModelName() == lsModelName)
				return mPhysicsPlayer[luiIndex];
	}


	return NULL;
}
*/

//Pintado todo el mundo, basandonos en el bullet, pero pintando con nuestro motor.
//sacado de btCollisionWorld: 1390
void	cPhysicsManager::RenderWorldDebug()
{


	



/*
	if (getDebugDrawer() && getDebugDrawer()->getDebugMode() & btIDebugDraw::DBG_DrawContactPoints)
	{
		int numManifolds = getDispatcher()->getNumManifolds();
		btVector3 color(0,0,0);
		for (int i=0;i<numManifolds;i++)
		{
			btPersistentManifold* contactManifold = getDispatcher()->getManifoldByIndexInternal(i);
			//btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
			//btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());

			int numContacts = contactManifold->getNumContacts();
			for (int j=0;j<numContacts;j++)
			{
				btManifoldPoint& cp = contactManifold->getContactPoint(j);
				getDebugDrawer()->drawContactPoint(cp.m_positionWorldOnB,cp.m_normalWorldOnB,cp.getDistance(),cp.getLifeTime(),color);
			}
		}
	}
*/


	//if (getDebugDrawer() && getDebugDrawer()->getDebugMode() & (btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawAabb))
	//{

	//	int i;

		btCollisionObjectArray lbtCollisionObjects =  mpbtDynamicsWorld->getCollisionObjectArray();
		for (int luiIndex = 0; luiIndex <  lbtCollisionObjects.size(); luiIndex++)
		{
			btCollisionObject* colObj = lbtCollisionObjects[luiIndex];
			if ((colObj->getCollisionFlags() & btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT)==0)
			{
				
				//if (getDebugDrawer() && getDebugDrawer()->getDebugMode() & btIDebugDraw::DBG_DrawWireframe)
				{
					
					btVector3 color(btScalar(1.),btScalar(1.),btScalar(1.));
					
					switch(colObj->getActivationState())
					{
					case  ACTIVE_TAG:
						color = btVector3(btScalar(1.),btScalar(1.),btScalar(1.)); break;
					case ISLAND_SLEEPING:
						color =  btVector3(btScalar(0.),btScalar(1.),btScalar(0.));break;
					case WANTS_DEACTIVATION:
						color = btVector3(btScalar(0.),btScalar(1.),btScalar(1.));break;
					case DISABLE_DEACTIVATION:
						color = btVector3(btScalar(1.),btScalar(0.),btScalar(0.));break;
					case DISABLE_SIMULATION:
						color = btVector3(btScalar(1.),btScalar(1.),btScalar(0.));break;
					default:
						{
							color = btVector3(btScalar(1),btScalar(0.),btScalar(0.));
						}
					};
					
					
					//debugDrawObject(colObj->getWorldTransform(),colObj->getCollisionShape(),color);
					RenderObjectDebug(colObj->getWorldTransform(),colObj->getCollisionShape(),color);
					
				}
				
				/*
				if (m_debugDrawer && (m_debugDrawer->getDebugMode() & btIDebugDraw::DBG_DrawAabb))
				{
					btVector3 minAabb,maxAabb;
					btVector3 colorvec(1,0,0);
					colObj->getCollisionShape()->getAabb(colObj->getWorldTransform(), minAabb,maxAabb);
					btVector3 contactThreshold(gContactBreakingThreshold,gContactBreakingThreshold,gContactBreakingThreshold);
					minAabb -= contactThreshold;
					maxAabb += contactThreshold;

					btVector3 minAabb2,maxAabb2;

					if(colObj->getInternalType()==btCollisionObject::CO_RIGID_BODY)
					{
						colObj->getCollisionShape()->getAabb(colObj->getInterpolationWorldTransform(),minAabb2,maxAabb2);
						minAabb2 -= contactThreshold;
						maxAabb2 += contactThreshold;
						minAabb.setMin(minAabb2);
						maxAabb.setMax(maxAabb2);
					}

					m_debugDrawer->drawAabb(minAabb,maxAabb,colorvec);
				}
				*/
			}

		}
		
	//}


}



//Sacado de la librería de btCollsionWorld a ajustandolo a nuestro render y nustro sistema. Cambiada unas cuentas cosas.
//btCollisionWorld.cpp Línea 1217
void cPhysicsManager::RenderObjectDebug(const btTransform& worldTransform, const btCollisionShape* shape, const btVector3& color)
{

	// Draw a small simplex at the center of the object
	//getDebugDrawer()->drawTransform(worldTransform,1);

	

	if (shape->getShapeType() == COMPOUND_SHAPE_PROXYTYPE)
	{
		const btCompoundShape* compoundShape = static_cast<const btCompoundShape*>(shape);
		for (int i = compoundShape->getNumChildShapes() - 1 ; i >=0 ; i--)
		{
			btTransform childTrans = compoundShape->getChildTransform(i);
			const btCollisionShape* colShape = compoundShape->getChildShape(i);
			RenderObjectDebug(worldTransform * childTrans, colShape, color);  //Recursivo
		}

	} 
	
	else
	{
		cPhysicsObject lTemp = cPhysicsObject();
		//btCollisionWorld lbCollisionWorld = btCollisionWorld();
		btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld(); 

		switch (shape->getShapeType())
		{

		case BOX_SHAPE_PROXYTYPE:
			{
				const btBoxShape* boxShape = static_cast<const btBoxShape*>(shape);
				btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
				//getDebugDrawer()->drawBox(-halfExtents,halfExtents,worldTransform,color);
				//lTemp.RenderBoxDebug(-halfExtents, halfExtents, worldTransform, color);
				lpDynamicsWorld->getDebugDrawer()->drawBox(-halfExtents,halfExtents,worldTransform,color);
				break;
			}
		/*
		case SPHERE_SHAPE_PROXYTYPE:
			{
				const btSphereShape* sphereShape = static_cast<const btSphereShape*>(shape);
				btScalar radius = sphereShape->getMargin();//radius doesn't include the margin, so draw with margin

				getDebugDrawer()->drawSphere(radius, worldTransform, color);
				break;
			}
		case MULTI_SPHERE_SHAPE_PROXYTYPE:
			{
				const btMultiSphereShape* multiSphereShape = static_cast<const btMultiSphereShape*>(shape);

				btTransform childTransform;
				childTransform.setIdentity();

				for (int i = multiSphereShape->getSphereCount()-1; i>=0;i--)
				{
					childTransform.setOrigin(multiSphereShape->getSpherePosition(i));
					getDebugDrawer()->drawSphere(multiSphereShape->getSphereRadius(i), worldTransform*childTransform, color);
				}

				break;
			}
		case CAPSULE_SHAPE_PROXYTYPE:
			{
				const btCapsuleShape* capsuleShape = static_cast<const btCapsuleShape*>(shape);

				btScalar radius = capsuleShape->getRadius();
				btScalar halfHeight = capsuleShape->getHalfHeight();

				int upAxis = capsuleShape->getUpAxis();
				getDebugDrawer()->drawCapsule(radius, halfHeight, upAxis, worldTransform, color);
				break;
			}
		case CONE_SHAPE_PROXYTYPE:
			{
				const btConeShape* coneShape = static_cast<const btConeShape*>(shape);
				btScalar radius = coneShape->getRadius();//+coneShape->getMargin();
				btScalar height = coneShape->getHeight();//+coneShape->getMargin();

				int upAxis= coneShape->getConeUpIndex();
				getDebugDrawer()->drawCone(radius, height, upAxis, worldTransform, color);
				break;

			}
		case CYLINDER_SHAPE_PROXYTYPE:
			{
				const btCylinderShape* cylinder = static_cast<const btCylinderShape*>(shape);
				int upAxis = cylinder->getUpAxis();
				btScalar radius = cylinder->getRadius();
				btScalar halfHeight = cylinder->getHalfExtentsWithMargin()[upAxis];
				getDebugDrawer()->drawCylinder(radius, halfHeight, upAxis, worldTransform, color);
				break;
			}
		
		
		case STATIC_PLANE_PROXYTYPE:
			{
				const btStaticPlaneShape* staticPlaneShape = static_cast<const btStaticPlaneShape*>(shape);
				btScalar planeConst = staticPlaneShape->getPlaneConstant();
				const btVector3& planeNormal = staticPlaneShape->getPlaneNormal();
				getDebugDrawer()->drawPlane(planeNormal, planeConst,worldTransform, color);
				//lTemp.RenderBoxDebug(planeNormal, planeConst, worldTransform, color);
				break;

			}
			*/
		/*	
		default:
			{

				if (shape->isConcave())
				{
					btConcaveShape* concaveMesh = (btConcaveShape*) shape;

					///@todo pass camera, for some culling? no -> we are not a graphics lib
					btVector3 aabbMax(btScalar(BT_LARGE_FLOAT),btScalar(BT_LARGE_FLOAT),btScalar(BT_LARGE_FLOAT));
					btVector3 aabbMin(btScalar(-BT_LARGE_FLOAT),btScalar(-BT_LARGE_FLOAT),btScalar(-BT_LARGE_FLOAT));

					DebugDrawcallback drawCallback(getDebugDrawer(),worldTransform,color);
					concaveMesh->processAllTriangles(&drawCallback,aabbMin,aabbMax);

				}

				if (shape->getShapeType() == CONVEX_TRIANGLEMESH_SHAPE_PROXYTYPE)
				{
					btConvexTriangleMeshShape* convexMesh = (btConvexTriangleMeshShape*) shape;
					//todo: pass camera for some culling			
					btVector3 aabbMax(btScalar(BT_LARGE_FLOAT),btScalar(BT_LARGE_FLOAT),btScalar(BT_LARGE_FLOAT));
					btVector3 aabbMin(btScalar(-BT_LARGE_FLOAT),btScalar(-BT_LARGE_FLOAT),btScalar(-BT_LARGE_FLOAT));
					//DebugDrawcallback drawCallback;
					DebugDrawcallback drawCallback(getDebugDrawer(),worldTransform,color);
					convexMesh->getMeshInterface()->InternalProcessAllTriangles(&drawCallback,aabbMin,aabbMax);
				}


				/// for polyhedral shapes
				if (shape->isPolyhedral())
				{
					btPolyhedralConvexShape* polyshape = (btPolyhedralConvexShape*) shape;

					int i;
					if (polyshape->getConvexPolyhedron())
					{
						const btConvexPolyhedron* poly = polyshape->getConvexPolyhedron();
						for (i=0;i<poly->m_faces.size();i++)
						{
							btVector3 centroid(0,0,0);
							int numVerts = poly->m_faces[i].m_indices.size();
							if (numVerts)
							{
								int lastV = poly->m_faces[i].m_indices[numVerts-1];
								for (int v=0;v<poly->m_faces[i].m_indices.size();v++)
								{
									int curVert = poly->m_faces[i].m_indices[v];
									centroid+=poly->m_vertices[curVert];
									getDebugDrawer()->drawLine(worldTransform*poly->m_vertices[lastV],worldTransform*poly->m_vertices[curVert],color);
									lastV = curVert;
								}
							}
							centroid*= 1./btScalar(numVerts);

							btVector3 normalColor(1,1,0);
							btVector3 faceNormal(poly->m_faces[i].m_plane[0],poly->m_faces[i].m_plane[1],poly->m_faces[i].m_plane[2]);
							getDebugDrawer()->drawLine(worldTransform*centroid,worldTransform*(centroid+faceNormal),normalColor);
							
							
						}

						
					} else
					{
						for (i=0;i<polyshape->getNumEdges();i++)
						{
							btVector3 a,b;
							polyshape->getEdge(i,a,b);
							btVector3 wa = worldTransform * a;
							btVector3 wb = worldTransform * b;
							getDebugDrawer()->drawLine(wa,wb,color);
						}
					}


				}
			}//default
			*/
		} //case
	}

}

