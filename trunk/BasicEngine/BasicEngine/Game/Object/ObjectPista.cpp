#include "ObjectPista.h"



cObjectPista::cObjectPista (cObject lObject)
{
	Init (lObject.GetPosition(), lObject.GetType(), lObject.GetModelName(), lObject.GetModelFile());

}

void cObjectPista::Update( float lfTimestep )
{


	mPosition = mPosition + cVec3(-1.0, 0, 0);
	//Probando posiciones
	mWorldMatrix.SetPosition(mPosition);

	
}
