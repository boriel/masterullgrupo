/*
class cHudManager: Controla el HUD y la gesti�n de los men�s
					Esta Clase se encargar� de todas las muestras de texto en la pantalla
*/

#pragma once

#include "..\Utility\Singleton.h"
#include "..\Graphics\Fonts\acgfx_font.h"
#include <vector>

using namespace std;

// ----------------- MENUS PENDIENTES -------------------
struct tMenuItem
{
	// Aqu� tendremos los diferentes items del men�
	std::string msMenuItem; // Identificador del item
	// Necesitaremos tipos de comportamiento para saber
	// qu� tipo de acci�n realizar� el item:
	// Abrir otro menu, Cerrar Juego, Empezar juego...
};

struct tMenu
{
	// Aqu� tendremos los diferentes men�s
	std::string msMenuName; //Identificador del Men�
	unsigned int muiNumItems; //N�mero de elementos
	typedef std::vector<tMenuItem *> mItemsList;
};
// -------------------------------------------------------

struct tHud
{
	// Aqu� estar�n todas las cosas que se mostrar�n al usuario mientras juega

	// En principio no hace falta id de Hud ya que solo utilizaremos uno para el jugador
	unsigned int muiNumActualLap; //Vuelta actual
	unsigned int muiNumTotalLaps; //N�mero de vueltas totales
	unsigned int muiPosition; //Posici�n actual en la carrera
};

class cHudManager :
	public cSingleton<cHudManager>
{
public:
	public:	
		bool Init(string lsFilename);
		void Deinit();
		void Render();
		void Update(float lfTimestep); 

	private:
		string msFileName;
		// Lista de men�s - PENDIENTE
		tHud mHud;
		bool mIsHudActive;
		cFont mFont; // La fuente con la que escribiremos los textos
		cResourceHandle mFontHandle;
		// Utilizaremos XML para la carga de men�s - PENDIENTE
		bool LoadXml(void);
		void Tokenize(const string& str, vector<string>& tokens,  const string& delimiters);
};

