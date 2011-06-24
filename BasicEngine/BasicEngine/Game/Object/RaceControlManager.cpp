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
	mVehicles.clear();
	mLegs.clear();
}

void cRaceControlManager::Update(float lfTimestep)
{	//Update ControlRace info, for every vehicle
/*	for (unsigned luiIndex = 0; luiIndex < muiMaxVehicles; ++luiIndex )
	{
		cObjectVehicle* lpVehicle = (cObjectVehicle*) cObjectManager::Get().GetObjectA("Vehicle",mpVehicleControl[luiIndex].msModelName);
		//
	}*/
}

void cRaceControlManager::Render()
{
	for (unsigned luiIndex = 0; luiIndex < mLegs.size(); ++luiIndex ) 
	{
		cGraphicManager::Get().DrawLine(mLegs[luiIndex]->mvPoint1, mLegs[luiIndex]->mvPoint2,cVec3(0,0,255));
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

	//RACE element
	TiXmlElement* lpElementRoot, *lpElementRace;
	lpElementRoot = lDoc.FirstChildElement ("Resources");
	lpElementRace = lpElementRoot->FirstChildElement("Race");

	if (lpElementRace->Attribute("MaxLaps") != NULL) {
		muiMaxLaps = (unsigned int) atoi(lpElementRace->Attribute("MaxLaps"));
	} else { muiMaxLaps=0; }

	//VEHICLES elements
	TiXmlElement *lpElement;
	lpElement =  lpElementRace->FirstChildElement ("Vehicles"); 

	for (lpElement=lpElement->FirstChildElement("Vehicle"); lpElement; lpElement=lpElement->NextSiblingElement()) 
	{
		tVehicleControl* lpVehicle = new tVehicleControl;
		lpVehicle->msModelName="Sin Definir";
		lpVehicle->muiNumLaps=0;
		lpVehicle->muiNumLegs=0;
		lpVehicle->isOut=false;
			
		if (lpElement->Attribute("ModelName") != NULL)
			lpVehicle->msModelName = ((char*)lpElement->Attribute("ModelName"));

		mVehicles.push_back(lpVehicle);
	}

	//LEGS elements
	lpElement =  lpElementRace->FirstChildElement ("Legs");
	unsigned int luiNextLeg=0;

	for (lpElement=lpElement->FirstChildElement("Leg"); lpElement; lpElement=lpElement->NextSiblingElement()) 
	{
		tLegControl* lpLeg = new tLegControl;
		lpLeg->muiID = ++luiNextLeg;
		lpLeg->mvPoint1 = cVec3(0,0,0);
		lpLeg->mvPoint2 = cVec3(0,0,0);
			
		if (lpElement->Attribute("Point1") != NULL) { 
			vector<string> lTokens;
			Tokenize((char*)lpElement->Attribute("Point1"), lTokens, ",");

			lpLeg->mvPoint1.x = (float) strtod(lTokens[0].c_str(), NULL);
			lpLeg->mvPoint1.y = (float) strtod(lTokens[1].c_str(), NULL);
			lpLeg->mvPoint1.z = (float) strtod(lTokens[2].c_str(), NULL);
		}

		if (lpElement->Attribute("Point2") != NULL) { 
			vector<string> lTokens;
			Tokenize((char*)lpElement->Attribute("Point2"), lTokens, ",");

			lpLeg->mvPoint2.x = (float) strtod(lTokens[0].c_str(), NULL);
			lpLeg->mvPoint2.y = (float) strtod(lTokens[1].c_str(), NULL);
			lpLeg->mvPoint2.z = (float) strtod(lTokens[2].c_str(), NULL);
		}
		mLegs.push_back(lpLeg);
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

