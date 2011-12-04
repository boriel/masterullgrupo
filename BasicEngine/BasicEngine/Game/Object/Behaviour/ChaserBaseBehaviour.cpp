#include "ChaserBaseBehaviour.h"

void cChaserBaseBehaviour::Init(cObjectAgent *lpCharacter)
{
	mpCharacter = lpCharacter;
}


void cChaserBaseBehaviour::SetTarget(const cVec3 &lTarget)
{
	mTarget = lTarget;
}