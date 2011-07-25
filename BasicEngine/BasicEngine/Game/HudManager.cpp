#include "HudManager.h"
#include "..\Graphics\GraphicManager.h"
#include "..\Graphics\Fonts\FontManager.h"
#include "FPSCounter.h"

#include <tinystr.h>
#include <tinyxml.h>
#include <vector>


bool cHudManager::Init(string lsFileName) 
{	
	msFileName = lsFileName;
	LoadXml();
	
	mFont.Init("./Data/Fonts/Test2.fnt"); // Init the Font
	cFontManager::Get().Init(5);
	mFontHandle = cFontManager::Get().LoadResourcesXml("Fonts");  //cargando desde XML
	mIsHudActive=true;
	return true;
}

void cHudManager::Deinit()
{
	mFont.Deinit();
}

void cHudManager::Update(float lfTimestep)
{	
	// Obtendremos de RaceControlManager los datos que mostrar en el Hud

	// Habrá que crear estas funciones:
	// mHud.muiPosition = cRaceControlManager::Get().GetRacePosition(idPlayer);
	// mHud.muiNumActualLap = cRaceControlManager::Get().GetRaceActualLap(idPlayer);
	// mHud.muiNumTotalLaps = cRaceControlManager::Get().GetRaceTotalLaps();
}

void cHudManager::Render()
{
	glEnable(GL_TEXTURE_2D);
	if(mIsHudActive)
	{
		mFont.SetHeight(30.0);
		// Posición: abajo derecha
		char *lPosition=new char(); 
		sprintf(lPosition,"%i",mHud.muiPosition);
		mFont.Write(220, -220, 0,lPosition, 0,	FONT_ALIGN_CENTER);
		// Vuelta actual / Vueltas totales: arriba derecha
		char *lLaps=new char(); 
		sprintf(lLaps,"%i/%i",mHud.muiNumActualLap,mHud.muiNumTotalLaps);
		mFont.Write(220, 170, 0,lLaps, 0,	FONT_ALIGN_CENTER);
	}
	
#if _DEBUG		
		//Draw some strings
		mFont.SetColour( 1.0f, 1.0f, 1.0f );
		mFont.Write(0, 200, 0, "ESC o botón izquierdo para Salir", 0,	FONT_ALIGN_CENTER);
		//mFont.SetColour( 0.0f, 1.0f, 1.0f );
		mFont.Write(0, -200, 0, "Cursor = Vehicle Move -- W,A,S,D,PAG_UP,PAG_DOWN: God Camera", 0,	FONT_ALIGN_CENTER);
		mFont.Write(0, -220, 0, "F8 = Change Camera  F9 = Debug", 0,	FONT_ALIGN_CENTER);
	

		float lfFPS = cFPSCounter::Get().GetFPS();
		char* lpcFPS = new char[10];
		sprintf(lpcFPS, "%.2g FPS", lfFPS );
		mFont.Write(-260, 210, 0, lpcFPS, 0, FONT_ALIGN_CENTER);
	
#endif
}

bool cHudManager::LoadXml(void)
{   //Leemos todos los recursos desde un xml
	TiXmlDocument lDoc;

	lDoc.LoadFile ((char*)msFileName.c_str());
	if (!lDoc.LoadFile())
	{
		OutputDebugString ("[cHudManager] XML Load: FAILED\n");
	}
	/*
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
		lpVehicle->muiNextLeg=0;
		lpVehicle->isOut=false;
		lpVehicle->muiOrder=0;
		lpVehicle->muiKm=0;
			
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
		lpLeg->muiID = luiNextLeg++;
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
*/
	return true;
}

//para hacer un split de un string
void cHudManager::Tokenize(const string& str, vector<string>& tokens,  const string& delimiters)
{
  /*
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
	*/
}


