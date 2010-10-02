/*
Clase Game. Representa nuestro juego e implementa una estructura o ciclo de vida como esta:
				Inicializacion - Update - Render - Destrucción
*/


#ifndef Game_H
#define Game_H

#include <stdio.h>


#include "..\Utility\Singleton.h"

//using namespace std;

class cGame : public cSingleton<cGame>
{
		

		friend class cSingleton<cGame>;
	

	private: 	//variables
		bool mbFinished;
		bool mbCloseApplication;
	

	protected:
		cGame () { ; } //Protected Constructor

	public:  //métodos

		bool Init(); // Function to initialize the game
		void Update(float lfTimestep); // Function to update the game
		void Render(); // Function to render the game
		bool Deinit(); // Function to deinitialize the game


		inline bool HasFinished() { return mbFinished; }  // Get if the game finished
		inline void SetFinished (bool lbValue) { mbFinished = lbValue; }
		inline bool GetCloseApplicaton () { return mbCloseApplication; }

	private:  //métodos

};


#endif