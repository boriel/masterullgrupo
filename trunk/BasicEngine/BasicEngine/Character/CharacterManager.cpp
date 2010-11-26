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
bool cCharacterManager::Deinit()
{
	for (cCharacterListIt i = mCharacters.begin(); i != mCharacters.end(); i++) {
		(*i)->Deinit();
	}

	return true;
}


cCharacter* cCharacterManager::CreateCharacter()
{
	cCharacter *result = new cCharacter();
	assert(result);
	mCharacters.push_back(result);

	return result;
}
