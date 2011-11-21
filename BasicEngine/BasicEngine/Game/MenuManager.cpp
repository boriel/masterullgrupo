#include "MenuManager.h"
#include <tinystr.h>
#include <tinyxml.h>
#include "InputConfiguration.h"
#include "..\Input\InputManager.h"

bool cMenuManager::Init(string lsFilename){
	mMenuPrincipal=new tMenu();
	mMenuJugar=new tMenu();
	mConfirmacion=new tMenu();
	mMenuOpciones=new tMenu();
	mMenuPartidaLibre=new tMenu();

	mMenuPrincipal->msMenuName="Menu Principal";
	mMenuPrincipal->muiNumItems=4;
	tMenuItem *aux=new tMenuItem();
	aux->mAction=Abrir;
	aux->msMenuItem="Jugar";
	aux->mTarget=mMenuJugar;
	mMenuPrincipal->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Abrir;
	aux->msMenuItem="Opciones";
	aux->mTarget=mMenuOpciones;
	mMenuPrincipal->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Comenzar;
	aux->msMenuItem="Créditos";
	aux->mTarget=NULL;
	mMenuPrincipal->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Preguntar;
	aux->msMenuItem="Salir";
	aux->mTarget=NULL;
	mMenuPrincipal->mItemsList.push_back(aux);
	muiSelectedItem=1;

	mMenuJugar->msMenuName="Jugar";
	mMenuJugar->muiNumItems=3;
	aux=new tMenuItem();
	aux->mAction=NoDisponible; // No esta disponible este modo
	aux->msMenuItem="Campaña";
	aux->mTarget=mMenuPrincipal;
	mMenuJugar->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Abrir;
	aux->msMenuItem="Partida Libre";
	aux->mTarget=mMenuPartidaLibre;
	mMenuJugar->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Atras;
	aux->msMenuItem="Atrás";
	aux->mTarget=mMenuPrincipal;
	mMenuJugar->mItemsList.push_back(aux);

	mMenuOpciones->msMenuName="Opciones";
	mMenuOpciones->muiNumItems=3;
	aux=new tMenuItem();
	aux->mAction=Sonido;
	aux->msMenuItem="Activar/Desactivar sonido";
	aux->mTarget=NULL;
	mMenuOpciones->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Musica;
	aux->msMenuItem="Activar/Desactivar música";
	aux->mTarget=NULL;
	mMenuOpciones->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Atras;
	aux->msMenuItem="Atrás";
	aux->mTarget=mMenuPrincipal;
	mMenuOpciones->mItemsList.push_back(aux);

	mMenuPartidaLibre->msMenuName="Partida Libre";
	mMenuPartidaLibre->muiNumItems=4;
	aux=new tMenuItem();
	aux->mAction=NoDisponible; // No esta disponible este modo
	aux->msMenuItem="Carrera cara a cara";
	aux->mTarget=mMenuPrincipal;
	mMenuPartidaLibre->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=NoDisponible; // No esta disponible este modo
	aux->msMenuItem="Carrera de cuatro";
	aux->mTarget=mMenuPrincipal;
	mMenuPartidaLibre->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Comenzar;
	aux->msMenuItem="Contrarreloj";
	aux->mTarget=NULL;
	mMenuPartidaLibre->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Atras;
	aux->msMenuItem="Atrás";
	aux->mTarget=mMenuJugar;
	mMenuPartidaLibre->mItemsList.push_back(aux);

	mConfirmacion->msMenuName="¿Está seguro?";
	mConfirmacion->muiNumItems=2;
	aux=new tMenuItem();
	aux->mAction=Salir;
	aux->msMenuItem="Sí";
	aux->mTarget=NULL;
	mConfirmacion->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Atras;
	aux->msMenuItem="No";
	aux->mTarget=NULL;
	mConfirmacion->mItemsList.push_back(aux);

	// Inicializamos las fuentes que usaremos
	mFont.Init("./Data/Fonts/Test2.fnt"); // Init the Font
	cFontManager::Get().Init(5);
	mFontHandle = cFontManager::Get().LoadResourcesXml("Fonts");  //cargando desde XML
	muiDistanceBWItems=30;

	// Añadimos el sonido del movimiento
	mMoveSound=new Sound();
	mMoveSound=cSoundManager::Get().AddSound("MenuMove.wav");
	
	cSoundManager::Get().Play(mMoveSound);

	// Inicializamos menu inicial
	mMenuActual = new tMenu();
	mMenuActual = mMenuPrincipal;
	return true;
}

void cMenuManager::Deinit(){
	// Eliminar todos los menús
	mMenuPrincipal->mItemsList.clear();
	delete mMenuPrincipal;
	mMenuJugar->mItemsList.clear();
	delete mMenuJugar;
	mMenuOpciones->mItemsList.clear();
	delete mMenuOpciones;
	mMenuPartidaLibre->mItemsList.clear();
	delete mMenuPartidaLibre;
	mConfirmacion->mItemsList.clear();
	delete mConfirmacion;
}

