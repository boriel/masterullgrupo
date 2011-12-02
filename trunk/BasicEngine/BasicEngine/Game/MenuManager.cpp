#include "MenuManager.h"
#include <tinystr.h>
#include <tinyxml.h>
#include "InputConfiguration.h"
#include "..\Input\InputManager.h"
#include "..\Graphics\Textures\TextureManager.h"

bool cMenuManager::Init(string lsFilename){
	mMenuPrincipal=new tMenu();
	mMenuJugar=new tMenu();
	mConfirmacion=new tMenu();
	mMenuOpciones=new tMenu();
	mMenuPartidaLibre=new tMenu();
	mMenuPausa=new tMenu();

	// MENU INICIAL //
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
	aux->mAction=Creditos;
	aux->msMenuItem="Creditos";
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
	aux->mAction=ComenzarHistoria; // No esta disponible este modo
	aux->msMenuItem="Historia";
	aux->mTarget=mMenuPrincipal;
	mMenuJugar->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Abrir;
	aux->msMenuItem="Partida Libre";
	aux->mTarget=mMenuPartidaLibre;
	mMenuJugar->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Atras;
	aux->msMenuItem="Atr�s";
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
	aux->msMenuItem="Activar/Desactivar musica";
	aux->mTarget=NULL;
	mMenuOpciones->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Atras;
	aux->msMenuItem="Atr�s";
	aux->mTarget=mMenuPrincipal;
	mMenuOpciones->mItemsList.push_back(aux);

	mMenuPartidaLibre->msMenuName="Partida Libre";
	mMenuPartidaLibre->muiNumItems=4;
	aux=new tMenuItem();
	aux->mAction=Comenzar2Jug; // No esta disponible este modo
	aux->msMenuItem="Carrera cara a cara";
	aux->mTarget=mMenuPrincipal;
	mMenuPartidaLibre->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Comenzar4Jug; // No esta disponible este modo
	aux->msMenuItem="Carrera de cuatro";
	aux->mTarget=mMenuPrincipal;
	mMenuPartidaLibre->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=ComenzarContrarreloj;
	aux->msMenuItem="Contrarreloj";
	aux->mTarget=NULL;
	mMenuPartidaLibre->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Atras;
	aux->msMenuItem="Atr�s";
	aux->mTarget=mMenuJugar;
	mMenuPartidaLibre->mItemsList.push_back(aux);

	mConfirmacion->msMenuName="�Esta seguro?";
	mConfirmacion->muiNumItems=2;
	aux=new tMenuItem();
	aux->mAction=Salir;
	aux->msMenuItem="Si";
	aux->mTarget=NULL;
	mConfirmacion->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Atras;
	aux->msMenuItem="No";
	aux->mTarget=NULL;
	mConfirmacion->mItemsList.push_back(aux);

	// MENU PAUSA //

	mMenuPausa->msMenuName="Pausa";
	mMenuPausa->muiNumItems=4;
	aux=new tMenuItem();
	aux->mAction=Continuar;
	aux->msMenuItem="Continuar";
	aux->mTarget=NULL;
	mMenuPausa->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Sonido;
	aux->msMenuItem="Activar/Desactivar sonido";
	aux->mTarget=NULL;
	mMenuPausa->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Musica;
	aux->msMenuItem="Activar/Desactivar musica";
	aux->mTarget=NULL;
	mMenuPausa->mItemsList.push_back(aux);
	aux=new tMenuItem();
	aux->mAction=Preguntar;
	aux->msMenuItem="Salir";
	aux->mTarget=NULL;
	mMenuPausa->mItemsList.push_back(aux);

	// A�adimos los sonidos de movimiento

	Sound *lAux=new Sound();
	lAux=cSoundManager::Get().AddSound("/Menu/Movimiento1.wav");
	mMoves_SoundBank.push_back(lAux);
	lAux=new Sound();
	lAux=cSoundManager::Get().AddSound("/Menu/Movimiento2.wav");
	mMoves_SoundBank.push_back(lAux);
	lAux=new Sound();
	lAux=cSoundManager::Get().AddSound("/Menu/Movimiento3.wav");
	mMoves_SoundBank.push_back(lAux);
	lAux=new Sound();
	lAux=cSoundManager::Get().AddSound("/Menu/Movimiento4.wav");
	mMoves_SoundBank.push_back(lAux);
	lAux=new Sound();
	lAux=cSoundManager::Get().AddSound("/Menu/Movimiento5.wav");
	mMoves_SoundBank.push_back(lAux);
	lAux=new Sound();
	lAux=cSoundManager::Get().AddSound("/Menu/Movimiento6.wav");
	mMoves_SoundBank.push_back(lAux);
	lAux=new Sound();
	lAux=cSoundManager::Get().AddSound("/Menu/Movimiento7.wav");
	mMoves_SoundBank.push_back(lAux);
	lAux=new Sound();
	lAux=cSoundManager::Get().AddSound("/Menu/Movimiento8.wav");
	mMoves_SoundBank.push_back(lAux);
	lAux=new Sound();
	lAux=cSoundManager::Get().AddSound("/Menu/Movimiento9.wav");
	mMoves_SoundBank.push_back(lAux);

	mAceptarSound=new Sound();
	mAceptarSound=cSoundManager::Get().AddSound("/Menu/Aceptar.wav");

	mAtrasSound=new Sound();
	mAtrasSound=cSoundManager::Get().AddSound("/Menu/Atras.wav");

	mMusicaCreditos=new Sound();
	mMusicaCreditos=cSoundManager::Get().AddSound("/Menu/MusicaCreditos.wav");

	//A�adimos las texturas
	mTexturaFondoMenu=cTextureManager::Get().LoadResource("Fondo","./Data/Menu/FondoMenu.jpg");
	mPortada=cTextureManager::Get().LoadResource("Portada","./Data/Menu/Portada.jpg");

	// Inicializamos las fuentes que usaremos
	mFont.Init("./Data/Fonts/Test1.fnt"); // Init the Font
	cFontManager::Get().Init(5);
	mFontHandle = cFontManager::Get().LoadResourcesXml("Fonts");  //cargando desde XML
	muiDistanceBWItems=30;
	mParpadeo=true;
	mTiempoParpadeo=0;

	// Inicializamos menu inicial
	mMenuActual = new tMenu();
	mMenuActual = mMenuPrincipal;
	return true;
}

