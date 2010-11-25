#ifndef CHASERSNAPORIENTATION_H
#define CHASERSNAPORIENTATION_H

#include "ChaserNoOrientation.h"

class cChaserSnapOrientation: public cChaserNoOrientation {
public:
	virtual void Update(float lfTimestep);
};


#endif
