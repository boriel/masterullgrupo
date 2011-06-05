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

	mfPI = 3.14159;


	//Lemeos desde un xml
	LoadObjectsXml("Objects");  //leyendo los objetos sin fisica
	//LoadObjectsXml("ObjectsCollision");  //Poniendo las collisiones




/*
	//Creando la Física de los objetos
	for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex ) 
	{
		//lo saco del xml y creamos los shapes sobre la marcha
		cVec3 lVec3 (LoadObjectsXmlCollision(mObjectPlayer[luiIndex]->GetModelName()));
		cPhysicsObject *lpObjectPlayer = ((cObjectPlayer*)mObjectPlayer[luiIndex])->GetPtrPhysicsObject();
		(*lpObjectPlayer).CreateBoxShape(lVec3);
		((cObjectPlayer*)mObjectPlayer[luiIndex])->InitPhysics();  //Aqui tambien se podría hacer la llamada con el puntero, 
		//((cPhysicsPlayer*)lpObjectPlayer)->Init(mObjectPlayer[luiIndex]->GetPosition(), mObjectPlayer[luiIndex]->GetRotacionInicial());

	}
	
	for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex ) 
	{
		cVec3 lVec3 (LoadObjectsXmlCollision(mObjectPista[luiIndex]->GetModelName()));
		cPhysicsObject *lpObjectPista = ((cObjectPista*)mObjectPista[luiIndex])->GetPtrPhysicsObject();
		(*lpObjectPista).CreateBoxShape(lVec3);
		((cObjectPista*)mObjectPista[luiIndex])->InitPhysics();
		//((cPhysicsPista*)lpObjectPista)->Init(mObjectPista[luiIndex]->GetPosition(), mObjectPlayer[luiIndex]->GetRotacionInicial());
	}

	//NO IMPLEMENTADO DEL TODO LOS OBJECTS GENÉRICOS
	for (unsigned luiIndex = 0; luiIndex < mObject.size(); ++luiIndex ) 
	{
		cVec3 lVec3 (LoadObjectsXmlCollision(mObject[luiIndex]->GetModelName()));
		cPhysicsObject *lpObject = ((cObject*)mObject[luiIndex])->GetPtrPhysicsObject();
		(*lpObject).CreateBoxShape(lVec3);
		((cObject*)mObject[luiIndex])->InitPhysics();
		//((cPhysicsObject*)lpObject)-> Init(); //
	}
	
*/

/*
	//Creamos a mano	
	cObject* lObject = new cObject;
	cObject* lObjectPtr = new cObjectVehicle(*lObject);
	mObjectVehicle.push_back(lObjectPtr);

	//Iniciamos a mano
	((cObjectVehicle*)mObjectVehicle[0])->InitPhysics();

*/

	//Inicializando los recursos aqui
	for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex ) 
		cModelManager::Get().LoadResource(mObjectPlayer[luiIndex]->GetModelName(), mObjectPlayer[luiIndex]->GetModelFile());

	for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex ) 
		cModelManager::Get().LoadResource(mObjectPista[luiIndex]->GetModelName(), mObjectPista[luiIndex]->GetModelFile());

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


}


//void cObjectManager::Render(cMatrix &lWorld)
void cObjectManager::Render()
{
	//Por ahora todos, hay que cambiarlo, peor lo dibujamos todo, auqnue no se vea por la camara

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
		OutputDebugString ("XML Load: FAILED\n");
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

			//para encapsular esto entre llaves
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

			
			
			if (!ExisteTipoAndModelName(lsModelName, lsType))
			{
				cObjectType lObjectType;
				lObjectType.SetModelName (lsModelName);
				lObjectType.SetType (lsType);
				mObjectType.push_back(lObjectType);
			}


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
			else //General
			{
				cObject* lObjectPtr = new cObject(*lObject);
				//(*lObjectPtr).Init(); //Como hay definido ya un constructor de copia, tengo que hacer el init por fuera y no como arriba que se invocaba al crearlo QUITAR ESTE INIT PAR QUE TB LO HAGA EN EL CONSTRUCTOR!
				mObject.push_back(lObjectPtr);
			}

			
			delete lObject;  //ya no nos hace falta, porque copiamos los parámetros y en el último caso lo duplicamos
		}
	}

	
	return true;

}

bool cObjectManager::ExisteTipoAndModelName(string lsModelName, string lsType)
{
	bool lbResul = false;

	for (unsigned int luiIndex = 0; luiIndex < mObjectType.size(); luiIndex++)
	{
		if ((mObjectType[luiIndex].GetModelName().c_str() == lsModelName.c_str()) && (mObjectType[luiIndex].GetType().c_str() == lsType.c_str()))
		{
			lbResul = true;
			break;
		}
	}

	return lbResul;
}



string cObjectManager::ObtenerTipoObjeto(string lsModelName)
{
	string lsType = "";

	for (unsigned int luiIndex = 0; luiIndex < mObjectType.size(); luiIndex++)
	{
		string lPrueba = mObjectType[luiIndex].GetModelName();
		if (mObjectType[luiIndex].GetModelName() == lsModelName)
		{
			lsType = mObjectType[luiIndex].GetType();
			break;
		}
	}

	return lsType;
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


void cObjectManager::InitPunterosFisica()
{
	
	for (unsigned luiIndex = 0; luiIndex < mObjectPista.size(); ++luiIndex )
	{
		mObjectPista[luiIndex]->SetPtrPhysicsObject(cPhysicsManager::Get().GetPhysicsObjectPtr(mObjectPista[luiIndex]->GetType(), mObjectPista[luiIndex]->GetModelName()));
	}


	for (unsigned luiIndex = 0; luiIndex < mObjectPlayer.size(); ++luiIndex )
		mObjectPlayer[luiIndex]->SetPtrPhysicsObject(cPhysicsManager::Get().GetPhysicsObjectPtr(mObjectPlayer[luiIndex]->GetType(), mObjectPlayer[luiIndex]->GetModelName()));


}