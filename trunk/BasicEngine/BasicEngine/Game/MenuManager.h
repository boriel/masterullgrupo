/*
class cMenuManager: Controla los menús. Tanto el inicial como el de pausa en medio de la partida.
					Posible actualización: Cargar los menús de XML.
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

// Se usarán para saber qué hace el elemento del menú
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
	// Aquí tendremos los diferentes items del menú
	std::string msMenuItem; // Identificador del item
	Action mAction;
	tMenu *mTarget; // En caso de Abrir, necesitamos saber qué abrir.
	// Necesitaremos tipos de comportamiento para saber
	// qué tipo de acción realizará el item:
	// Abrir otro menu, Cerrar Juego, Empezar juego...
};

struct tMenu
{
	// Aquí tendremos los diferentes menús
	std::string msMenuName; //Identificador del Menú
	unsigned int muiNumItems; //Número de elementos
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
		void AbrirMenu(); // Haremos la acción apropiada con cada elemento del menú
		inline void IniciarMenu(){mMenuActual = mMenuPrincipal;muiSelectedItem=1;}
		void MenuPausa(){mMenuActual=mMenuPausa;}
		inline void SetAviso(bool lParpadeo){mAviso=lParpadeo;}
	private:
		string msFileName;
		// Menús Iniciales
		tMenu *mMenuActual;

		tMenu *mMenuPrincipal;
		tMenu *mMenuJugar;
		tMenu *mMenuOpciones;
		tMenu *mMenuPartidaLibre;
		tMenu *mConfirmacion; // Pequeño menú para decisiones que requieran "si/no"
		// Menú Pausa inGame
		tMenu *mMenuPausa;

		// Variables de estética
		unsigned int muiSelectedItem;
		unsigned int muiDistanceBWItems; // Selecciona la distancia entre dos menuitems
		bool mParpadeo; // Dará efecto de parpadear a ciertos elementos
		unsigned int mTiempoParpadeo;
		bool mAviso;

		// Sonidos
		Sound *mAceptarSound;
		Sound *mAtrasSound;
		Sound *mMusicaMenu;
		Sound *mMusicaCreditos;
		mSoundBank mMoves_SoundBank; // Añadiremos todos los sonidos para los movimientos, de manera que podamos ejecutarlos aleatoriamente
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

