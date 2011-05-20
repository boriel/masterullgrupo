#include "ObjectPlayer.h"


void cObjectPlayer::Update( float lfTimestep )
{


	mPosition = mPosition + cVec3(-1.0, 0, 0);
	//Probando posiciones
	mWorldMatrix.SetPosition(mPosition);

	
}
