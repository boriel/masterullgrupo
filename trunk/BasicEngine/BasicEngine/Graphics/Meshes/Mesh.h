/*
Class cMesh:
	carga la malla desde la estructura que nos proporciona
	la librer�a Assimp y posteriormente c�mo almacenar la informaci�n de mallas en la
	tarjeta gr�fica.

*/


#ifndef MESH_H
#define MESH_H


#include <string>
#include "../../Utility/Resource.h"

struct aiMesh;

class cMesh : public cResource
{
	public:
		cMesh() { mbLoaded = false; }
		virtual bool Init( const std::string &lacNameID, void * lpMemoryData, int luiTypeID );
		virtual void Deinit();
		virtual bool IsLoaded() { return mbLoaded; }
		void RenderMesh();

		inline unsigned	getVertices() { return mVboVertices; }
		inline unsigned getIndex() { return mVboIndex; }

	
	private:
		unsigned muiIndexCount;  // n�mero de �ndices que contiene la malla
		bool mbLoaded;

		unsigned mVboVertices;
		unsigned mVboNormals;
		unsigned mVboIndex;
		unsigned mVboTexture;
};

#endif
