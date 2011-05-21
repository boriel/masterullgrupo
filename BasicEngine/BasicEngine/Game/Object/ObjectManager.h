/*
class ObjectManager: Lista de objetos


*/

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>

#include "Object.h"
#include "..\..\Utility\Singleton.h"


class cObjectManager : public cSingleton<cObjectManager>
{
	
	public:
		friend class cSingleton<cObjectManager>;
		
		bool Init();
		void Deinit();
		void Render(cMatrix &lWorld);
		void Update(float lfTimestep);

	private:
		bool LoadObjectsXml(std::string lsResource);
		void Tokenize(const string& str, vector<string>& tokens,  const string& delimiters); //sacado de internet, un split de cadena!
		void CreandoTipoDeObjeto(cVec3 lPosition, string lsType, string lsModelName, string lsModelFile);

	private:
		typedef std::vector<cObject *> cObjectList;
		cObjectList mObject;  //Objetos en general que no se donde clasificarlos por ahora ....
		cObjectList mObjectPlayer;
		cObjectList mObjectPista;

		std::string msFilename;  // Resources or Properties file


};


#endif