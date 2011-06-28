#include "FPSCounter.h"


void cFPSCounter::Init()
{
	mfUpdateInterval = 1.0f;
  mfTimeSinceLastUpdate = 0.0f;
  mfFrameCount = 0;
  mfFPS = 0;
}


void cFPSCounter::Deinit()
{

}


void cFPSCounter::Update(float lfTimestep)
{
  float lfElapsed = lfTimestep;
  mfFrameCount++;
  mfTimeSinceLastUpdate += lfElapsed;

  if (mfTimeSinceLastUpdate > mfUpdateInterval)
  {
		mfFPS = mfFrameCount / mfTimeSinceLastUpdate;
		mfFrameCount = 0;
		mfTimeSinceLastUpdate -= mfUpdateInterval;
	}

}
