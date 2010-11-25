#ifndef CHASERWITHORIENTATION_H
#define CHASERWITHORIENTATION_H

#include "ChaserBase.h"

class cChaserWithOrientation: public cChaserBase {
protected:
	cVec3 lDistanceVec;  // Vector de distancia entre el objetivo y el personaje
	float lfDistance; // Distancia al cuadrado

public:
	virtual void Update(float lfTimestep);
};


#endif
