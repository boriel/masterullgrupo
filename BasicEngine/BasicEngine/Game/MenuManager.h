/*
class cMenuManager: Controla los men�s. Tanto el inicial como el de pausa en medio de la partida.
					Posible actualizaci�n: Cargar los men�s de XML.
*/

#pragma once

#include "..\Utility\Singleton.h"
#include "..\Graphics\Fonts\acgfx_font.h"
#include "..\Graphics\GraphicManager.h"
#include "..\Graphics\Fonts\FontManager.h"
#include "..\Sound\SoundManager.h"
#include "SceneManager.h"
#include <vector>

using namespace std;

// Se usar�n para saber qu� hace el elemento del men�
enum Action{
	Abrir,
	Comenzar,
	Preguntar,
	Atras,
	Sonido,
	Musica,
	Salir,
};

struct tMenu;

struct tMenuItem
{
	// Aqu� tendremos los diferentes items del men�
	std::string msMenuItem; // Identificador del item
	Action mAction;
	tMenu *mTarget; // En caso de Abrir, necesitamos saber qu� abrir.
	// Necesitaremos tipos de comportamiento para saber
	// qu� tipo de acci�n realizar� el item:
	// Abrir otro menu, Cerrar Juego, Empezar juego...
};

struct tMenu
{
	// Aqu� tendremos los diferentes men�s
	std::string msMenuName; //Identificador del Men�
	unsigned int muiNumItems; //N�mero de elementos
	std::vector<tMenuItem *> mItemsList;
};

class cMenuManager :
	public cSingleton<cMenuManager>
{
public:
	public:	
		bool Init(string lsFilename);
		void Deinit();
		void Render();
		void Update(float lfTimestep); 
		void AbrirMenu(); // Haremos la acci�n apropiada con cada elemento del men�

	private:
		string msFileName;
		// Men�s Iniciales
		tMenu *mMenuActual;

		tMenu *mMenuPrincipal;
		tMenu *mMenuJugar;
		tMenu *mMenuOpciones;
		tMenu *mMenuPartidaLibre;
		tMenu *mConfirmacion; // Peque�o men� para decisiones que requieran "si/no"
		// Men� Pausa inGame
		tMenu *mMenuPausa;

		// Variables de est�tica
		unsigned int muiSelectedItem;
		unsigned int muiDistanceBWItems; // Selecciona la distancia entre dos menuitems

		// Sonidos
		Sound *mMoveSound;

		// La fuente que utilizaremos
		cFont mFont; // La fuente con la que escribiremos los textos
		cResourceHandle mFontHandle;
		// Carga XML
		bool LoadXml(void);
};

