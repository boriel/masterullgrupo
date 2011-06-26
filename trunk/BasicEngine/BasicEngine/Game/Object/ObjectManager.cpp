#include "ObjectManager.h"

#include <tinystr.h>
#include <tinyxml.h>
#include <Windows.h>
#include <vector>

#include "..\Scene\ModelManager.h"
#include "..\Scene\Model.h"
#include "ObjectPlayer.h"
#include "ObjectPista.h"
#include "ObjectVehicle.h"


#include "..\..\Physics\Objects\PhysicsPlayer.h"
#include "..\..\Physics\Objects\PhysicsPista.h"
#include "..\..\Physics\Objects\PhysicsVehicle.h"

#include "..\..\Graphics\Meshes\MeshManager.h"

bool cObjectManager::Init() 
{
	msFilename = (".\\Data\\" + std::string("Resources.xml"));

	mfPI = 3.14159f;
	mfScale = 1.0f; //Por defecto no se aplica escalado en las cargas a menos que se indique explícitamente

	//Leemos los Objects desde un XML
	LoadObjectsXml("Objects");  //leyendo los objetos sin fisica

	//Inicializando los recursos aqui
	for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex )
	{
		SetScale(mObjectPlayer[luiIndex]->GetScale());
		cModelManager::Get().LoadResource(mObjectPlayer[luiIndex]->GetModelName(), mObjectPlayer[luiIndex]->GetModelFile());
	}

	for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex ) 
	{
		cPhysicsPista* lpPhysicsPista = new cPhysicsPista;
		mObjectPista[luiIndex]->SetPtrPhysicsObject(lpPhysicsPista);
		SetScale(mObjectPista[luiIndex]->GetScale());
		cModelManager::Get().LoadResource(mObjectPista[luiIndex]->GetModelName(), mObjectPista[luiIndex]->GetModelFile());
	}
		
	for (unsigned luiIndex = 0; luiIndex < mObjectVehicle.size(); ++luiIndex )
	{
		SetScale(mObjectVehicle[luiIndex]->GetScale());
		cModelManager::Get().LoadResource(mObjectVehicle[luiIndex]->GetModelName(), mObjectVehicle[luiIndex]->GetModelFile());
	}

	for (unsigned luiIndex = 0; luiIndex < mObject.size(); ++luiIndex ) 
	{
		SetScale(mObject[luiIndex]->GetScale());
		cModelManager::Get().LoadResource(mObject[luiIndex]->GetModelName(), mObject[luiIndex]->GetModelFile());
	}

	//Creando la Física de los objetos  ( A LO MEJRO ALGO DE ESTO SE REPITA CON LA REUBICACION, MIRARLO! como que cargue dos veces la pista o algo asi Yorman OJO)
	for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex ) 
	{
		cPhysicsPlayer* lpPhysicsPlayer = new cPhysicsPlayer;
		LoadObjectsXmlCollision(mObjectPlayer[luiIndex]->GetModelName(), mObjectPlayer[luiIndex]->GetType(), lpPhysicsPlayer);
		lpPhysicsPlayer->Init(mObjectPlayer[luiIndex]->GetPosition(), mObjectPlayer[luiIndex]->GetRotacionInicial());
		mObjectPlayer[luiIndex]->SetPtrPhysicsObject(lpPhysicsPlayer);
	}
	
	for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex ) 
	{
		cPhysicsPista* lpPhysicsPista = new cPhysicsPista;

		CreandoFisica(mObjectPista[luiIndex], lpPhysicsPista);


		mObjectPista[luiIndex]->SetPtrPhysicsObject(lpPhysicsPista);

/*
		LoadObjectsXmlCollision(mObjectPista[luiIndex]->GetModelName(), mObjectPista[luiIndex]->GetType(), lpPhysicsPista);
		//lpPhysicsPista->Init(mObjectPista[luiIndex]->GetPosition(), mObjectPista[luiIndex]->GetRotacionInicial());
		lpPhysicsPista->Init(mObjectPista[luiIndex]->GetPosition());

		mObjectPista[luiIndex]->SetPtrPhysicsObject(lpPhysicsPista);

#ifdef _DEBUG
		cout << "------> Objeto : " << mObjectPista[luiIndex]->GetModelName() << endl;
#endif		

		//Pruebas no vale por ahora
		//No se si hay alguna forma mejro de pasar por esto, pero asi va 
			cResourceHandle lResourceHandle = cModelManager::Get().FindResourceA(mObjectPista[luiIndex]->GetModelName());
			cResource* lResource =  lResourceHandle.GetResource();
			cModel* lpModel = new cModel;
			lpModel = (cModel*)lResource;
			cModel::cObjectList lObjectList = lpModel->GetObjectList();
			for (int liIndex = 0; liIndex < lpModel->GetTamMeshList(); liIndex++)
			{
				//La verdad se podría hacer solo con el lObjectList que creo que para eso está. De este es el unico que puedo sacar el nombre del mesh
				cSubModel* lSubModel = lObjectList[liIndex];
				string lsMeshName = lSubModel->GetName();

#ifdef _DEBUG
				cout << "MeshName : " << lsMeshName << endl;
#endif
			}
*/		
	}
	
	for (unsigned luiIndex = 0; luiIndex < mObjectVehicle.size(); ++luiIndex ) 
	{
		cPhysicsVehicle* lpPhysicsVehicle = new cPhysicsVehicle;
		LoadObjectsXmlCollision(mObjectVehicle[luiIndex]->GetModelName(), mObjectVehicle[luiIndex]->GetType(), lpPhysicsVehicle);  //No hace nada por ahora
		//lpPhysicsVehicle->Init(mObjectPista[luiIndex]->GetPosition(), mObjectPista[luiIndex]->GetRotacionInicial());
		lpPhysicsVehicle->Init();

		mObjectVehicle[luiIndex]->SetPtrPhysicsObject(lpPhysicsVehicle);
	}

	//Objetos Generales con un box por ahora
	for (unsigned luiIndex = 0; luiIndex < mObject.size(); ++luiIndex ) 
	{
		cPhysicsObject* lpPhysicsObject = new cPhysicsObject;
		
		CreandoFisica(mObject[luiIndex], lpPhysicsObject);


		mObject[luiIndex]->SetPtrPhysicsObject(lpPhysicsObject);


//		//if (mObject[luiIndex]->GetModelName() == "Rampa")  //Pruebas con la rampa para ver como queda sacando vértices, hay cosas repetidas
//		//{


//			cPhysicsObject* lpPhysicsObject = new cPhysicsObject;
//
//			//No se si hay alguna forma mejro de pasar por esto, pero asi va 
//			cResourceHandle lResourceHandle = cModelManager::Get().FindResourceA(mObject[luiIndex]->GetModelName());
//			cResource* lResource =  lResourceHandle.GetResource();
//			cModel* lpModel = new cModel;
//			lpModel = (cModel*)lResource;
//			cModel::cObjectList lObjectList = lpModel->GetObjectList();
//
//
//			(*lpPhysicsObject).SetMass(0.0f); //ASIGNAR LA MASA DESDE XML, Y TAMBIEN PREGUNTAR SI TIENE FISICA O NO EL OBJETO?
//
//#ifdef _DEBUG
//		cout << "------> Objeto : " << mObject[luiIndex]->GetModelName() << endl;
//#endif		
//
//
//			
//
//			//Obtetemos todas las mesh del modelo
//			for (int liIndex = 0; liIndex < lpModel->GetTamMeshList(); liIndex++)
//			{
//				//La verdad se podría hacer solo con el lObjectList que creo que para eso está. De este es el unico que puedo sacar el nombre del mesh
//				cSubModel* lSubModel = lObjectList[liIndex];
//				string lsMeshName = lSubModel->GetName();
//
//				cout << "MeshName : " << lsMeshName << endl;
//
//				vector<string> lTokens;
//				Tokenize(lsMeshName, lTokens, "_");
//				string lsTipoShape = lTokens[0].c_str();
//
//				//Con este metodo obtenemos todos los puntos del vector
//				if (lsTipoShape == "Mesh")
//				{
//					cMesh* lpMesh = lpModel[liIndex].GetMesh(liIndex);
//					cVec3* lVec3 = lpMesh->mpVertexPositionBuffer;
//					btTransform lbtLocalTrans(btQuaternion (0,0,0,1), btVector3(mObject[luiIndex]->GetPosition().x,  mObject[luiIndex]->GetPosition().y, mObject[luiIndex]->GetPosition().z));
//					//lbtLocalTrans.setIdentity();
///*
//					btMatrix3x3 mat;
//					mat.setIdentity();
//					//btTransform bb = btTransform(mat);
//
//					
//					//mat.setEulerZYX(3.1416 / 2, 0, 0);
//					
//					//mat.setEulerYPR(3.1416 / 2, 0, 0);
//
//					lbtLocalTrans.setBasis(mat);
//*/					
//					
//
//					btConvexHullShape* lbtShape = new btConvexHullShape();
//					float lfScala = 1.0f;
//
//					for (int liCont = 0; liCont < lpMesh->muiNumVertex; liCont++)
//						lbtShape->addPoint( lfScala * btVector3(lVec3[liCont].x, lVec3[liCont].y, lVec3[liCont].z) );
//
//					btVector3 aabbMin(0,0,0), aabbMax(0,0,0);
//					//btTransform tmp = btTransform::getIdentity();
//					//tmp.inverse();
//					lbtShape->getAabb( btTransform::getIdentity(), aabbMin, aabbMax );
//					//lbtShape->getAabb( tmp, aabbMin, aabbMax );
//					btVector3 aabbExtents = aabbMax - aabbMin;  //No se usa para nada?
//					
//					btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
//					(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);
//					mObject[luiIndex]->SetPtrPhysicsObject(lpPhysicsObject);
//				}
//				else if (lsTipoShape == "Box")
//				{
//					btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(mObject[luiIndex]->GetPosition().x,  mObject[luiIndex]->GetPosition().y, mObject[luiIndex]->GetPosition().z));
//					btCollisionShape* lbtShape = new btBoxShape(btVector3(1, 1, 1));  
//					btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
//					(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);
//					mObject[luiIndex]->SetPtrPhysicsObject(lpPhysicsObject);
//				}
//				else  //del xml provisional
//				{
//					cPhysicsObject* lpPhysicsObject = new cPhysicsObject;
//					LoadObjectsXmlCollision(mObject[luiIndex]->GetModelName(), mObject[luiIndex]->GetType(), lpPhysicsObject);
//					lpPhysicsObject->Init(mObject[luiIndex]->GetPosition(), mObject[luiIndex]->GetRotacionInicial());
//
//					mObject[luiIndex]->SetPtrPhysicsObject(lpPhysicsObject);
//				}
//
//
//			}
//			
//
//			//lM->
//
//
//			//cModel::cObjectList lOL = lM->GetObjectList();
//
//
//			
//			//lOL[0]->GetMeshId(idObject)
//			//unsigned int luiID = lOL[0]->  ->mMeshHandles[0].GetID();
//
//
//
//			//lM->GetBounding();
//			/*
//			btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(mObject[luiIndex]->GetPosition().x,  mObject[luiIndex]->GetPosition().y, mObject[luiIndex]->GetPosition().z));
//			btCollisionShape* lbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  
//			btRigidBody* lpbtRirigBody = (*lpPhysicsPista).LocalCreateRigidBody((*lpPhysicsPista).GetMass(), lbtLocalTrans, lbtShape);
//			(*lpPhysicsPista).SetRigidBody(lpbtRirigBody);
//			*/
//
//
//			
//
//	  //}
//		//else if (mObject[luiIndex]->GetModelName() == "Rectangulo")  // pruebas con esto
//		//{
//		//	cPhysicsObject* lpPhysicsObject = new cPhysicsObject;
//
//		//		(*lpPhysicsObject).SetMass(1.0f);
//		//		//cVec3 lPosition = GetPosition(lsType, lsModelName);
//
//		//		cResourceHandle lRH = cModelManager::Get().FindResourceA("Rectangulo");
//		//		cResource* lR =  lRH.GetResource();
//		//		cModel* lpModel = new cModel;
//		//		lpModel = (cModel*)lR;
//
//		//		//tBounding lBounding = lpModel->ProcessBounding();
//		//		
//
//
//		//		
//		//		//btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(mObject[luiIndex]->GetPosition().x,  mObject[luiIndex]->GetPosition().y+2, mObject[luiIndex]->GetPosition().z));
//		//		//btCollisionShape* lbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  		
//		//	
//		//		//btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
//		//		//(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);
//
//
//		//		mObject[luiIndex]->SetPtrPhysicsObject(lpPhysicsObject);
//	
//		//}
//	//	else
//	//	{
//	//		cPhysicsObject* lpPhysicsObject = new cPhysicsObject;
//	//		LoadObjectsXmlCollision(mObject[luiIndex]->GetModelName(), mObject[luiIndex]->GetType(), lpPhysicsObject);
//	//		lpPhysicsObject->Init(mObject[luiIndex]->GetPosition(), mObject[luiIndex]->GetRotacionInicial());
//
//	//		mObject[luiIndex]->SetPtrPhysicsObject(lpPhysicsObject);
//	//	}
	}

	return true;
}

