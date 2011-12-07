#include "HudManager.h"
#include "..\Graphics\GraphicManager.h"
#include "..\Graphics\Fonts\FontManager.h"
#include "FPSCounter.h"
#include "Object\RaceControlManager.h"
#include "SceneManager.h"

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
	//mHud.muiPosition = cRaceControlManager::Get().GetRacePosition(idPlayer);
	mHud.muiNumActualLap = cRaceControlManager::Get().GetRaceActualLap();
	mHud.muiNumTotalLaps = cRaceControlManager::Get().GetRaceTotalLaps();
	mHud.muiTiempoCarrera = cRaceControlManager::Get().GetRaceTime();
}

void cHudManager::Render()
{
	glEnable(GL_TEXTURE_2D);
	int lPosX;
	int lPosY;
	if(cRaceControlManager::Get().isFinalRace()){
		mFont.SetHeight(40);
		mFont.SetColour(1.0,0,0);

		lPosY=40*(int)cWindow::Get().GetHeight()/DEFAULT_HEIGHT;

		if(cRaceControlManager::Get().GetTipoPartida()==eContrarreloj){
			mFont.Write(0, lPosY, 0,"Has conseguido un tiempo de:", 0,FONT_ALIGN_CENTER);
			mFont.Write(0, 0, 0,cRaceControlManager::Get().millisecondsToString(mHud.muiTiempoCarrera), 0,FONT_ALIGN_CENTER);
		}else if(cRaceControlManager::Get().GetVictoria()){
				mFont.Write(0, lPosY, 0,"Felicidades! Has Ganado! :)", 0,FONT_ALIGN_CENTER);
			}else mFont.Write(0, lPosY, 0,"Lo siento... Has Perdido... :(", 0,FONT_ALIGN_CENTER);
			
		if(cSceneManager::Get().GetHistoria()==0 || !cRaceControlManager::Get().GetVictoria())mFont.Write(0, -lPosY, 0,"Presiona 'Enter' para volver al menu", 0,FONT_ALIGN_CENTER);
		else mFont.Write(0, -lPosY, 0,"Presiona 'Enter' para ir al siguiente nivel", 0,FONT_ALIGN_CENTER);
	}else if(mIsHudActive && cRaceControlManager::Get().isRaceRunning()){
		mFont.SetHeight(50.0);
		mFont.SetColour(1.0,0,0);
		// Posición: abajo derecha // No mostraremos la posición. El primero que llegue acaba la partida
		/*char *lPosition=new char(); 
		sprintf(lPosition,"%i",mHud.muiPosition);
		mFont.Write(220, -220, 0,lPosition, 0,	FONT_ALIGN_CENTER);*/
		// Vuelta actual / Vueltas totales: arriba derecha
		char *lLaps=new char(); 
		sprintf(lLaps,"%i/%i",mHud.muiNumActualLap,mHud.muiNumTotalLaps);
		lPosY=-220*(int)cWindow::Get().GetHeight()/DEFAULT_HEIGHT;
		lPosX=220*(int)cWindow::Get().GetWidth()/DEFAULT_WIDTH;
		mFont.Write(lPosX, lPosY, 0,lLaps, 0,	FONT_ALIGN_CENTER);


		// Tiempo de carrera: Algun lugar
		char *lTime=new char(); 
		int milisegundos;
		int segundos;
		int minutos;
		milisegundos = mHud.muiTiempoCarrera ;

		//sprintf(lLaps,"%i:%i:%i",minutos, segundos, milisegundos);// Hay que mejorar cómo se muestra el tiempo recorrido
		//sprintf(lLaps,"%S",cRaceControlManager::Get().millisecondsToString(mHud.muiTiempoCarrera));

		//std::string aux=cRaceControlManager::Get().millisecondsToString(mHud.muiTiempoCarrera);
		//sprintf(lTime,"%s",aux);
		lPosY=170*(int)cWindow::Get().GetHeight()/DEFAULT_HEIGHT;
		if(cRaceControlManager::Get().GetTipoPartida()==eContrarreloj)mFont.Write(0, lPosY, 0,cRaceControlManager::Get().millisecondsToString(mHud.muiTiempoCarrera), 0,	FONT_ALIGN_CENTER);
	}

	// Cuenta atrás para empezar: Centro de la pantalla
	if(cRaceControlManager::Get().GetCuentaAtras()>0){
		char *lCuentaAtras=new char(); 
		sprintf(lCuentaAtras,"%i",cRaceControlManager::Get().GetCuentaAtras());
		mFont.SetHeight(70);
		mFont.SetColour(255,0,0);
		mFont.Write(0, 0, 0,lCuentaAtras, 0,	FONT_ALIGN_CENTER);
	}

#if _DEBUG		
		//Draw some strings
		mFont.SetColour( 1.0f, 1.0f, 1.0f );
		mFont.Write(0, 200, 0, "ESC o botón izquierdo para Salir", 0,	FONT_ALIGN_CENTER);
		//mFont.SetColour( 0.0f, 1.0f, 1.0f );
		mFont.Write(0, -200, 0, "Cursor = Vehicle Move -- W,A,S,D,PAG_UP,PAG_DOWN: God Camera -- R: Reload", 0,	FONT_ALIGN_CENTER);
		mFont.Write(0, -220, 0, "F8 = Change Camera  F9 = Debug", 0,	FONT_ALIGN_CENTER);
	
#endif
		/*
		float lfFPS = cFPSCounter::Get().GetFPS();
		char* lpcFPS = new char[10];
		sprintf(lpcFPS, "%.2g FPS", lfFPS );
		mFont.Write(-260, 210, 0, lpcFPS, 0, FONT_ALIGN_CENTER);
		*/
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
			cStringUtils::Tokenize((char*)lpElement->Attribute("Point1"), lTokens, ",");

			lpLeg->mvPoint1.x = (float) atof(lTokens[0].c_str());
			lpLeg->mvPoint1.y = (float) atof(lTokens[1].c_str());
			lpLeg->mvPoint1.z = (float) atof(lTokens[2].c_str());
		}

		if (lpElement->Attribute("Point2") != NULL) { 
			vector<string> lTokens;
			cStringUtils::Tokenize((char*)lpElement->Attribute("Point2"), lTokens, ",");

			lpLeg->mvPoint2.x = (float) atof(lTokens[0].c_str());
			lpLeg->mvPoint2.y = (float) atof(lTokens[1].c_str());
			lpLeg->mvPoint2.z = (float) atof(lTokens[2].c_str());
		}
		mLegs.push_back(lpLeg);
	}
*/
	return true;
}

