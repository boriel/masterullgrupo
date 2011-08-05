#include "FPSCounter.h"

void cFPSCounter::Init() {
	mfUpdateInterval = 1.0f;
	mfTimeSinceLastUpdate = 0.0f;
	mfFrameCount = 0;
	mfFPS = 0;
}

void cFPSCounter::Deinit() {

}

void cFPSCounter::Update(float lfTimestep) {
	mfFrameCount++;
	mfTimeSinceLastUpdate += lfTimestep;

	if (mfTimeSinceLastUpdate > mfUpdateInterval) {
		mfFPS = mfFrameCount / mfTimeSinceLastUpdate;
		mfFrameCount = 0;
		mfTimeSinceLastUpdate = 0.0f;
#ifdef _DAVID
		//Esta era la línea original, pero la cambio porque el cálculo no debe acumularse
		mfTimeSinceLastUpdate -= mfUpdateInterval;
#endif
	}
}
