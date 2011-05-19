#include "SkeletalCoreModel.h"

#include <tinystr.h>
#include <tinyxml.h>
#include <Windows.h>
#include <cassert>

#include "../GLHeaders.h"
#include "cal3d\cal3d.h"
#include "..\..\Utility\FileUtils.h"
#include "SkeletalMesh.h"
#include "../../MathLib/MathLib.h"



//El c�digo se limita a leer valores del XML y a hacer llamadas directas a Cal3D usando un CalCoreModel
bool cSkeletalCoreModel::Init( const std::string &lacNameID, const std::string &lacFile )
{
	macFile = lacFile;
	std::string lacBaseDirectory = cFileUtils::GetDirectory(lacFile);
	
	// Load the XML file
	TiXmlDocument doc( lacFile.c_str() );
	bool lbLoadOk = doc.LoadFile();
	if ( lbLoadOk )
	{
		OutputDebugString("XML Load: OK\n");
	}
	else
	{
		OutputDebugString("XML Load: FAILED\n");
		return false;
	}

	TiXmlHandle lhDoc(&doc);
	TiXmlElement* lpElem;
	TiXmlHandle lhRoot(0);

	lpElem = lhDoc.FirstChildElement().Element();
	assert(lpElem);

	// save this for later
	lhRoot = TiXmlHandle(lpElem);

	// Create the Cal3D Coremodel
	mpCoreModel = new CalCoreModel(lacNameID);
	// Obtain the Skeleton Path
	std::string lacSkeletonFile = lacBaseDirectory + lhRoot.ToElement()->Attribute("skeletonfile");
	
	// Load the skeleton
	bool lbIsOk = mpCoreModel->loadCoreSkeleton(lacSkeletonFile);
	assert(lbIsOk);
	
	// Read all the animations
	lpElem=lhRoot.FirstChild( "Animation" ).Element();
	for (lpElem; lpElem; lpElem = lpElem->NextSiblingElement("Animation"))
	{
		sAnimationDef lDefinition;
		lDefinition.macAnimationFile = lacBaseDirectory +
		lpElem->Attribute("file");
		lDefinition.macName = lpElem->Attribute("name");
		std::string lacType = lpElem->Attribute("type");
		if (lacType.length() > 0 && (lacType[0] == 'A' ||	lacType[0] == 'a'))
		{
			// It�s an action
			lDefinition.meAnimType = eAnimType_Action;
		}
		else
		{
			// It�s a cycle
			lDefinition.meAnimType = eAnimType_Cycle;
		}

		// Load the animation in the coremodel
		lDefinition.miAnimID=mpCoreModel->loadCoreAnimation(lDefinition.macAnimationFile,	lDefinition.macName);
		assert( lDefinition.miAnimID >= 0 );
		// Store the animation info for later
		mAnimationDefs.push_back(lDefinition);
	}

	// Read all the meshes
	lpElem=lhRoot.FirstChild( "Mesh" ).Element();
	for( lpElem; lpElem; lpElem = lpElem->NextSiblingElement("Mesh"))
	{
		std::string lacFile = lacBaseDirectory + lpElem->Attribute("file");
		// Load the mesh into Cal3D
		int liMeshIndex = mpCoreModel->loadCoreMesh(lacFile);
		assert(liMeshIndex >= 0);
		// Store the mesh index
		mMeshIndexes.push_back(liMeshIndex);
	}

	
	CreateBuffers();


	return true;
}

void cSkeletalCoreModel::Deinit()
{
	
	if (mpCoreModel)
	{
		ReleaseBuffers();  //no se si va aqui o antes del if
		delete mpCoreModel;
		mpCoreModel = NULL;
	}
}

void cSkeletalCoreModel::CreateInstance( cSkeletalMesh * lpMesh )
{
	// Create the CalModel instance
	assert(lpMesh);
	lpMesh->mpCal3DModel = new CalModel(mpCoreModel);
	lpMesh->mpCoreModel = this;

	// Attach the meshes in the instance
	std::list<int>::iterator it = mMeshIndexes.begin();
	while (it != mMeshIndexes.end())
	{
		lpMesh->mpCal3DModel->attachMesh( *it );
		++it;
	}

}


