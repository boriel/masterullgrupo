#include "CharacterManager.h"


bool cCharacterManager::Init()
{
	return true;
}


//Llama al Update de todos personajes
void cCharacterManager::Update( float lfTimestep )
{
	for (cCharacterListIt i = mCharacters.begin(); i != mCharacters.end(); i++) {
		(*i)->Update(lfTimestep);
	}
}


//Llama al Render de todos personajes
void cCharacterManager::Render()
{
	for (cCharacterListIt i = mCharacters.begin(); i != mCharacters.end(); i++) {
		(*i)->Render();
	}
}
		

//Llama al Deinit de todos personajes
//Y los elimina de la memoria

bool cCharacterManager::Deinit()
{
	while (!mCharacters.empty()) {
		(*mCharacters.begin())->Deinit();
		DestroyCharacter(*mCharacters.begin());
	}

	return true;
}



void cCharacterManager::DestroyCharacter(cCharacter *lpCharacter)
{
	for (cCharacterListIt i = mCharacters.begin(); i != mCharacters.end(); i++) {
		if ((*i) == lpCharacter) {
			mCharacters.erase(i);
			break;
		}
	}
}



cCharacter* cCharacterManager::CreateCharacter()
{
	cCharacter *result = new cCharacter();
	assert(result);
	mCharacters.push_back(result);

	return result;
}
