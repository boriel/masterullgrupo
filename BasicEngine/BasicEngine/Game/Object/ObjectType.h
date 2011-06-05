/*
	Class cObectType: Con esta clase identificamos de que tipo es cada objeto para su posterior carga y gestion en la fisica, para colocarlo en el array correspondiente

*/

#ifndef OBJECT_TYPE_H
#define OBJECT_TYPE_H

#include <string>

using namespace std;

class cObjectType
{

	private:
		string msModelName;
		string msType;

	public:
		inline void SetType (string lsType) { msType = lsType; }
		inline string GetType () { return msType; }
		inline void SetModelName (string lsModelName) { msModelName = lsModelName; }
		inline string GetModelName () {return msModelName; }



};

#endif