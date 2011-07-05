/*
class cSoundManager: Controla y maneja todos los sonidos que se utilizarán en el juego
					Después de inicializar la librería con AddSound registraremos el sonido y obtendremos el ID del buffer, para ejecutar el sonido utilizaremos Play(ID)

					-- ACTUALMENTE EN REFORMAS INTERNAS --
*/

#pragma once

#include "..\Utility\Singleton.h"
#include "..\Graphics\Fonts\acgfx_font.h"
#include <vector>
// OpenAL includes
#include"Framework\Framework.h"
using namespace std;

#define	PASOS		"Footsteps.wav"
#define SIRENA		"Sirena.wav"
#define ENTORNO		"Entorno.wav"
#define PLAYTIME	20
class cSoundManager :
	public cSingleton<cSoundManager>
{
public:
	public:	
		bool Init();
		bool Deinit();
		void Render();
		void Update(float lfTimestep); 
		void Play();
		void AddSound();
		// Con esto mostraremos la pantalla de Hud de juego
		/*inline void ActivateHud(){mIsHudActive=true;}
		inline void DeactivateHud(){mIsHudActive=false;}
		*/
	private:
		ALuint      uiBufferPasos;
		ALuint      uiSourcePasos;
		ALuint      uiBufferSirena;
		ALuint      uiSourceSirena;
		ALuint      uiBufferEntorno;
		ALuint      uiSourceEntorno;
		/*string msFileName;
		// Lista de menús - PENDIENTE
		tHud mHud;
		bool mIsHudActive;
		cFont mFont; // La fuente con la que escribiremos los textos
		cResourceHandle mFontHandle;
		// Utilizaremos XML para la carga de menús - PENDIENTE
		bool LoadXml(void);
		void Tokenize(const string& str, vector<string>& tokens,  const string& delimiters);*/
};

