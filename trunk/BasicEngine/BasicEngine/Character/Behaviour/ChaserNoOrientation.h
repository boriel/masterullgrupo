#ifndef CHASERNOORIENTATION_H
#define CHASERNOORIENTATION_H

#include "ChaserBase.h"

class cChaserNoOrientation: public cChaserBase {
protected:
	cVec3 lDistanceVec;  // Vector de distancia entre el objetivo y el personaje
	float lfDistance; // Distancia al cuadrado

public:
	virtual void Update(float lfTimestep);
};


#endif