sAnimationDef * cSkeletalCoreModel::GetAnimationDef(const std::string lacAnim)
{
	// Look for the animation
	std::list<sAnimationDef>::iterator it = mAnimationDefs.begin();

	while (it != mAnimationDefs.end())
	{
		std::string lacName = it->macName;
		
		if ( lacName == lacAnim )
			return &(*it);
		
		++it;
	}

	return NULL;
}


void cSkeletalCoreModel::CreateBuffers()
{
	int luiNumMeshes = mpCoreModel->getCoreMeshCount();
	unsigned luiVertexCount = 0;
	unsigned luiFaceCount = 0;
	unsigned luiTextCoordCount = 0;
	
	//Calculate the number of vertices, indexes and texture coordinates
	for (int liIndexMesh = 0; liIndexMesh < luiNumMeshes; ++liIndexMesh)
	{
		CalCoreMesh * lpCoreMesh = mpCoreModel->getCoreMesh(liIndexMesh);
		assert( lpCoreMesh );
		int liNumSubMeshes = lpCoreMesh->getCoreSubmeshCount();

		// For all submeshes
		for (int liIndexSubMesh=0;liIndexSubMesh<liNumSubMeshes; ++liIndexSubMesh)
		{
			CalCoreSubmesh *lpCoreSubMesh = lpCoreMesh->getCoreSubmesh(	liIndexSubMesh );
			assert( lpCoreSubMesh );
			luiVertexCount += lpCoreSubMesh->getVertexCount( );
			luiFaceCount += lpCoreSubMesh->getFaceCount();
			const std::vector< std::vector< CalCoreSubmesh::TextureCoordinate > >	&lTextureCoords = lpCoreSubMesh->	getVectorVectorTextureCoordinate();
			luiTextCoordCount =	(lTextureCoords.size() > luiTextCoordCount)? lTextureCoords.size() : luiTextCoordCount;
		}
	}

	//En el c�digo anterior se recorren todas las mallas y submallas que contiene el modelo
	//de Cal3D y se suman sus v�rtices e �ndices. Adem�s se calcula el m�ximo de
	//coordenadasde textura que se necesitan. Una vez tenemos esas cantidades, tenemos
	//que inicializar una serie de buffers en memoria del juego para extraer esa informaci�n
	//para m�s tarde poder pas�rsela a la GPU:

	// Create the buffers
	cVec3* laPositionBuffer = new cVec3[luiVertexCount];
	cVec3* laNormalBuffer = new cVec3[luiVertexCount];
	cVec4* laBoneIndexes = new cVec4[luiVertexCount];
	unsigned char* laWeights = new unsigned char[luiVertexCount * 4];
	cVec2** laaTextureBuffer = new cVec2*[luiTextCoordCount];
	
	for (unsigned luiIndex = 0; luiIndex < luiTextCoordCount; ++luiIndex)
		laaTextureBuffer[luiIndex] = new cVec2[luiVertexCount];
	
	muiIndexCount = luiFaceCount * 3;
	unsigned* lauiIndexBuffer = new unsigned[muiIndexCount];
	
	//A continuaci�n inicializaremos estos buffers recorriendo cada una de las submallas y
	//extraendo dicha informaci�n:

	// Load the vertex and index information
	unsigned luiVertexIndex = 0;
	unsigned luiIndexesIndex = 0;
	unsigned luiVertexAnt = 0;

	// For all the meshes
	for (int liIndexMesh = 0; liIndexMesh < luiNumMeshes; ++liIndexMesh)
	{
		CalCoreMesh * lpCoreMesh = mpCoreModel->getCoreMesh(liIndexMesh);
		int luiCoreSubMeshesCount = lpCoreMesh->getCoreSubmeshCount();
		// For all submeshes
		for (int liIndexSubMesh= 0; liIndexSubMesh < luiCoreSubMeshesCount;	++liIndexSubMesh)
		{
			CalCoreSubmesh *lpCoreSubMesh =	lpCoreMesh->getCoreSubmesh( liIndexSubMesh );
			int luiSkinVertexCount = lpCoreSubMesh->getVertexCount( );
			// For all the vertex
			for(int liIndex = 0; liIndex < luiSkinVertexCount; ++liIndex )
			{
				const CalCoreSubmesh::Vertex &cv = lpCoreSubMesh->getVectorVertex( )[ liIndex ];
	
				// Read Vertex Normals and Position
				laPositionBuffer[luiVertexIndex].x = cv.position.x;
				laPositionBuffer[luiVertexIndex].y = cv.position.y;
				laPositionBuffer[luiVertexIndex].z = cv.position.z;
				laNormalBuffer[luiVertexIndex].x = cv.normal.x;
				laNormalBuffer[luiVertexIndex].y = cv.normal.y;
				laNormalBuffer[luiVertexIndex].z = cv.normal.z;
	
				// Initialize Vertex Weights and BoneIndex
				for( int j = 0; j < 4; ++j )
				{
					laWeights[ luiVertexIndex * 4 + j ] = 0;
					laBoneIndexes[luiVertexIndex][ j ] = 0;
				}
	
				for(size_t j=0;j< cv.vectorInfluence.size( ); ++j )
				{
					const CalCoreSubmesh::Influence &influence = cv.vectorInfluence[ j ];
					laWeights[ luiVertexIndex * 4 + j ] =	(unsigned char)(influence.weight * 255.0f);
					laBoneIndexes[luiVertexIndex][ j ] =	(float)influence.boneId;
				}
	
				// Read Texture Coordinates
				const std::vector< std::vector< CalCoreSubmesh::TextureCoordinate > >	&laTexturesCoord = lpCoreSubMesh->getVectorVectorTextureCoordinate();
				for (unsigned luiTexIndex = 0; luiTexIndex < laTexturesCoord.size(); ++luiTexIndex)
				{
					const CalCoreSubmesh::TextureCoordinate &lCoord	= laTexturesCoord[luiTexIndex][luiVertexIndex];
					laaTextureBuffer[luiTexIndex][luiVertexIndex].x =	lCoord.u;
					laaTextureBuffer[luiTexIndex][luiVertexIndex].y = lCoord.v;
				}
				luiVertexIndex++;
			}

			// Calculate indices
			unsigned luiFaceCount = lpCoreSubMesh->getFaceCount();
			const std::vector<CalCoreSubmesh::Face> &lFaces = lpCoreSubMesh->getVectorFace();
				for (unsigned luiIndex = 0; luiIndex < luiFaceCount; ++luiIndex)
				{
					const CalCoreSubmesh::Face &lFace = lFaces[luiIndex];
					lauiIndexBuffer[ luiIndexesIndex++ ] = lFace.vertexId[0] +	luiVertexAnt;
					lauiIndexBuffer[ luiIndexesIndex++ ] = lFace.vertexId[1] +	luiVertexAnt;
					lauiIndexBuffer[ luiIndexesIndex++ ] = lFace.vertexId[2] +	luiVertexAnt;
					assert(lauiIndexBuffer[ luiIndexesIndex - 1 ] < luiVertexCount);
					assert(lauiIndexBuffer[ luiIndexesIndex - 2 ] < luiVertexCount);
					assert(lauiIndexBuffer[ luiIndexesIndex - 3 ] < luiVertexCount);
				}
			luiVertexAnt = luiVertexIndex;
		}
	}

	assert( luiVertexIndex == luiVertexCount );

	//El c�digo anterior extrae toda la informaci�n de las mallas de Cal3D y la distribuye en
	//un buffer distinto dependiendo del tipo de dato. Una vez que tenemos toda la
	//informaci�n, pasamos a la creaci�n y rellenado de los buffers de OpenGL:

	// Create the GPU buffers
	//----------------------------------------------------------------------------------------------------
	// Get the number of texture coordinates
	unsigned luiTextureCoordinateCount = luiTextCoordCount;
	assert(luiTextureCoordinateCount <= 3);
	maVboTexture.resize(luiTextureCoordinateCount);
	glGenBuffers(1, &mVboVertices);
	assert(glGetError() == GL_NO_ERROR);
	// Creating all the texture coordinate buffers
	for(unsigned luiIndex = 0; luiIndex < luiTextureCoordinateCount; ++luiIndex)
	{
		glGenBuffers(1, &maVboTexture[luiIndex]);
		assert(glGetError() == GL_NO_ERROR);
	}

	glGenBuffers(1, &mVboNormals);
	assert(glGetError() == GL_NO_ERROR);
	glGenBuffers(1, &mVboWeight);
	assert(glGetError() == GL_NO_ERROR);
	glGenBuffers(1, &mVboBoneIx);
	assert(glGetError() == GL_NO_ERROR);
	glGenBuffers(1, &mVboIndex);

	assert(glGetError() == GL_NO_ERROR);

	// Send the buffers to GPU
	//----------------------------------------------------------------------------------------------------
	
	// Position
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	assert(glGetError() == GL_NO_ERROR);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * luiVertexCount,	laPositionBuffer, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);
	
	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
	assert(glGetError() == GL_NO_ERROR);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * luiVertexCount,	laNormalBuffer, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);
	
	// Textures
	for(unsigned luiTexCoordChannel = 0; luiTexCoordChannel <	luiTextureCoordinateCount; ++luiTexCoordChannel)
	{
		glBindBuffer(GL_ARRAY_BUFFER, maVboTexture[luiTexCoordChannel]);
		assert(glGetError() == GL_NO_ERROR);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 *	luiVertexCount,	laaTextureBuffer[luiTexCoordChannel],	GL_STATIC_DRAW);
		assert(glGetError() == GL_NO_ERROR);
	}

	// Weights (Color Channel)
	glBindBuffer(GL_ARRAY_BUFFER, mVboWeight);
	assert(glGetError() == GL_NO_ERROR);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned char) * 4 *
	luiVertexCount,
	laWeights, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);
	
	// Bone IDs
	glBindBuffer(GL_ARRAY_BUFFER, mVboBoneIx);
	assert(glGetError() == GL_NO_ERROR);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * luiVertexCount,	laBoneIndexes, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);
	
	// Index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIndex);
	assert(glGetError() == GL_NO_ERROR);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, muiIndexCount *	sizeof(unsigned), lauiIndexBuffer, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);
	
	//Como se puede comprobar, los buffers se crean y rellenan de la misma forma que en la
	//clase cMesh. Con esto ya hemos acabado pr�cticamente, s�lo nos queda liberar la
	//memoria de los buffers intermedios que usamos para extraer la informaci�n de Cal3D.
	
	// Delete Buffers
	// ----------------------------------------------------------------
	delete laPositionBuffer;
	delete laNormalBuffer;
	delete laBoneIndexes;
	delete laWeights;
	
	for (unsigned luiIndex=0; luiIndex < luiTextCoordCount; ++luiIndex)
		delete laaTextureBuffer[luiIndex];
	
	delete laaTextureBuffer;
	delete lauiIndexBuffer;
}


void cSkeletalCoreModel::ReleaseBuffers()
{
	glDeleteBuffers(1, &mVboBoneIx);
	glDeleteBuffers(1, &mVboWeight);
	glDeleteBuffers(1, &mVboVertices);
	
	for( unsigned luiTexCoordChannel = 0;	luiTexCoordChannel<maVboTexture.size(); ++luiTexCoordChannel)
		glDeleteBuffers(1, &maVboTexture[luiTexCoordChannel]);
	
	glDeleteBuffers(1, &mVboNormals);
	glDeleteBuffers(1, &mVboIndex);
}