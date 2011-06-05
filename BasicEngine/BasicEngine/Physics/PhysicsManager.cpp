
#include "PhysicsManager.h"
#include "..\Game\Object\ObjectManager.h"
#include "PhysicsObject.h"
#include "Objects\PhysicsPlayer.h"
#include "Objects\PhysicsPista.h"
#include "Objects\PhysicsVehicle.h"

bool cPhysicsManager::Init () 
{

	//========================
	//Creando el mundo físico
	mpBroadphase = new btDbvtBroadphase(); // Build the broadphase

	// Set up the collision configuration and dispatcher
	mpCollisionConfiguration = new btDefaultCollisionConfiguration();
	mpDispatcher = new btCollisionDispatcher(mpCollisionConfiguration);
	
	mpSolver = new btSequentialImpulseConstraintSolver; // The actual physics solver
 
	// The world.
	mpDynamicsWorld = new btDiscreteDynamicsWorld(mpDispatcher, mpBroadphase, mpSolver, mpCollisionConfiguration);
	mpDynamicsWorld->setGravity(btVector3(0,-10,0));

	msFilename = (".\\Data\\" + std::string("Resources.xml"));

	LoadObjectsXmlCollision();

	return true;	
}

bool cPhysicsManager::Deinit () 
{
	delete mpDynamicsWorld;
	delete mpSolver;
	delete mpDispatcher;
	delete mpCollisionConfiguration;
	delete mpBroadphase;
 
	//delete collision shapes
	for (int luiIndex = 0; luiIndex < mabtCollisionShapes.size(); luiIndex++) 
	{
		btCollisionShape* lbtShape = mabtCollisionShapes[luiIndex];
		delete lbtShape;
	}


	return true;
}

//update
void cPhysicsManager::Update(float lfTimestep) 
{ 
	//Actualizamos todos el mundo físicos
	//mpDynamicsWorld->stepSimulation(1/60.f,10);
	mpDynamicsWorld->stepSimulation(lfTimestep, 10); //Actualizamos el mundo

	for (unsigned luiIndex = 0; luiIndex < mPhysicsPista.size(); ++luiIndex ) 
		mPhysicsPista[luiIndex]->Update();

	for (unsigned luiIndex = 0; luiIndex < mPhysicsPlayer.size(); ++luiIndex ) 
		mPhysicsPlayer[luiIndex]->Update();

}


void cPhysicsManager::LoadObjectsXmlCollision()
{
	TiXmlDocument lDoc;

	cVec3 lVec3 (-1,-1,-1);

	lDoc.LoadFile ((char*)msFilename.c_str());
	if (!lDoc.LoadFile())
	{
		OutputDebugString ("XML Load: FAILED\n");
	}

	
	TiXmlElement *lpElementResources;
	lpElementResources = lDoc.FirstChildElement ("Resources");

	
	TiXmlElement *lpElement;
	lpElement =  lpElementResources->FirstChildElement ("ObjectsCollision"); 
		

	for (lpElement = lpElement->FirstChildElement("ObjectCollision"); lpElement; lpElement = lpElement->NextSiblingElement()) 
	{
		std::string  lsModelName, lsPosition, lsScale = "", lsX = "", lsY = "", lsZ = "";
		float lfScale = 1.0f;
		cVec3 lCollision = cVec3(0.5, 0.5, 0.5);


		
		lsModelName = lpElement->Attribute("ModelName");

		string lsType = cObjectManager::Get().ObtenerTipoObjeto(lsModelName);

		
		
		if (lsType != "")
		{
		  TiXmlElement *lpElement2;
			for (lpElement2 = lpElement->FirstChildElement("COLBOX"); lpElement2; lpElement2 = lpElement2->NextSiblingElement()) 
			{
				if (lpElement2->Attribute("X") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
					lsX = ((char*)lpElement2->Attribute("X"));

				if (lpElement2->Attribute("Y") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
					lsY = ((char*)lpElement2->Attribute("Y"));

				if (lpElement2->Attribute("Z") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
					lsZ = ((char*)lpElement2->Attribute("Z"));

				float lfX = (float)atof(lsX.c_str());
				float lfY = (float)atof(lsY.c_str());
				float lfZ = (float)atof(lsZ.c_str());

				lVec3.x = lfX;
				lVec3.y = lfY;
				lVec3.z = lfZ;
			
				
			}
		}

		//HACER EL array de shapes

		if (lsType == "Player")
		{
			//cPhysicsObject* lPhysicsObjectPtr = new cPhysicsPlayer(*lPhysicsObject);
			//mPhysicsPlayer.push_back(lPhysicsObjectPtr);
			cPhysicsObject* lPhysicsObjectPtr = new cPhysicsPlayer;
			lPhysicsObjectPtr->CreateBoxShape(lVec3);
			(*lPhysicsObjectPtr).SetTypeObject (lsType);
			(*lPhysicsObjectPtr).SetModelName(lsModelName);
			mPhysicsPlayer.push_back(lPhysicsObjectPtr);
		}
		else if (lsType == "Pista")
		{
			cPhysicsObject* lPhysicsObjectPtr = new cPhysicsPista;
			lPhysicsObjectPtr->CreateBoxShape(lVec3);
			(*lPhysicsObjectPtr).SetTypeObject (lsType);
			(*lPhysicsObjectPtr).SetModelName(lsModelName);
			mPhysicsPista.push_back(lPhysicsObjectPtr);
		}

	}


	
}


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

}

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
