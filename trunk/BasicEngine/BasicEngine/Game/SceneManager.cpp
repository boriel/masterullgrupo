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

bool cSceneManager::LoadScene(eScenes lScene){
	mActualScene=lScene;
	if(lScene==eLoading){
		cGame::Get().Render();
		cGame::Get().LoadRace();
	}
	if(lScene==eNoDisponible){
		cGame::Get().Render();
	}
	//if(lScene==eGameplay) {};
	//if(lScene==eMenuPrincipal) {};
	return true;
}