void cMenuManager::Deinit(){
	mFont.Deinit();
	// Eliminar todos los men�s
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
	GLint lAuxX;
	GLint lAuxY;
	glEnable(GL_TEXTURE_2D);
	switch(cSceneManager::Get().GetScene())
	{
		case eMenuPrincipal:	

			mFont.SetHeight(40.0);
			// Posici�n: arriba izquierda
			mFont.SetColour(1.0f,1.0f,1.0f);
			mFont.Write(-1000, 100, 10,mMenuActual->msMenuName.c_str(), 0,	FONT_ALIGN_LEFT);
			
			mFont.SetColour(0.0f,0.0f,0.0f);
			glBindTexture( GL_TEXTURE_2D, mTexturaFondoMenu.GetKey() );
			// Draw texture using a quad 
			glBegin(GL_POLYGON); 
			lAuxX=cWindow::Get().GetWidth()/2;
			lAuxY=cWindow::Get().GetHeight()/2;

			// Top left 
			glTexCoord2f(1.0, 1.0); 
			glVertex2i(lAuxX,-lAuxY); 
			// Top right 
			glTexCoord2f(0.0, 1.0); 
			glVertex2i(-lAuxX, -lAuxY); 
			// Bottom right 
			glTexCoord2f(0.0, 0.0); 
			glVertex2i(-lAuxX, lAuxY); 
			// Bottom left 
			glTexCoord2f(1.0, 0.0); 
			glVertex2i(lAuxX,lAuxY); 
			// Finish quad drawing 
			glEnd();

			mFont.Write(-260, 150, 0,mMenuActual->msMenuName.c_str(), 0,	FONT_ALIGN_LEFT);

			for (unsigned luiIndex = 0; luiIndex < mMenuActual->mItemsList.size(); ++luiIndex ) 
			{
				if(muiSelectedItem==luiIndex+1)
					mFont.Write(-220, 140-(1+(float)luiIndex)*muiDistanceBWItems, 0,("-> "+mMenuActual->mItemsList[luiIndex]->msMenuItem).c_str(), 0,	FONT_ALIGN_LEFT);
				else
					mFont.Write(-220, 140-(1+(float)luiIndex)*muiDistanceBWItems, 0,mMenuActual->mItemsList[luiIndex]->msMenuItem.c_str(), 0,	FONT_ALIGN_LEFT);
			}
			break;
		case eLoading:
			mFont.SetHeight(40.0);
			// Posici�n: arriba izquierda
			mFont.SetColour(1.0f,1.0f,1.0f);
			mFont.Write(-1000, 100, 10,mMenuActual->msMenuName.c_str(), 0,	FONT_ALIGN_LEFT);
			
			mFont.SetColour(0.0f,0.0f,0.0f);
			if(cSceneManager::Get().GetHistoria()==0)
				glBindTexture( GL_TEXTURE_2D, mTexturaFondoMenu.GetKey() );
			if(cSceneManager::Get().GetHistoria()==1)
				glBindTexture( GL_TEXTURE_2D, mTexturaFondoMenu.GetKey() );
			if(cSceneManager::Get().GetHistoria()==2)
				glBindTexture( GL_TEXTURE_2D, mTexturaFondoMenu.GetKey() );
			if(cSceneManager::Get().GetHistoria()==3)
				glBindTexture( GL_TEXTURE_2D, mTexturaFondoMenu.GetKey() );

			// Draw texture using a quad 
			glBegin(GL_POLYGON); 
			lAuxX=cWindow::Get().GetWidth()/2;
			lAuxY=cWindow::Get().GetHeight()/2;

			// Top left 
			glTexCoord2f(1.0, 1.0); 
			glVertex2i(lAuxX,-lAuxY); 
			// Top right 
			glTexCoord2f(0.0, 1.0); 
			glVertex2i(-lAuxX, -lAuxY); 
			// Bottom right 
			glTexCoord2f(0.0, 0.0); 
			glVertex2i(-lAuxX, lAuxY); 
			// Bottom left 
			glTexCoord2f(1.0, 0.0); 
			glVertex2i(lAuxX,lAuxY); 
			// Finish quad drawing 
			glEnd();

			if(cSceneManager::Get().GetHistoria()==0)mFont.Write(0, 0, 0,"CARGANDO...", 0,	FONT_ALIGN_CENTER);
			else mFont.Write(0, -195, 0,"CARGANDO...", 0,	FONT_ALIGN_CENTER);
			break;
		case eNoDisponible:
			mFont.SetHeight(50.0);
			mFont.Write(0, 0, 0,"Modo aun no disponible.", 0,	FONT_ALIGN_CENTER);
			mFont.Write(0, -50, 0,"Presione 'Enter' para volver", 0,	FONT_ALIGN_CENTER);
			break;
		case ePausa:
			mFont.SetHeight(40.0);
			// Posici�n: arriba izquierda
			mFont.SetColour(1.0f,1.0f,1.0f);
			mFont.Write(-1000, 100, 10,mMenuActual->msMenuName.c_str(), 0,	FONT_ALIGN_LEFT);
			
			mFont.SetColour(0.0f,0.0f,0.0f);
			glBindTexture( GL_TEXTURE_2D, mTexturaFondoMenu.GetKey() );
			// Draw texture using a quad 
			glBegin(GL_POLYGON); 
			lAuxX=cWindow::Get().GetWidth()/2;
			lAuxY=cWindow::Get().GetHeight()/2;

			// Top left 
			glTexCoord2f(1.0, 1.0); 
			glVertex2i(lAuxX,-lAuxY); 
			// Top right 
			glTexCoord2f(0.0, 1.0); 
			glVertex2i(-lAuxX, -lAuxY); 
			// Bottom right 
			glTexCoord2f(0.0, 0.0); 
			glVertex2i(-lAuxX, lAuxY); 
			// Bottom left 
			glTexCoord2f(1.0, 0.0); 
			glVertex2i(lAuxX,lAuxY); 
			// Finish quad drawing 
			glEnd();

			mFont.Write(-260, 150, 0,mMenuActual->msMenuName.c_str(), 0,	FONT_ALIGN_LEFT);

			for (unsigned luiIndex = 0; luiIndex < mMenuActual->mItemsList.size(); ++luiIndex ) 
			{
				if(muiSelectedItem==luiIndex+1)
					mFont.Write(-220, 140-(1+(float)luiIndex)*muiDistanceBWItems, 0,("-> "+mMenuActual->mItemsList[luiIndex]->msMenuItem).c_str(), 0,	FONT_ALIGN_LEFT);
				else
					mFont.Write(-220, 140-(1+(float)luiIndex)*muiDistanceBWItems, 0,mMenuActual->mItemsList[luiIndex]->msMenuItem.c_str(), 0,	FONT_ALIGN_LEFT);
			}
			break;
		case ePortada:
			mFont.SetHeight(40.0);
			// Posici�n: arriba izquierda
			mFont.SetColour(1.0f,1.0f,1.0f);
			mFont.Write(-1000, 100, 10,mMenuActual->msMenuName.c_str(), 0,	FONT_ALIGN_LEFT);
			
			mFont.SetColour(0.0f,0.0f,0.0f);
			glBindTexture( GL_TEXTURE_2D, mPortada.GetKey() );
			// Draw texture using a quad 
			glBegin(GL_POLYGON); 
			
			lAuxX=cWindow::Get().GetWidth()/2;
			lAuxY=cWindow::Get().GetHeight()/2;

			// Top left 
			glTexCoord2f(1.0, 1.0); 
			glVertex2i(lAuxX,-lAuxY); 
			// Top right 
			glTexCoord2f(0.0, 1.0); 
			glVertex2i(-lAuxX, -lAuxY); 
			// Bottom right 
			glTexCoord2f(0.0, 0.0); 
			glVertex2i(-lAuxX, lAuxY); 
			// Bottom left 
			glTexCoord2f(1.0, 0.0); 
			glVertex2i(lAuxX,lAuxY); 
			// Finish quad drawing 
			glEnd();

			if(mParpadeo)mFont.Write(0, -195, 0,"Presione 'Enter' para continuar", 0,	FONT_ALIGN_CENTER);
			break;
		case eCreditos:
			mFont.SetHeight(40.0);
			// Posici�n: arriba izquierda
			mFont.SetColour(1.0f,1.0f,1.0f);
			mFont.Write(-1000, 100, 10,mMenuActual->msMenuName.c_str(), 0,	FONT_ALIGN_LEFT);
			
			mFont.SetColour(0.0f,0.0f,0.0f);
			glBindTexture( GL_TEXTURE_2D, mTexturaFondoMenu.GetKey() ); // Poner im�gen de cr�ditos
			// Draw texture using a quad 
			glBegin(GL_POLYGON); 
			
			lAuxX=cWindow::Get().GetWidth()/2;
			lAuxY=cWindow::Get().GetHeight()/2;

			// Top left 
			glTexCoord2f(1.0, 1.0); 
			glVertex2i(lAuxX,-lAuxY); 
			// Top right 
			glTexCoord2f(0.0, 1.0); 
			glVertex2i(-lAuxX, -lAuxY); 
			// Bottom right 
			glTexCoord2f(0.0, 0.0); 
			glVertex2i(-lAuxX, lAuxY); 
			// Bottom left 
			glTexCoord2f(1.0, 0.0); 
			glVertex2i(lAuxX,lAuxY); 
			// Finish quad drawing 
			glEnd();

			if(mParpadeo)mFont.Write(0, -195, 0,"Presione 'Enter' para volver", 0,	FONT_ALIGN_CENTER);
			break;
	}
	
}