void cObjectManager::CreandoFisica(cObject* lpObject, cPhysicsObject* lpPhysicsObject)
{

			//No se si hay alguna forma mejro de pasar por esto, pero asi va 
	cResourceHandle lResourceHandle = cModelManager::Get().FindResourceA(lpObject->GetModelName());
	cResource* lResource =  lResourceHandle.GetResource();
	cModel* lpModel = new cModel;
	lpModel = (cModel*)lResource;
	cModel::cObjectList lObjectList = lpModel->GetObjectList();


	(*lpPhysicsObject).SetMass(lpObject->GetMass()); //ASIGNAR LA MASA DESDE XML, Y TAMBIEN PREGUNTAR SI TIENE FISICA O NO EL OBJETO?

#ifdef _DEBUG
		cout << "cObjectManager::CreandoFisica ------> Objeto : " << lpObject->GetModelName() << endl;
#endif		


	//Obtetemos todas las mesh del modelo
	for (int liIndex = 0; liIndex < lpModel->GetTamMeshList(); liIndex++)
	{
		//La verdad se podría hacer solo con el lObjectList que creo que para eso está. De este es el unico que puedo sacar el nombre del mesh
		cSubModel* lSubModel = lObjectList[liIndex];
		string lsMeshName = lSubModel->GetName();

#ifdef _DEBUG
		cout << "MeshName : " << lsMeshName << endl;
#endif		

		vector<string> lTokens;
		Tokenize(lsMeshName, lTokens, "_");
		string lsTipoShape = lTokens[0].c_str();

		//Con este metodo obtenemos todos los puntos del vector
		if (lsTipoShape == "Mesh")
		{
			cResource* lResourceMesh = lSubModel->GetResource(0);
			cMesh* lpMesh = new cMesh;
			lpMesh = (cMesh*)lResourceMesh;

			//cMesh* lpMesh = lpModel[liIndex].GetMesh(liIndex);


			//cResourceHandle cRH = lpModel[liIndex].GetResourceHandle(liIndex);

			//cMesh* lpMesh = lpModel[liIndex].GetMesh(liIndex);
			cVec3* lVec3 = lpMesh->mpVertexPositionBuffer;  //los vertices o puntos de la malla
			btTransform lbtLocalTrans(btQuaternion (0,0,0,1), btVector3(lpObject->GetPosition().x,  lpObject->GetPosition().y, lpObject->GetPosition().z));
			//lbtLocalTrans.setIdentity();

			btConvexHullShape* lbtShape = new btConvexHullShape();

			float lfScala = 1.0f;//0.07f;

			for (int liCont = 0; liCont < (int) lpMesh->muiNumVertex; liCont++)
				lbtShape->addPoint( lfScala * btVector3(lVec3[liCont].x, lVec3[liCont].y, lVec3[liCont].z) );

			btVector3 aabbMin(0,0,0), aabbMax(0,0,0);
			lbtShape->getAabb( btTransform::getIdentity(), aabbMin, aabbMax );
			btVector3 aabbExtents = aabbMax - aabbMin;  //No se usa para nada?
			
			//----Pruebas de rotacion
			//lbtLocalTrans.setRotation(btQuaternion(btVector3(1,0,0), btRadians(-90)));  
			///----- end pruebas


			btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
			(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);
			//lpObject->SetPtrPhysicsObject(lpPhysicsObject);
		}
		
		else if (lsTipoShape == "Box")
		{
			//if (lsMeshName == "Box_Help_SueloMesa")
			//{
			cResource* lResourceMesh = lSubModel->GetResource(0);
			cMesh* lpMesh = new cMesh;
			lpMesh = (cMesh*)lResourceMesh;
			
			tBoundingMesh ltBoundingMesh = lpMesh->GetBoundingMesh();

			btVector3 lvbtObjectPosition = btVector3 (lpObject->GetPosition().x,  lpObject->GetPosition().y, lpObject->GetPosition().z);
			btVector3 lvbtCenterMesh = btVector3 (btVector3(ltBoundingMesh.mfCentroX,  ltBoundingMesh.mfCentroY, ltBoundingMesh.mfCentroZ));
			btVector3 lvbtposFinal = lvbtObjectPosition * lvbtCenterMesh;
			//btTransform lbtLocalTrans (btQuaternion (0,0,0,1), lvbtposFinal );
			btTransform lbtLocalTrans (btQuaternion (0,0,0,1), lvbtCenterMesh );
			lbtLocalTrans.setRotation(btQuaternion(btVector3(1,0,0), btRadians(-90))); //Rotando
			btCollisionShape* lbtShape = new btBoxShape(btVector3(ltBoundingMesh.mfAnchoX, ltBoundingMesh.mfAnchoY, ltBoundingMesh.mfAnchoZ));  
			btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
			(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);  
			 
			btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
			//lpDynamicsWorld->getCollisionObjectArray();

			/*
			btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lpObject->GetPosition().x,  lpObject->GetPosition().y, lpObject->GetPosition().z));
			btCollisionShape* lbtShape = new btBoxShape(btVector3(1, 1, 1));  
			btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
			(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);
			//lpObject->SetPtrPhysicsObject(lpPhysicsObject);
			*/
			//}
		}
		
		else if (lsTipoShape == "Sphere")
		{
			cResource* lResourceMesh = lSubModel->GetResource(0);
			cMesh* lpMesh = new cMesh;
			lpMesh = (cMesh*)lResourceMesh;
			
			tBoundingMesh ltBoundingMesh = lpMesh->GetBoundingMesh();
			btVector3 lvbtCenterMesh = btVector3 (btVector3(ltBoundingMesh.mfCentroX,  ltBoundingMesh.mfCentroY, ltBoundingMesh.mfCentroZ));
			

			btTransform lbtLocalTrans (btQuaternion (0,0,0,1), lvbtCenterMesh);
			btCollisionShape* lbtShape = new btSphereShape(ltBoundingMesh.mfRadius);  
			btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
			(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);

			/*
			btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lpObject->GetPosition().x,  lpObject->GetPosition().y, lpObject->GetPosition().z));
			btCollisionShape* lbtShape = new btSphereShape(1);  
			btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
			(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);
			//lpObject->SetPtrPhysicsObject(lpPhysicsObject);
			*/
		}
		else  // general con un box de 1x1x1 para el que no tenga nombre delante, auqne desaperecera
		{
			btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lpObject->GetPosition().x,  lpObject->GetPosition().y, lpObject->GetPosition().z));
			btCollisionShape* lbtShape = new btBoxShape(btVector3(1, 1, 1));  
			btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
			(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);
			//lpObject->SetPtrPhysicsObject(lpPhysicsObject);
		}
		/*
		else  //del xml provisional
		{
			//cPhysicsObject* lpPhysicsObject = new cPhysicsObject;
			LoadObjectsXmlCollision(lpObject->GetModelName(), lpObject->GetType(), lpPhysicsObject);
			lpPhysicsObject->Init(lpObject->GetPosition(), lpObject->GetRotacionInicial());

			//lpObject->SetPtrPhysicsObject(lpPhysicsObject);
		}
		*/

	}


}


