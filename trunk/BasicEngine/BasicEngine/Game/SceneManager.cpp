#include "SceneManager.h"

bool cSceneManager::Init(){
	return true;
}

bool cSceneManager::Deinit(){
	return true;
}

void cSceneManager::Render(){

}

void cSceneManager::Update(float lfTimestep){
}

bool cSceneManager::LoadScene(Scenes lScene){
	mActualScene=lScene;
	if(lScene==Loading){
		cGame::Get().Render();
		cGame::Get().LoadRace();
	}
	if(lScene==Gameplay)NULL;
	if(lScene==MenuPrincipal)NULL;
	return true;
}