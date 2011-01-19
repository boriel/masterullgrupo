/*
Class cCharacterManager: Se encargará de gestionar los personajes del juego.


*/


#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

#include <list>

#include "..\Utility\Singleton.h"

#include "Character.h"



class cCharacterManager : public cSingleton<cCharacterManager>
{
	friend class cSingleton<cCharacterManager>;

	protected:
		cCharacterManager() { ; } // Protected constructor
	
	private:
		typedef std::list<cCharacter *> cCharacterList;
		typedef cCharacterList::iterator cCharacterListIt;
		cCharacterList mCharacters; //Lista de personajes
		int miIdCounter; // Contador de instancias de personaje. Se usará para ir generando ID's

	public:
		
		bool Init();
		
		void Update( float lfTimestep ); //Llama al Update de todos personajes
		
		void Render(); //Llama al Render de todos personajes
		
		bool Deinit(); //Llama al Deinit de todos personajes

		cCharacter *GetCharacter(int liId); // Devuelve el personaje dado su ID
		
		//Crea un nuevo personaje, llama a su Init() y lo añade a la lista.
		//Devuelve un puntero al personaje creado
		cCharacter* CreateCharacter();
		
		void DestroyCharacter(cCharacter* lpCharacter); //Elimina al personaje de la lista y llama a su Deinit()

};







#endif