void cObjectManager::Deinit()
{
		//Inicializando los recursos aqui
	for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex ) 
		mObjectPlayer[luiIndex]->Deinit();

	for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex ) 
		mObjectPista[luiIndex]->Deinit();

	for (unsigned luiIndex = 0; luiIndex < mObject.size(); ++luiIndex ) 
		mObject[luiIndex]->Deinit();
	
	for (unsigned luiIndex = 0; luiIndex < mObjectVehicle.size(); ++luiIndex ) 
		mObjectVehicle[luiIndex]->Deinit();

	//Eliminar la memoria, pendiente por hacer
}

void cObjectManager::Update(float lfTimestep)
{
	//Actualizando el Player
	for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex )
		mObjectPlayer[luiIndex]->Update(lfTimestep);
	
	//Actualizando la pista
	for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex )
		if (mObjectPista[luiIndex]->GetMass() != 0)
			mObjectPista[luiIndex]->Update(lfTimestep);
	

	for (unsigned luiIndex = 0; luiIndex < mObjectVehicle.size(); ++luiIndex )
	{
		mObjectVehicle[luiIndex]->Update(lfTimestep);
#if _DEBUG
		((cPhysicsVehicle*)mObjectVehicle[luiIndex]->GetPtrPhysicsObject())->MostrarInfo();
#endif

	}

	//Actualizando los objetos
	for (unsigned luiIndex = 0; luiIndex < mObject.size(); ++luiIndex )
		//if (mObject[luiIndex]->GetMass() != 0)
			mObject[luiIndex]->Update(lfTimestep);
}

