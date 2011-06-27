/*
Class: FPSCounter.

Con esto tenemos información de a que velocidada o Frame per Second se ve nuestro juego

*/


#ifndef FPSCOUNTER_H_
#define FPSCOUNTER_H_

#include "..\Utility\Singleton.h"


class cFPSCounter : public cSingleton<cFPSCounter>
{
	friend class cSingleton<cFPSCounter>;
	
	public:
		void Init();
		void Deinit();
		void Update(float lfTimestep);

		float GetFPS () { return mfFPS; }


	private:
    float mfUpdateInterval;
    float mfTimeSinceLastUpdate;
    float mfFrameCount;
    float mfFPS;
  
};





#endif