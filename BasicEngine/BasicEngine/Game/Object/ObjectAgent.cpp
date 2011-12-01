#include "ObjectAgent.h"

void cObjectAgent::Update( float lfTimestep )
{
 //   cObject::Update(lfTimestep);

	if (mpActiveBehaviour != NULL)
		mpActiveBehaviour->Update(lfTimestep);
}


void cObjectAgent::Init()
{
    cObject::Init();
    mpActiveBehaviour = NULL; // Ningún comportamiento
}
