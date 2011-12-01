#ifndef __OBJECT_AGENT_H__
#define __OBJECT_AGENT_H__

#include "Object.h"
#include "Behaviour\Behaviour.h"
// Clase que define un objeto con comportamiento

class cObjectAgent: public cObject
{
protected:
    cBehaviour *mpActiveBehaviour;

public:
    inline void SetActiveBehaviour( cBehaviour *lpBehaviour ) { mpActiveBehaviour = lpBehaviour; }
	inline cBehaviour* GetActiveBehaviour() { return mpActiveBehaviour; }
    virtual void cObjectAgent::Update( float lfTimestep );
    virtual void Init();
};

#endif