#include "ObjectManager.h"

#include <tinystr.h>
#include <tinyxml.h>
#include <Windows.h>

#include "..\Scene\ModelManager.h"
#include "ObjectPlayer.h"
#include "ObjectPista.h"

bool cObjectManager::Init() 
{
	msFilename = (".\\Data\\" + std::string("Resources.xml"));

	mfPI = 3.1416;


	//Lemeos desde un xml
	LoadObjectsXml("Objects");  //leyendo los objetos sin fisica
	//LoadObjectsXml("ObjectsCollision");  //Poniendo las collisiones

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

			

			//Lo iba a poner en una funcion, pero si esto crece en parametros como la pista pasarle los limites, el parametro descompensa. Incluye Init en los constructores
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
				(*lObjectPtr).Init(); //Como hay definido ya un constructor de copia, tengo que hacer el init por fuera y no como arriba que se invocaba al crearlo QUITAR ESTE INIT PAR QUE TB LO HAGA EN EL CONSTRUCTOR!
				mObject.push_back(lObjectPtr);
			}

			
			delete lObject;  //ya no nos hace falta, porque copiamos los parámetros y en el último caso lo duplicamos
		}
	}

	
	return true;

}

bool cObjectManager::LoadObjectsXmlCollision(std::string lsResource)
{
	TiXmlDocument lDoc;

	lDoc.LoadFile ((char*)msFilename.c_str());
	if (!lDoc.LoadFile())
	{
		OutputDebugString ("XML Load: FAILED\n");
	}

	
	TiXmlElement *lpElementResources;
	lpElementResources = lDoc.FirstChildElement ("Resources");

	
	if (lsResource == "ObjectsCollision")
	{
		TiXmlElement *lpElement;
		lpElement =  lpElementResources->FirstChildElement (lsResource); 
		


		
		for (lpElement = lpElement->FirstChildElement("ObjectCollision"); lpElement; lpElement = lpElement->NextSiblingElement()) 
		{
			std::string lsType, lsModelFile, lsModelName, lsPosition, lsScale = "", lsCollX = "", lsCollY = "", lsCollZ = "";
			float lfScale = 1.0f;
			cVec3 lCollision = cVec3(0.5, 0.5, 0.5);
		
		}

	}

	return true;
}






//para hacer un split de un string
void  cObjectManager::Tokenize(const string& str, vector<string>& tokens,  const string& delimiters)
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