void cMenuManager::Render(){
	glEnable(GL_TEXTURE_2D);
	switch(cSceneManager::Get().GetScene())
	{
		case eMenuPrincipal:	
			mFont.SetHeight(40.0);
			// Posición: arriba izquierda
			mFont.Write(-280, 200, 0,mMenuActual->msMenuName.c_str(), 0,	FONT_ALIGN_LEFT);

			for (unsigned luiIndex = 0; luiIndex < mMenuActual->mItemsList.size(); ++luiIndex ) 
			{
				if(muiSelectedItem==luiIndex+1)
					mFont.Write(-250, 190-(1+(float)luiIndex)*muiDistanceBWItems, 0,("-> "+mMenuActual->mItemsList[luiIndex]->msMenuItem).c_str(), 0,	FONT_ALIGN_LEFT);
				else
					mFont.Write(-250, 190-(1+(float)luiIndex)*muiDistanceBWItems, 0,mMenuActual->mItemsList[luiIndex]->msMenuItem.c_str(), 0,	FONT_ALIGN_LEFT);
			}
			break;
		case eLoading:
			mFont.SetHeight(100.0);
			mFont.Write(0, 0, 0,"CARGANDO...", 0,	FONT_ALIGN_CENTER);
			break;
		case eNoDisponible:
			mFont.SetHeight(50.0);
			mFont.Write(0, 0, 0,"Modo aun no disponible.", 0,	FONT_ALIGN_CENTER);
			mFont.Write(0, -50, 0,"Presione 'Enter' para volver", 0,	FONT_ALIGN_CENTER);
			break;
	}
}

void cMenuManager::Update(float lfTimestep){
	// Movimiento por el menú
	if (BecomePressed(eIA_Up)){
		muiSelectedItem--;
		cSoundManager::Get().Play(mMoveSound);
	}
	if (BecomePressed(eIA_Down)){
		muiSelectedItem++;
		cSoundManager::Get().Play(mMoveSound);
	}
	// Con esto haremos el menú bucle, es decir que desde arriba pasa abajo
	if(muiSelectedItem<1)muiSelectedItem=mMenuActual->muiNumItems;
	if(muiSelectedItem>mMenuActual->muiNumItems)muiSelectedItem=1;
	
	if (BecomePressed(eIA_Accept) && (cSceneManager::Get().GetScene()==eNoDisponible) ){
		cSoundManager::Get().Play(mMoveSound);
		cSceneManager::Get().LoadScene(eMenuPrincipal);
	}

	
	if (BecomePressed(eIA_Accept) && (cSceneManager::Get().GetScene()==eMenuPrincipal) ){
		cSoundManager::Get().Play(mMoveSound);
		AbrirMenu();
	}


}

void cMenuManager::AbrirMenu(){
	// Obtenemos qué elemento se abrirá
	switch(mMenuActual->mItemsList.at(muiSelectedItem-1)->mAction){
		case Comenzar: // 
			cSceneManager::Get().LoadScene(eLoading);
			this->IniciarMenu();
			break;
		case NoDisponible:
			cSceneManager::Get().LoadScene(eNoDisponible);
		case Abrir: // Asignamos como menuactual al destino
			mMenuActual=mMenuActual->mItemsList.at(muiSelectedItem-1)->mTarget;
			break;
		case Atras: // Volvemos al destino
			mMenuActual=mMenuActual->mItemsList.at(muiSelectedItem-1)->mTarget;
			break;
		case Salir: // Cerramos el juego
			cGame::Get().SetFinished(true);
			break;
		case Preguntar: // Confirmamos decisión
			mConfirmacion->mItemsList.at(1)->mTarget=mMenuActual; // Asignamos que Atras vaya al menu anterior
			mMenuActual=mConfirmacion;
			break;
		case Sonido: // Activar/Desactivar sonido
			if(cSoundManager::Get().IsSoundOn()){
				cSoundManager::Get().DeactivateSound();
				cSoundManager::Get().Stop(mMoveSound);
			}
			else{
				cSoundManager::Get().ActivateSound();
				cSoundManager::Get().Play(mMoveSound);
			}
			break;
		case Musica: // Activar/Desactivar musica
			if(cSoundManager::Get().IsMusicOn()){
				cSoundManager::Get().DeactivateMusic();
				cSoundManager::Get().StopMusic();
			}else{
				cSoundManager::Get().ActivateMusic();
				cSoundManager::Get().PlayMusic();
			}
			break;
	}
	// Ponemos siempre el indicador al principio
	muiSelectedItem=1;
}

bool cMenuManager::LoadXml(void)
{   //Leemos todos los recursos desde un xml
	TiXmlDocument lDoc;

	lDoc.LoadFile ((char*)msFileName.c_str());
	if (!lDoc.LoadFile())
	{
		OutputDebugString ("[cMenuManager] XML Load: FAILED\n");
	}
	/* PENDIENTE DE HACER
	// Obtenemos el menú principal:
	TiXmlElement* lpElementRoot, *lpElementMain;
	lpElementRoot = lDoc.FirstChildElement ("Resources");
	lpElementMain = lpElementRoot->FirstChildElement("MenuPrincipal");

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

			lpLeg->mvPoint1.x = atof(lTokens[0].c_str());
			lpLeg->mvPoint1.y = atof(lTokens[1].c_str());
			lpLeg->mvPoint1.z = atof(lTokens[2].c_str());
		}

		if (lpElement->Attribute("Point2") != NULL) { 
			vector<string> lTokens;
			cStringUtils::Tokenize((char*)lpElement->Attribute("Point2"), lTokens, ",");

			lpLeg->mvPoint2.x = atof(lTokens[0].c_str());
			lpLeg->mvPoint2.y = atof(lTokens[1].c_str());
			lpLeg->mvPoint2.z = atof(lTokens[2].c_str());
		}
		mLegs.push_back(lpLeg);
	}
	*/
	return true;
}

