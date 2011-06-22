/*
Class cMesh:
	carga la malla desde la estructura que nos proporciona
	la librería Assimp y posteriormente cómo almacenar la información de mallas en la
	tarjeta gráfica.

*/

#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include "..\..\Utility\Resource.h"
#include "..\..\Utility\ResourceHandle.h"

//constantes que identifican si la malla es de tipo estática o esqueletal
static int kuiStaticMesh = 0;
static int kuiSkeletalMesh = 1;

struct aiMesh;
struct cVec3;

class cMesh : public cResource
{
	public:
		cMesh() { mbLoaded = false; }
		//virtual bool Init( const std::string &lacNameID, void * lpMemoryData, int luiTypeID );  //cambio el nombre ultimo valor, imaigno que no será importante
		virtual bool Init( const std::string &lacNameID, void * lpMemoryData, int liDataType );
		void Reload( void * lpMemoryData );
		virtual void Deinit();
		virtual bool IsLoaded() { return mbLoaded; }
		virtual void RenderMesh();
		virtual void Update(float lfTimestep) {}

		//Estos dos inline los borro en la pag 59 de los apuntes, no están
		//inline unsigned	getVertices() { return mVboVertices; }
		//inline unsigned getIndex() { return mVboIndex; }

		virtual void PrepareRender(cResourceHandle lMaterial) { ; }

		cVec3 *mpVertexPositionBuffer;
		unsigned muiNumVertex;

	protected:
		std::string macNameID;
		unsigned muiIndexCount;  // número de índices que contiene la malla
		bool mbLoaded;

		unsigned mVboVertices;
		unsigned mVboNormals;
		unsigned mVboIndex;
		//unsigned mVboTexture; //cambiado esto por un stl vector
		std::vector<unsigned> maVboTexture;
};

#endif
