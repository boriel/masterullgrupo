#include "RaceControlManager.h"
#include "ObjectManager.h"
#include "ObjectVehicle.h"
#include "..\..\Graphics\GraphicManager.h"
#include <tinystr.h>
#include <tinyxml.h>
#include <vector>

bool cRaceControlManager::Init(string lsFileName) 
{	
	msFileName = lsFileName;
	LoadXml();
	
	return true;
}

void cRaceControlManager::Deinit()
{
	delete mpVehicleControl;
	delete mpLegControl;
}

void cRaceControlManager::Update(float lfTimestep)
{	//Update ControlRace info, for every vehicle
	for (unsigned luiIndex = 0; luiIndex < muiMaxVehicles; ++luiIndex )
	{
		cObjectVehicle* lpVehicle = (cObjectVehicle*) cObjectManager::Get().GetObjectA("Vehicle",mpVehicleControl[luiIndex].msModelName);
		//
	}
}

void cRaceControlManager::Render()
{
	for (unsigned luiIndex = 0; luiIndex < muiMaxLegs; ++luiIndex ) 
	{
		cGraphicManager::Get().DrawLine(mpLegControl[luiIndex].mvPoint1,mpLegControl[luiIndex].mvPoint2,cVec3(0,0,255));
	}
}

bool cRaceControlManager::LoadXml(void)
{   //Leemos todos los recursos desde un xml
	TiXmlDocument lDoc;

	lDoc.LoadFile ((char*)msFileName.c_str());
	if (!lDoc.LoadFile())
	{
		OutputDebugString ("[cRaceControlManager] XML Load: FAILED\n");
	}
	
	TiXmlElement *lpElementResources;
	lpElementResources = lDoc.FirstChildElement ("RaceControl");
	
	TiXmlElement *lpElement;
	lpElement =  lpElementResources->FirstChildElement ("VehicleControl"); 

	for (lpElement = lpElement->FirstChildElement("Object"); lpElement; lpElement = lpElement->NextSiblingElement()) 
	{
		std::string lsType, lsModelFile, lsModelName, lsPosition, lsScale = "", lsRotation = "", lsAngle = "";
		float lfScale = 1.0f;
		cVec3 lCollision = cVec3(0.5, 0.5, 0.5);
		cQuaternion lQuatRot = cQuaternion(1,0,0,0);
			
		if (lpElement->Attribute("ModelName") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
			lsModelName = ((char*)lpElement->Attribute("ModelName"));

		if (lpElement->Attribute("Position") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
			lsPosition = ((char*)lpElement->Attribute("Position"));

		if (lpElement->Attribute("Rotation") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
			lsRotation = ((char*)lpElement->Attribute("Rotation"));

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
			
			
		if ((lsRotation != "") && (lsAngle != ""))
		{
			vector<string> lTokens;
			Tokenize(lsRotation, lTokens, ",");
			double ldX = strtod(lTokens[0].c_str(), NULL);
			double ldY = strtod(lTokens[1].c_str(), NULL);
			double ldZ = strtod(lTokens[2].c_str(), NULL);
		}	

		(*lObject).SetType (lsType);
		(*lObject).SetModelName(lsModelName);
		(*lObject).SetModelFile(lsModelFile);
			
		delete lObject;  //ya no nos hace falta, porque copiamos los parámetros y en el último caso lo duplicamos
	}	
	return true;
}

//para hacer un split de un string
void cRaceControlManager::Tokenize(const string& str, vector<string>& tokens,  const string& delimiters)
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

