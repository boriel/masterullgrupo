/*
Class: TimeDebug

Esta clase es un singleton que implementa varios temporizadores
para ayudarnos medir los tiempo consumidos por diversas partes
del código.

*/

#ifndef TIME_DEBUG_H
#define TIME_DEBUG_H

#include "..\Utility\Singleton.h"
#include <string>
#include <vector>
using namespace std;

struct tTimer {
	unsigned long muiBegin;
	unsigned long muiEnd;
	string msDescription;
};

class cTimeDebug : public cSingleton<cTimeDebug> {
	friend class cSingleton<cTimeDebug>;
	
public:
	void Init(unsigned int luiSize);
	void Deinit();

	void StartTimer(unsigned int luiIndex, string lsDescription);
	float StopTimer(unsigned int luiIndex);
	void StopAndEchoTimer(unsigned int luiIndex);

private:
    vector<tTimer> mTimers;
};

#endif