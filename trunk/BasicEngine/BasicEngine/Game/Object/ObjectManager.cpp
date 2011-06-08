#include "ObjectManager.h"

#include <tinystr.h>
#include <tinyxml.h>
#include <Windows.h>

#include "..\Scene\ModelManager.h"
#include "ObjectPlayer.h"
#include "ObjectPista.h"
#include "ObjectVehicle.h"

#include "..\..\Physics\Objects\PhysicsPlayer.h"
#include "..\..\Physics\Objects\PhysicsPista.h"
#include "..\..\Physics\Objects\PhysicsVehicle.h"


bool cObjectManager::Init() 
{
	msFilename = (".\\Data\\" + std::string("Resources.xml"));

	mfPI = 3.14159f;

	//Lemeos desde un xml
	LoadObjectsXml("Objects");  //leyendo los objetos sin fisica
	//LoadObjectsXml("ObjectsCollision");  //Poniendo las collisiones


	//Creando la Física de los objetos
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
		LoadObjectsXmlCollision(mObjectPista[luiIndex]->GetModelName(), mObjectPista[luiIndex]->GetType(), lpPhysicsPista);
		lpPhysicsPista->Init(mObjectPista[luiIndex]->GetPosition(), mObjectPista[luiIndex]->GetRotacionInicial());

		mObjectPista[luiIndex]->SetPtrPhysicsObject(lpPhysicsPista);
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
		LoadObjectsXmlCollision(mObject[luiIndex]->GetModelName(), mObject[luiIndex]->GetType(), lpPhysicsObject);
		lpPhysicsObject->Init(mObject[luiIndex]->GetPosition(), mObject[luiIndex]->GetRotacionInicial());

		mObject[luiIndex]->SetPtrPhysicsObject(lpPhysicsObject);
	}



	//Inicializando los recursos aqui
	for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex ) 
		cModelManager::Get().LoadResource(mObjectPlayer[luiIndex]->GetModelName(), mObjectPlayer[luiIndex]->GetModelFile());

	for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex ) 
		cModelManager::Get().LoadResource(mObjectPista[luiIndex]->GetModelName(), mObjectPista[luiIndex]->GetModelFile());
		
	for (unsigned luiIndex = 0; luiIndex < mObjectVehicle.size(); ++luiIndex ) 
		cModelManager::Get().LoadResource(mObjectVehicle[luiIndex]->GetModelName(), mObjectVehicle[luiIndex]->GetModelFile());

	for (unsigned luiIndex = 0; luiIndex < mObject.size(); ++luiIndex ) 
		cModelManager::Get().LoadResource(mObject[luiIndex]->GetModelName(), mObject[luiIndex]->GetModelFile());

	return true;
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
		mObjectPista[luiIndex]->Update(lfTimestep);


	for (unsigned luiIndex = 0; luiIndex < mObjectVehicle.size(); ++luiIndex )
		mObjectVehicle[luiIndex]->Update(lfTimestep);

	//Actualizando los objetos
	for (unsigned luiIndex = 0; luiIndex < mObject.size(); ++luiIndex )
		mObject[luiIndex]->Update(lfTimestep);


}

//void cObjectManager::Render(cMatrix &lWorld)
void cObjectManager::Render()
{
	//TODO: Por ahora todos, hay que cambiarlo, peor lo dibujamos todo, auqnue no se vea por la camara
	for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex )
		mObjectPista[luiIndex]->Render();

	for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex )
		mObjectPlayer[luiIndex]->Render();

	for (unsigned luiIndex = 0; luiIndex < mObject.size(); ++luiIndex )
		mObject[luiIndex]->Render();

	for (unsigned luiIndex = 0; luiIndex < mObjectVehicle.size(); ++luiIndex )
		mObjectVehicle[luiIndex]->Render();
}

//Leemeos todos los recursos desde un xml
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
			std::string lsType, lsModelFile, lsModelName, lsPosition, lsScale = "", lsRotation = "", lsAngle = "";
			float lfScale = 1.0f;
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
			{
				lfScale = (float)atof(lsScale.c_str());
			}
			

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
void cObjectManager::Tokenize(const string& str, vector<string>& tokens,  const string& delimiters)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));

        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);

        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
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
		}

		//TODO: Yorman: HACER EL array de shapes

		if (lsType == "Player")
		{
			cPhysicsPlayer* lpPhysicsPlayer = (cPhysicsPlayer*)lpPhysicsObject;

			//lpPhysicsPlayer->CreateBoxShape(lVec3);
			(*lpPhysicsPlayer).CreateBoxShape(lVec3);
			//(*lpPhysicsPlayer).SetTypeObject ("borrar el tipo de esta clase");

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

			//lpPhysicsPlayer->CreateBoxShape(lVec3);
			(*lpPhysicsPista).CreateBoxShape(lVec3);
			//(*lpPhysicsPista).SetTypeObject ("borrar el tipo de esta clase ya no hace falta");
		}
		else if (lsType == "Vehicle") 		//Cargamos la fisica del vehicle, no implmento desde el xml todavía
		{
			cPhysicsVehicle* lpPhysicsVehicle = (cPhysicsVehicle*)lpPhysicsObject;
		}
		else if (lsType != "") //general
		{
			//cPhysicsObject* lpPhysicsObject = (cPhysicsObject*)lpPhysicsObject;
			lpPhysicsObject->CreateBoxShape(lVec3);
			
		}



	}


	
}
