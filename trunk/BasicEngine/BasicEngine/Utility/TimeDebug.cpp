#include "TimeDebug.h"
#include <Windows.h>
#include <iostream>

void cTimeDebug::Init(unsigned int luiSize) {
	mTimers.clear();
	for(unsigned int luiIndex=0; luiIndex<luiSize; ++luiIndex) {
		tTimer lTimer; 
		lTimer.muiBegin=0; lTimer.muiEnd=0; lTimer.msDescription="*";
		mTimers.push_back(lTimer);
	}
}

void cTimeDebug::Deinit() {
	mTimers.clear();
}

void cTimeDebug::StartTimer(unsigned int luiIndex, string lsDescription) {
	mTimers[luiIndex].muiBegin = timeGetTime();
	mTimers[luiIndex].muiEnd=0;
	mTimers[luiIndex].msDescription=lsDescription;
}

float cTimeDebug::StopTimer(unsigned int luiIndex) {
	mTimers[luiIndex].muiEnd = timeGetTime();
	float lfTimestep = ((float) (mTimers[luiIndex].muiEnd - mTimers[luiIndex].muiBegin) / 1000.0f);
	return lfTimestep;
}

void cTimeDebug::StopAndEchoTimer(unsigned int luiIndex) {
	float lfTimestep = StopTimer(luiIndex);
	cout<< "Timer("<<luiIndex<<", "<<mTimers[luiIndex].msDescription <<") = "<< lfTimestep << endl;
}