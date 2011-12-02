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
#include "Object\RaceControlManager.h"
#include <vector>

using namespace std;

// Se usar�n para saber qu� hace el elemento del men�
enum Action{
	Abrir,
	ComenzarContrarreloj,
	Comenzar2Jug,
	Comenzar4Jug,
	ComenzarHistoria,
	Continuar,
	NoDisponible,
	Preguntar,
	Atras,
	Sonido,
	Musica,
	Creditos,
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
		inline void IniciarMenu(){mMenuActual = mMenuPrincipal;muiSelectedItem=1;}
		void MenuPausa(){mMenuActual=mMenuPausa;}
		inline void SetAviso(bool lParpadeo){mAviso=lParpadeo;}
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
		bool mParpadeo; // Dar� efecto de parpadear a ciertos elementos
		unsigned int mTiempoParpadeo;
		bool mAviso;

		// Sonidos
		Sound *mAceptarSound;
		Sound *mAtrasSound;
		Sound *mMusicaMenu;
		Sound *mMusicaCreditos;
		mSoundBank mMoves_SoundBank; // A�adiremos todos los sonidos para los movimientos, de manera que podamos ejecutarlos aleatoriamente
		// La fuente que utilizaremos
		cFont mFont; // La fuente con la que escribiremos los textos
		cResourceHandle mFontHandle;
		cResourceHandle mTexturaFondoMenu;
		cResourceHandle mTexturaFondoCargando;
		cResourceHandle mTexturaFondoHistoria1;
		cResourceHandle mTexturaFondoHistoria2;
		cResourceHandle mTexturaFondoHistoria3;
		cResourceHandle mTexturaFondoHistoria4;
		cResourceHandle mPortada;
		cResourceHandle mTexturaFondoPausa;
		cResourceHandle mTexturaFondoCreditos;

		// Carga XML
		bool LoadXml(void);
};