void cObjectManager::Render()
{
	//TODO: Por ahora se dibuja todo, aunque no se vea por la camara
	for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex )
		mObjectPista[luiIndex]->Render();

	for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex )
		mObjectPlayer[luiIndex]->Render();

	for (unsigned luiIndex = 0; luiIndex < mObject.size(); ++luiIndex )
		mObject[luiIndex]->Render();

	for (unsigned luiIndex = 0; luiIndex < mObjectVehicle.size(); ++luiIndex )
		mObjectVehicle[luiIndex]->Render();
}

//Leemos todos los recursos desde un xml
bool cObjectManager::LoadObjectsXml(std::string lsResource)
{
	TiXmlDocument lDoc;

	lDoc.LoadFile ((char*)msFilename.c_str());
	if (!lDoc.LoadFile())
	{
		OutputDebugString ("[cObjectManager] XML Load: FAILED\n");
	}
	
	TiXmlElement *lpElementResources;
	lpElementResources = lDoc.FirstChildElement ("Resources");
	
	if (lsResource == "Objects")
	{
		TiXmlElement *lpElement;
		lpElement =  lpElementResources->FirstChildElement (lsResource); 

		for (lpElement = lpElement->FirstChildElement("Object"); lpElement; lpElement = lpElement->NextSiblingElement()) 
		{
			std::string lsType, lsModelFile, lsModelName, lsPosition, lsScale = "", lsRotation = "", lsAngle = "", lsMass = "";
			float lfScale = 1.0f, lfMass = 0.0f;
			cVec3 lCollision = cVec3(0.5, 0.5, 0.5);
			cQuaternion lQuatRot = cQuaternion(1,0,0,0);
			
			if (lpElement->Attribute("Type") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
				lsType = ((char*)lpElement->Attribute("Type"));

			if (lpElement->Attribute("ModelName") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
				lsModelName = ((char*)lpElement->Attribute("ModelName"));

			if (lpElement->Attribute("ModelFile") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
				lsModelFile = ((char*)lpElement->Attribute("ModelFile"));

			if (lpElement->Attribute("Position") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
				lsPosition = ((char*)lpElement->Attribute("Position"));

			if (lpElement->Attribute("Scale") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
				lsScale = ((char*)lpElement->Attribute("Scale"));

			if (lpElement->Attribute("Rotation") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
				lsRotation = ((char*)lpElement->Attribute("Rotation"));

			if (lpElement->Attribute("Angle") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
				lsAngle = ((char*)lpElement->Attribute("Angle"));

			if (lpElement->Attribute("Mass") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
				lsMass = ((char*)lpElement->Attribute("Mass"));

			cObject* lObject = new cObject;

			//TODO: para encapsular esto entre llaves
			{ 
			vector<string> lTokens;
			Tokenize(lsPosition, lTokens, ",");

			double ldX = strtod(lTokens[0].c_str(), NULL);
			double ldY = strtod(lTokens[1].c_str(), NULL);
			double ldZ = strtod(lTokens[2].c_str(), NULL);

			cVec3 lPosition((float)ldX, (float)ldY, (float)ldZ);
			(*lObject).SetPosition(lPosition);

			}
			
			//pansando algunos formatos a lo que necesitamos
			if (lsScale != "") 
				lfScale = (float)atof(lsScale.c_str());

			if (lsMass != "") 
				lfMass = (float)atof(lsMass.c_str());

			if ((lsRotation != "") && (lsAngle != ""))
			{
				vector<string> lTokens;
				Tokenize(lsRotation, lTokens, ",");

				double ldX = strtod(lTokens[0].c_str(), NULL);
				double ldY = strtod(lTokens[1].c_str(), NULL);
				double ldZ = strtod(lTokens[2].c_str(), NULL);
	
				float lfAngle = (float)atof(lsAngle.c_str());
				//lQuatRot = cQuaternion((float)ldX, (float)ldY, (float)ldZ, lfAngle * 2 *  (float) PI / (float) 360.0);
				cQuaternion lQuatRot((float)ldX, (float)ldY, (float)ldZ, lfAngle * (float) mfPI / (float) 180.0);
				(*lObject).SetRotacionInicial(lQuatRot);
			}	

			(*lObject).SetType (lsType);
			(*lObject).SetModelName(lsModelName);
			(*lObject).SetModelFile(lsModelFile);	
			(*lObject).SetScale(lfScale);
			(*lObject).SetMass(lfMass);

			//Lo iba a poner en una funcion, pero si esto crece en parametros como la pista pasarle los limites, el parametro descompensa. Incluye Init en los constructores
			//Creamos tambien el objeto Físico
			if (lsType == "Player")
			{
				cObject* lObjectPtr = new cObjectPlayer(*lObject);
				mObjectPlayer.push_back(lObjectPtr);
			}
			else if (lsType == "Pista")
			{
				cObject* lObjectPtr = new cObjectPista(*lObject);
				mObjectPista.push_back(lObjectPtr);
			}
			else if (lsType == "Vehicle")
			{
				cObject* lObjectPtr = new cObjectVehicle(*lObject);
				mObjectVehicle.push_back(lObjectPtr);
			}
			else if (lsType != "") //General
			{
				cObject* lObjectPtr = new cObject(*lObject);
				mObject.push_back(lObjectPtr);
			}
			
			delete lObject;  //ya no nos hace falta, porque copiamos los parámetros y en el último caso lo duplicamos
		}
	}
	return true;
}

//para hacer un split de un string
void cObjectManager::Tokenize(const string& lsStr, vector<string>& lvTokens,  const string& lsDelimiters)
{
    // Skip delimiters at beginning.
    string::size_type lLastPos = lsStr.find_first_not_of(lsDelimiters, 0);

    // Find first "non-delimiter".
    string::size_type lPos  = lsStr.find_first_of(lsDelimiters, lLastPos);

    while (string::npos != lPos || string::npos != lLastPos)
    {
        // Found a token, add it to the vector.
        lvTokens.push_back(lsStr.substr(lLastPos, lPos - lLastPos));

        // Skip delimiters.  Note the "not_of"
        lLastPos = lsStr.find_first_not_of(lsDelimiters, lPos);

        // Find next "non-delimiter"
        lPos = lsStr.find_first_of(lsDelimiters, lLastPos);
    }
}

cVec3 cObjectManager::GetPosition(const string lsType, const string lsModelName)
{
	cVec3 lPosition(0,0,0);

	if (lsType == "Pista")
	{
		for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex ) 
			if (mObjectPista[luiIndex]->GetModelName() == lsModelName)
				return mObjectPista[luiIndex]->GetPosition();
	}
	else if (lsType == "Player")
	{
		for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex ) 
			if (mObjectPlayer[luiIndex]->GetModelName() == lsModelName)
				return mObjectPlayer[luiIndex]->GetPosition();
	}
	else  //general
	{
		for (unsigned luiIndex = 0; luiIndex < mObject.size(); ++luiIndex ) 
			if (mObject[luiIndex]->GetModelName() == lsModelName)
				return mObject[luiIndex]->GetPosition();

	}

	return lPosition;
}

cQuaternion cObjectManager::GetRotacionInicial (const string lsType, const string lsModelName)
{
	cQuaternion lRotInicial (0,0,0,0);
	if (lsType == "Pista")
	{
		for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex ) 
			if (mObjectPista[luiIndex]->GetModelName() == lsModelName)
				return mObjectPista[luiIndex]->GetRotacionInicial();
	}
	else if (lsType == "Player")
	{
		for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex ) 
			if (mObjectPlayer[luiIndex]->GetModelName() == lsModelName)
				return mObjectPlayer[luiIndex]->GetRotacionInicial();
	}

	return lRotInicial;
}

cObject *cObjectManager::GetObject(const string lsType, const string lsModelName) 
{	//Devuelve puntero al Object solicitado
	if (lsType == "Pista")
	{
		for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex ) 
			if (mObjectPista[luiIndex]->GetModelName() == lsModelName)
				return mObjectPista[luiIndex];
	}
	else if (lsType == "Player")
	{
		for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex ) 
			if (mObjectPlayer[luiIndex]->GetModelName() == lsModelName)
				return mObjectPlayer[luiIndex];
	}
	else if (lsType == "Vehicle")
	{
		for (unsigned luiIndex = 0; luiIndex < mObjectVehicle.size(); ++luiIndex ) 
			if (mObjectVehicle[luiIndex]->GetModelName() == lsModelName)
				return mObjectVehicle[luiIndex];
	}

	return NULL;
}


void cObjectManager::LoadObjectsXmlCollision(const std::string lsModelNameBuscar, const std::string lsType,  cPhysicsObject* lpPhysicsObject)
{
	TiXmlDocument lDoc;

	cVec3 lVec3 (-1,-1,-1);

	msFilename = msFilename = (".\\Data\\" + std::string("Resources.xml"));

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

		//string lsType = cObjectManager::Get().ObtenerTipoObjeto(lsModelName);
		//if (lsType != "")
		if (lsModelName == lsModelNameBuscar)
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

			//TODO: Yorman: HACER EL array de shapes
			if (lsType == "Player")
			{
				cPhysicsPlayer* lpPhysicsPlayer = (cPhysicsPlayer*)lpPhysicsObject;
				//(*lpPhysicsPlayer).CreateBoxShape(lVec3);

				(*lpPhysicsPlayer).SetMass(800.0f);
				cVec3 lPosition = GetPosition(lsType, lsModelName);

				btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lPosition.x, lPosition.y, lPosition.z));
				//lbtLocalTrans.setIdentity();
				btCollisionShape* lbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  
			
				btRigidBody* lpbtRirigBody = (*lpPhysicsPlayer).LocalCreateRigidBody((*lpPhysicsPlayer).GetMass(), lbtLocalTrans, lbtShape);
				(*lpPhysicsPlayer).SetRigidBody(lpbtRirigBody);

				/*
				cPhysicsObject* lPhysicsObjectPtr = new cPhysicsPlayer;
				lPhysicsObjectPtr->CreateBoxShape(lVec3);
				(*lPhysicsObjectPtr).SetTypeObject (lsType);
				(*lPhysicsObjectPtr).SetModelName(lsModelName);
				//mPhysicsPlayer.push_back(lPhysicsObjectPtr);
				*/
			}
			else if (lsType == "Pista")
			{
				cPhysicsPista* lpPhysicsPista = (cPhysicsPista*)lpPhysicsObject;

				/*
				cVec3 lPosition = GetPosition(lsType, lsModelName);

				lpPhysicsPista->Init(lPosition);
				*/
				
				//lpPhysicsPlayer->CreateBoxShape(lVec3);
				//(*lpPhysicsPista).CreateBoxShape(lVec3);
				(*lpPhysicsPista).SetMass(0.0f);
				cVec3 lPosition = GetPosition(lsType, lsModelName);

				btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lPosition.x, lPosition.y, lPosition.z));
				//lbtLocalTrans.setIdentity();
				btCollisionShape* lbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  
			
				btRigidBody* lpbtRirigBody = (*lpPhysicsPista).LocalCreateRigidBody((*lpPhysicsPista).GetMass(), lbtLocalTrans, lbtShape);
				(*lpPhysicsPista).SetRigidBody(lpbtRirigBody);

				//(*lpPhysicsPista).SetTypeObject ("borrar el tipo de esta clase ya no hace falta");
				
			}
			else if (lsType == "Vehicle") 		//Cargamos la fisica del vehicle, no implmento desde el xml todavía
			{
				cPhysicsVehicle* lpPhysicsVehicle = (cPhysicsVehicle*)lpPhysicsObject;
			}
			else if (lsType == "Rampa")  //Pruebas por ahora
			{
				/*
				(*lpPhysicsObject).SetMass(0.0f);
				cVec3 lPosition = GetPosition(lsType, lsModelName);

				btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lPosition.x, lPosition.y, lPosition.z));
				//lbtLocalTrans.setIdentity();
				btCollisionShape* lbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  
			
				btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
				(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);
				*/

				(*lpPhysicsObject).SetMass(0.0f);
				cVec3 lPosition = GetPosition(lsType, lsModelName);

				btTransform lbtLocalTrans (btQuaternion (0,1,0,1), btVector3(lPosition.x, lPosition.y, lPosition.z));
				//btCollisionShape* lbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  
				
				btConvexHullShape* lbtShape = new btConvexHullShape();

				float lfScala = 2.0f;
				
				lbtShape->addPoint( lfScala * btVector3(0,0,0) );
				lbtShape->addPoint( lfScala * btVector3(0,0,1) );
				lbtShape->addPoint( lfScala * btVector3(0,1,1) );
				lbtShape->addPoint( lfScala * btVector3(0,1,0) );
				lbtShape->addPoint( lfScala * btVector3(0,0,0) );
				
				lbtShape->addPoint( lfScala * btVector3(0,0,0) );
				lbtShape->addPoint( lfScala * btVector3(1,0,0) );
				lbtShape->addPoint( lfScala * btVector3(1,0,1) );
				lbtShape->addPoint( lfScala * btVector3(0,0,1) );
				lbtShape->addPoint( lfScala * btVector3(0,0,0) );

				lbtShape->addPoint( lfScala * btVector3(0,1,0) );
				lbtShape->addPoint( lfScala * btVector3(1,0,0) );
				lbtShape->addPoint( lfScala * btVector3(1,0,1) );
				lbtShape->addPoint( lfScala * btVector3(0,1,1) );
				lbtShape->addPoint( lfScala * btVector3(0,1,0) );

				btVector3 aabbMin(0,0,0), aabbMax(0,0,0);
				lbtShape->getAabb( btTransform::getIdentity(), aabbMin, aabbMax );

				btVector3 aabbExtents = aabbMax - aabbMin;

				btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
				(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);

				/*
				(*lpPhysicsObject).SetMass(1.0f);
				cVec3 lPosition = GetPosition(lsType, lsModelName);

				btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lPosition.x, lPosition.y, lPosition.z));
				//lbtLocalTrans.setIdentity();
				//btCollisionShape* lbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  
				
				
				btVector3 aabbMin(-1000,-1000,-1000), aabbMax(1000,1000,1000);
				bool useQuantizedAabbCompression = true;
				
				int totalTriangles = 1682, NUM_VERTS_X = 30, NUM_VERTS_Y = 30;
				const int totalVerts = NUM_VERTS_X*NUM_VERTS_Y;
				const float TRIANGLE_SIZE=8.f;
				int indexStride = 3*sizeof(int);
				int* gIndices = new int[totalTriangles*3];
				static btVector3*	gVertices = new btVector3[totalVerts];
				int vertStride = sizeof(btVector3);

				int index=0;
				for (int i=0;i < NUM_VERTS_X-1;i++)
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

				float offset = 0.f;
				static float waveheight = 5.f;

				for (int i=0;i<NUM_VERTS_X;i++)
					{
						for (int j=0;j<NUM_VERTS_Y;j++)
						{
							gVertices[i+j*NUM_VERTS_X].setValue((i-NUM_VERTS_X*0.5f)*TRIANGLE_SIZE,
								//0.f,
								waveheight*sinf((float)i+offset)*cosf((float)j+offset),
								(j-NUM_VERTS_Y*0.5f)*TRIANGLE_SIZE);
						}
					}

				//btTriangleIndexVertexArray* m_indexVertexArrays = new btTriangleIndexVertexArray(totalTriangles,	gIndices,	indexStride, totalVerts,(btScalar*) &gVertices[0].x(),vertStride);
				btTriangleIndexVertexArray* m_indexVertexArrays = new btTriangleIndexVertexArray(totalTriangles,	gIndices,	indexStride, 900,(btScalar*) &gVertices[0].x(),vertStride);

				btCollisionShape* lbtTrimeshShape  = new btBvhTriangleMeshShape(m_indexVertexArrays, useQuantizedAabbCompression, aabbMin, aabbMax);
			
				btConvexHullShape

				btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtTrimeshShape);
				(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);
				*/
			}
			else if (lsType != "") //general
			{
				//cPhysicsObject* lpPhysicsObject = (cPhysicsObject*)lpPhysicsObject;
				//lpPhysicsObject->CreateBoxShape(lVec3);

				(*lpPhysicsObject).SetMass(1.0f);
				cVec3 lPosition = GetPosition(lsType, lsModelName);

				btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lPosition.x, lPosition.y, lPosition.z));
				//lbtLocalTrans.setIdentity();
				btCollisionShape* lbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  		
			
				btRigidBody* lpbtRirigBody = (*lpPhysicsObject).LocalCreateRigidBody((*lpPhysicsObject).GetMass(), lbtLocalTrans, lbtShape);
				(*lpPhysicsObject).SetRigidBody(lpbtRirigBody);
			}
		}
	}
}
