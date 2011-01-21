/*
Class cScene:


*/



#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "..\..\Utilities\Resource.h"
#include "..\..\Utilities\ResourceHandle.h"
#include "Object.h"

struct aiScene;
struct aiNode;


class cScene : public cResource
{
	public:
		cScene() { mbLoaded = false; }
	
		virtual bool Init( const std::string &lacNameID, const std::string &lacFile );
		virtual void Deinit();
		virtual bool IsLoaded() { return mbLoaded; }
		void Update( float lfTimestep );
		void Render();

		void ConvertNodesToObjects( aiNode *lpNode, cMatrix lTransform );
	
	private:
		std::string macFile;
		bool mbLoaded;

		typedef std::vector<cResourceHandle> cResourceHandleList;
		typedef cResourceHandleList::iterator cResourceHandleListIt;
		
		cResourceHandleList mMeshList;
		cResourceHandleList mMaterialList;
		
		std::vector<unsigned> mMeshMaterialIndexList; //un vector adicional en la clase escena que nos indicar� que material se debe usar para cada malla

		void ProcessScene( const aiScene* lpScene );
		
		typedef std::vector<cObject *> cObjectList;
		cObjectList mObjectList;
		
};


#endif