void cMenuManager::Update(float lfTimestep){
	// Movimiento por el men�
	if (BecomePressed(eIA_Up)){
		muiSelectedItem--;
		cSoundManager::Get().PlaySoundBank(&mMoves_SoundBank);
	}
	if (BecomePressed(eIA_Down)){
		muiSelectedItem++;
		cSoundManager::Get().PlaySoundBank(&mMoves_SoundBank);
	}
	// Con esto haremos el men� bucle, es decir que desde arriba pasa abajo
	if(muiSelectedItem<1)muiSelectedItem=mMenuActual->muiNumItems;
	if(muiSelectedItem>mMenuActual->muiNumItems)muiSelectedItem=1;
	
	if (BecomePressed(eIA_Accept) && ((cSceneManager::Get().GetScene()==eNoDisponible)|| cSceneManager::Get().GetScene() == eCreditos || cSceneManager::Get().GetScene() == ePortada) ){
		cSoundManager::Get().Play(mAceptarSound);
		cSceneManager::Get().LoadScene(eMenuPrincipal);
	}else if (BecomePressed(eIA_Accept) && ((cSceneManager::Get().GetScene()==eMenuPrincipal) || (cSceneManager::Get().GetScene()==ePausa))){
		cSoundManager::Get().Play(mAceptarSound);
		AbrirMenu();
	}

	/*if(cSceneManager::Get().GetScene() == ePortada && BecomePressed(eIA_Accept)){
		cSoundManager::Get().Play(mAceptarSound);
		cSceneManager::Get().LoadScene(eMenuPrincipal);
	}*/



	if(mTiempoParpadeo>10){
		mParpadeo=!mParpadeo;
		mTiempoParpadeo=0;
	}else mTiempoParpadeo++;

}

