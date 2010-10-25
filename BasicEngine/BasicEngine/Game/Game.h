/*
Clase Game. Representa nuestro juego e implementa una estructura o ciclo de vida como esta:
				Inicializacion - Update - Render - Destrucción
*/


#ifndef Game_H
#define Game_H

#include <stdio.h>

#include <tinystr.h>
#include <tinyxml.h>


#include "..\Utility\Singleton.h"

#include "..\Window\ApplicationProperties.h"
#include "..\Graphics\Camera.h"

//#include "InputConfiguration.h"
//#include "..\Input\InputManager.h"


class cGame : public cSingleton<cGame>
{
		friend class cSingleton<cGame>;
	

	private: 	//variables
		bool mbFinish;
		
		cApplicationProperties mProperties;
		
		string msFilename;  // Resources or Properties file
		TiXmlDocument mDoc;

		cCamera m3DCamera;
		
	protected:
		cGame () { ; } //Protected Constructor

	public:  //métodos

		bool Init(); // Function to initialize the game
		void Update(float lfTimestep); // Function to update the game
		void Render(); // Function to render the game
		bool Deinit(); // Function to deinitialize the game


		inline bool HasFinished() { return mbFinish; }  // Get if the game finished
		inline void SetFinished (bool lbValue) { mbFinish = lbValue; }
		

		void SetFilename (char* lsFilename);

	private:  //métodos
		
		void LoadResources(); //Read resources for the game (window properties)
		bool LoadPropertiesXML(const char* lacLevelFile);
		bool LoadTagConfigXML();


};

#endif