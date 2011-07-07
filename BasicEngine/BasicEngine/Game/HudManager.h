/*
class cHudManager: Controla el HUD.	Esta Clase se encargará de todas las muestras de texto en la pantalla
*/

#pragma once

#include "..\Utility\Singleton.h"
#include "..\Graphics\Fonts\acgfx_font.h"
#include <vector>

using namespace std;

struct tHud
{
	// Aquí estarán todas las cosas que se mostrarán al usuario mientras juega

	// En principio no hace falta id de Hud ya que solo utilizaremos uno para el jugador
	unsigned int muiNumActualLap; //Vuelta actual
	unsigned int muiNumTotalLaps; //Número de vueltas totales
	unsigned int muiPosition; //Posición actual en la carrera
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

		// Con esto mostraremos la pantalla de Hud de juego
		inline void ActivateHud(){mIsHudActive=true;}
		inline void DeactivateHud(){mIsHudActive=false;}

	private:
		string msFileName;
		// Lista de menús - PENDIENTE
		tHud mHud;
		bool mIsHudActive;
		cFont mFont; // La fuente con la que escribiremos los textos
		cResourceHandle mFontHandle;
		// Utilizaremos XML para la carga de menús - PENDIENTE
		bool LoadXml(void);
		void Tokenize(const string& str, vector<string>& tokens,  const string& delimiters);
};