void cMenuManager::AbrirMenu(){
	// Obtenemos qu� elemento se abrir�
	switch(mMenuActual->mItemsList.at(muiSelectedItem-1)->mAction){
		case Continuar:
			cSceneManager::Get().LoadScene(eGameplay);
			break;
		case ComenzarContrarreloj:
			cSoundManager::Get().StopMusic();
			cRaceControlManager::Get().SetTipoPartida(eContrarreloj); 
			cSceneManager::Get().LoadScene(eLoading);
			this->IniciarMenu();
			break;
		case Comenzar2Jug: 
			cSoundManager::Get().StopMusic();
			cRaceControlManager::Get().SetTipoPartida(e2Jugadores);
			cSceneManager::Get().LoadScene(eLoading);
			this->IniciarMenu();
			break;
		case Comenzar4Jug: 
			cSoundManager::Get().StopMusic();
			cRaceControlManager::Get().SetTipoPartida(e4Jugadores);
			cSceneManager::Get().LoadScene(eLoading);
			this->IniciarMenu();
			break;
		case ComenzarHistoria: 
			cSoundManager::Get().StopMusic();
			cRaceControlManager::Get().SetTipoPartida(eCampana);
			cSceneManager::Get().NextHistoria();
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
		case Preguntar: // Confirmamos decisi�n
			mConfirmacion->mItemsList.at(1)->mTarget=mMenuActual; // Asignamos que Atras vaya al menu anterior
			mMenuActual=mConfirmacion;
			break;
		case Sonido: // Activar/Desactivar sonido
			if(cSoundManager::Get().IsSoundOn()){
				cSoundManager::Get().DeactivateSound();
				cSoundManager::Get().Stop(mAceptarSound);
			}
			else{
				cSoundManager::Get().ActivateSound();
				cSoundManager::Get().Play(mAceptarSound);
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
		case Creditos:
			cSceneManager::Get().LoadScene(eCreditos);
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
	// Obtenemos el men� principal:
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
