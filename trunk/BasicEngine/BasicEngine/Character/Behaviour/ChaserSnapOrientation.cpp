#include "ChaserSnapOrientation.h"

void cChaserSnapOrientation::Update(float lfTimestep)
{
	// Llamamos al método de la clase padre que realiza la persecución
	// Esto además, establecerá los valores del vector de distancia y de lfDistance
	cChaserNoOrientation::Update(lfTimestep);

	//Una vez el perseguidor se haya movido (ver comportamiento anterior),
	//debemos orientarlo. Para orientarlo hay que modificar el Yaw del
	//perseguidor de la //siguiente forma:
	if (lfDistance > 0.001f)
	{
		mpCharacter->SetYaw(atan2f(lDistanceVec.x, lDistanceVec.z));
	}
}
