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
		void Render();
		void Update(float lfTimestep);

		cVec3 GetPosition(const string lsType, const string lsModelName);
		cQuaternion GetRotacionInicial (const string lsType, const string lsModelName);
		cObject *GetObject(const string lsType, const string lsModelName);

	private:
		bool LoadObjectsXml(std::string lsResource);
		void LoadObjectsXmlCollision(const std::string lsResourceBuscar, const std::string lsType, cPhysicsObject* lpPhysicsObject);
		void Tokenize(const string& str, vector<string>& tokens,  const string& delimiters); //sacado de internet, un split de cadena!

	private:
		typedef std::vector<cObject *> cObjectList;
		cObjectList mObject;  //Objetos en general que no se donde clasificarlos por ahora .... (y por el final)
		cObjectList mObjectPlayer;
		cObjectList mObjectPista;
		cObjectList mObjectVehicle;  

		string msFilename;  // Resources or Properties file
		bool ExisteTipoAndModelName(string lsModelName, string lsType);
		float mfPI;
};


#endif