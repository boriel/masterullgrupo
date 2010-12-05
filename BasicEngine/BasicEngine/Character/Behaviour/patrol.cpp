#include <stdlib.h>
#include <cassert>
#include "../../Lua/LuaManager.h"
#include "BehaviourManager.h"
#include "../CharacterManager.h"
#include "../../Game/Game.h"
#include "patrol.h"


void cPatrol::Init(cCharacter *lpCharacter)
{
	mpBehaviour = (cChaserWithOrientation *)cBehaviourManager::Get().CreateBehaviour(eCHASER_WITH_ORIENTATION);
	mpCharacter = lpCharacter;
	//mpCharacter->SetActiveBehaviour(mpBehaviour);	
	mTargetWayPoint = mpCharacter->GetPosition();
	mpBehaviour->Init(lpCharacter);
	mpBehaviour->SetTarget(mTargetWayPoint);
	miEnemyId = 0; // El 0 no existe como Id
	mfAwareRadius = 0;
}


void cPatrol::Deinit()
{
	mpBehaviour->Deinit();
	mpCharacter = NULL;
}


void cPatrol::Update(float lfTimestep)
{
	cCharacter *lpEnemyCharacter = cCharacterManager::Get().GetCharacter(miEnemyId);
	float lfDistance;
	
	if (lpEnemyCharacter != NULL) {
		lfDistance = mpCharacter->GetPosition().DistanceTo(lpEnemyCharacter->GetPosition());
		if (mfAwareRadius > lfDistance) // Está dentro del radio de acción? Pues lo perseguimos!
			SetTargetWayPoint(cCharacterManager::Get().GetCharacter(miEnemyId)->GetPosition());
		else // Si no, seguimos con el circuito, preguntando a LUA el punto actual
			cLuaManager::Get().CallLua<int, int>("CurrentEndPoint", mpCharacter->GetId());
	}

	if (!mpBehaviour->EndPointReached()) {
		mpBehaviour->Update(lfTimestep);
	} else { 
		// Comprobamos si hemos alcanzado al jugador
		if (lpEnemyCharacter != NULL && mpCharacter->GetPosition() == lpEnemyCharacter->GetPosition()) {
			cGame::Get().SetFinished(true);
			return;
		}
 		// Llamara función LUA que obtiene el nuevo punto
		cLuaManager::Get().CallLua<int, int>("NextEndPoint", mpCharacter->GetId());
	}	
}


void cPatrol::SetTargetWayPoint(const cVec3 &lTargetWayPoint)
{
	mTargetWayPoint = lTargetWayPoint;
	mpBehaviour->SetTarget(mTargetWayPoint);
}


void cPatrol::SetAwareRadius(float lfAwareRadius)
{
	if (lfAwareRadius >= 0)
		mfAwareRadius = lfAwareRadius;
}


void cPatrol::SetEnemyId(int liEnemyId)
{
	miEnemyId = liEnemyId;
}

