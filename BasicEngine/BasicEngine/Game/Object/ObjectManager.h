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
	

	private:
		bool LoadObjectsXml(std::string lsResource);
		void Tokenize(const string& str, vector<string>& tokens,  const string& delimiters);


	private:
		typedef std::vector<cObject *> cObjectList;
		cObjectList mObject;
		//Probablemente hay que hacer varias listas par alos diferentes tipos de objetos

		std::string msFilename;  // Resources or Properties file



};


#endif