/*
Class cMesh:
	carga la malla desde la estructura que nos proporciona
	la librería Assimp y posteriormente cómo almacenar la información de mallas en la
	tarjeta gráfica.

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
		unsigned muiIndexCount;  // número de índices que contiene la malla
		bool mbLoaded;

		unsigned mVboVertices;
		unsigned mVboNormals;
		unsigned mVboIndex;
		unsigned mVboTexture;
};

#endif
