/*
Class cScene:


*/



#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "..\..\Utilities\Resource.h"
#include "..\..\Utilities\ResourceHandle.h"


struct aiScene;

class cScene : public cResource
{
	public:
		cScene() { mbLoaded = false; }
	
		virtual bool Init( const std::string &lacNameID, const std::string &lacFile );
		virtual void Deinit();
		virtual bool IsLoaded() { return mbLoaded; }
		void Update( float lfTimestep );
		void Render();
	
	private:
		std::string macFile;
		bool mbLoaded;

		typedef std::vector<cResourceHandle> cResourceHandleList;
		typedef cResourceHandleList::iterator cResourceHandleListIt;
		cResourceHandleList mMeshList;

		void ProcessScene( const aiScene* lpScene );
};


#endif
