
#include "Mesh.h"
#include "..\..\Game\Object\ObjectManager.h"

#include "../GLHeaders.h"
#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>
#include <iostream>
#include "..\..\MathLib\Vec\Vec3.h"
#include "..\..\MathLib\MathLib.h"

bool cMesh::Init (const std::string &lacNameID, void* lpMemoryData, int luiTypeID)
{
	macNameID = lacNameID;

	//En primer lugar crearemos el buffer de índices
	aiMesh* lpAiMesh = (aiMesh*)lpMemoryData;
	// Get the number of texture coordinates
	unsigned luiTextureCoordinateCount = lpAiMesh->GetNumUVChannels();
	assert(luiTextureCoordinateCount <= 4);
	maVboTexture.resize(luiTextureCoordinateCount);

	glGenBuffers(1, &mVboVertices);
	assert(glGetError() == GL_NO_ERROR);
	
	// Creating all the texture coordinate buffers
	for(unsigned luiIndex = 0; luiIndex < luiTextureCoordinateCount; ++luiIndex)
	{
		glGenBuffers(1, &maVboTexture[luiIndex]);
		assert(glGetError() == GL_NO_ERROR);
	}

	//Una vez que hemos creado el buffer,
	//debemos indicarle a OpenGL que las siguientes llamadas se refieren al buffer de
	//vértices, por lo que ejecutamos:
	//Position
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	assert(glGetError() == GL_NO_ERROR);

	//TODO: Pruebas de escalado
	float lfScale = cObjectManager::Get().GetScale();

	for (unsigned int luiIndex=0; luiIndex<lpAiMesh->mNumVertices; ++luiIndex) {
		lpAiMesh->mVertices[luiIndex].x=lpAiMesh->mVertices[luiIndex].x*lfScale;
		lpAiMesh->mVertices[luiIndex].y=lpAiMesh->mVertices[luiIndex].y*lfScale;
		lpAiMesh->mVertices[luiIndex].z=lpAiMesh->mVertices[luiIndex].z*lfScale;
	}

	//Y por último inicializamos el buffer con la siguiente llamada:
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * lpAiMesh->mNumVertices,	lpAiMesh->mVertices, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);


	//Almacenamos todos los vértices del Mesh
	muiNumVertex = lpAiMesh->mNumVertices; 
	mpVertexPositionBuffer = new cVec3[muiNumVertex];
	memcpy(mpVertexPositionBuffer, lpAiMesh->mVertices, sizeof(float) * 3 * muiNumVertex);

	//ProcessBoundingMesh();  //No se si este es el mejor lugar

	//El primer parámetro de la llamada le indica a OpenGL que es un array buffer normal y
	//no uno de índices. A continuación se le indica cuanta memoria tiene que copiar en el
	//buffer, por lo que se multiplica el número de vértices por el número de flotantes que
	//tiene cada vértice (X, Y, Z) por el tamaño que tiene un flotante, todo esto junto da la
	//cantidad de bytes que se deben copiar. El tercer parámetro es el comienzo de la
	//memoria donde se encuentran los vértices dentro de la estructura de la escena (en este
	//caso la estructura encaja con lo que necesitamos, ya que es una array de posiciones X,
	//Y, Z). El último parámetro le indica a la tarjeta gráfica que el buffer se debe almacenar
	//en memoria de video y que la aplicación no accederá directamente al buffer para
	//modificar los datos que hay en él contenidos. Con esto ya tenemos listo el buffer de
	//posiciones. El buffer de normales es bastante similar:
	
	glGenBuffers(1, &mVboNormals);
	assert(glGetError() == GL_NO_ERROR);
	
	//Normals
	// Check that the mesh has normals
	assert(lpAiMesh->HasNormals());
	glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
	assert(glGetError() == GL_NO_ERROR);
	glBufferData(GL_ARRAY_BUFFER,	sizeof(float) * 3 * lpAiMesh->mNumVertices,	lpAiMesh->mNormals, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);

	//El código anterior muestra un error si la malla no cuenta con normales
	//Al igual que en el caso de las posiciones,
	//las normales están convenientemente almacenadas en la escena, por lo que la
	//inicialización del buffer es bastante simple. Esto no sucede con las coordenadas de
	//textura, por lo que tenemos que componer primero el buffer en memoria:

	// Reading all the texture coordinate
	unsigned luiTexCoordNum = lpAiMesh->mNumVertices;
	unsigned luiTexCoordFloats = 2 * luiTexCoordNum;
	float* lpTexCoordinates = new float[ luiTexCoordFloats ];
	for(unsigned luiTexCoordChannel = 0; luiTexCoordChannel < luiTextureCoordinateCount; ++luiTexCoordChannel)
	{
		unsigned luiInc = 0;
		for ( unsigned luiTexIndex = 0;	luiTexIndex < luiTexCoordNum; ++luiTexIndex )
		{
			lpTexCoordinates[luiInc++] =
			lpAiMesh->mTextureCoords[luiTexCoordChannel][luiTexIndex].x;
			lpTexCoordinates[luiInc++] = (1.0f -
			lpAiMesh->mTextureCoords[luiTexCoordChannel][luiTexIndex].y);
			// OpenGL Correction
		}
		glBindBuffer(GL_ARRAY_BUFFER, maVboTexture[luiTexCoordChannel]);
		assert(glGetError() == GL_NO_ERROR);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * luiTexCoordFloats,
		lpTexCoordinates, GL_STATIC_DRAW);
		assert(glGetError() == GL_NO_ERROR);
	}
	delete [] lpTexCoordinates;



	/* Se elimino al cambio  de vecctores de las coordenadas

	assert(lpAiMesh->HasTextureCoords(0));
	unsigned luiTexCoordNum = lpAiMesh->mNumVertices;
	unsigned luiTexCoordFloats = 2 * luiTexCoordNum;
	float* lpTexCoordinates = new float[ luiTexCoordFloats ];
	unsigned luiIndex = 0;
	for ( unsigned luiTexIndex=0;luiTexIndex<luiTexCoordNum;++luiTexIndex)
	{
		lpTexCoordinates[luiIndex++] = lpAiMesh->mTextureCoords[0][luiTexIndex].x;
		lpTexCoordinates[luiIndex++] = (1.0f - lpAiMesh->mTextureCoords[0][luiTexIndex].y);
	}


	//El código anterior crea el buffer en memoria con los datos en la distribución que
	//necesitamos. Si nos fijamos, estamos aplicando una conversión a las coordenadas Y de
	//la textura. Esto es porque OpenGL y DirectX tienen invertidos entre sí este parámetro.
	//Por lo que es necesario invertirlo para que se muestre correctamente. Una vez que
	//tenemos el buffer, se aplica un código similar al ya visto con las posiciones y las
	//normales:

	glGenBuffers(1, &mVboTexture);
	assert(glGetError() == GL_NO_ERROR);
	glBindBuffer(GL_ARRAY_BUFFER, mVboTexture);
	assert(glGetError() == GL_NO_ERROR);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * luiTexCoordFloats,
	lpTexCoordinates, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);

	delete [] lpTexCoordinates;


	//El código mostrado sólo considera que hay un juego de coordenadas de texturas, si
	//hubiera más, habría que repetir este código por cada juego de coordenadas. Ya sólo nos
	//queda la carga del buffer de índices, que también nos fuerza a componer primero el
	//buffer en memoria:
	*/

	// Index
	muiIndexCount = lpAiMesh->mNumFaces * 3;
	unsigned* lpIndex = new unsigned[ muiIndexCount ];
	
	unsigned luiIndex = 0;
	for(unsigned luiFaceIndex=0;luiFaceIndex<lpAiMesh->mNumFaces;++luiFaceIndex )
	{
		// Make sure that each face has 3 vertex
		assert(lpAiMesh->mFaces[luiFaceIndex].mNumIndices == 3 );
		lpIndex[luiIndex++] = lpAiMesh->mFaces[luiFaceIndex].mIndices[0];
		lpIndex[luiIndex++] = lpAiMesh->mFaces[luiFaceIndex].mIndices[1];
		lpIndex[luiIndex++] = lpAiMesh->mFaces[luiFaceIndex].mIndices[2];
	}


	//Y creamos el buffer de índices:
	glGenBuffers(1, &mVboIndex);
	assert(glGetError() == GL_NO_ERROR);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIndex);
	assert(glGetError() == GL_NO_ERROR);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,	muiIndexCount * sizeof(unsigned),	lpIndex, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);
	delete [] lpIndex;
	
	// End of the function
	mbLoaded = true;
	return true;
	
	//Fíjense que el primer parámetro de las llamadas es distinto al de los casos anteriores,
	//esto es porque OpenGL necesita que se le indique el buffer es un buffer de índices.


}



void cMesh::Deinit()
{
	glDeleteBuffers(1, &mVboVertices);
	
	for(unsigned luiTexCoordChannel = 0; luiTexCoordChannel < maVboTexture.size(); ++luiTexCoordChannel)
		glDeleteBuffers(1, &maVboTexture[luiTexCoordChannel]);

	//glDeleteBuffers(1, &mVboTexture);  //eliminado
	glDeleteBuffers(1, &mVboNormals);
	glDeleteBuffers(1, &mVboIndex);
}


void cMesh::RenderMesh()
{
	glColor3f (1.0f, 1.0f, 1.0f);
	// Position
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	assert(glGetError() == GL_NO_ERROR);
	glVertexPointer(3, GL_FLOAT, sizeof(float) * 3, 0);
	assert(glGetError() == GL_NO_ERROR);
	
	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
	assert(glGetError() == GL_NO_ERROR);
	glNormalPointer(GL_FLOAT, sizeof(float) * 3, 0);
	assert(glGetError() == GL_NO_ERROR);
	
	// Set all the UV channels to the render
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	static GLenum meTextureChannelEnum[] = { GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3 };
	for(unsigned luiTexCoordChannel = 0; luiTexCoordChannel < maVboTexture.size(); ++luiTexCoordChannel)
	{
		// Texture coordinates
		glClientActiveTexture(meTextureChannelEnum[luiTexCoordChannel]);
		glBindBuffer(GL_ARRAY_BUFFER, maVboTexture[luiTexCoordChannel]);
		assert(glGetError() == GL_NO_ERROR);
		glTexCoordPointer(2, GL_FLOAT, sizeof(float)*2, 0);
		assert(glGetError() == GL_NO_ERROR);
	}


	/*  cambiada esta parte por las coordenadas
	// Texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, mVboTexture);
	assert(glGetError() == GL_NO_ERROR);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float)*2, 0);
	assert(glGetError() == GL_NO_ERROR);
	*/

	// Index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIndex);
	assert(glGetError() == GL_NO_ERROR);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawRangeElements(GL_TRIANGLES,	0,	muiIndexCount,	muiIndexCount,	GL_UNSIGNED_INT,	NULL);
	assert(glGetError() == GL_NO_ERROR);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//Por ahora las mallas las pintaremos de blanco. Como se puede ver, antes de renderizar
	//la malla le indicamos a OpenGL cuales con los búferes que debe utilizar. Las llamadas
	//a glEnableClientState sirve para indicarle a OpenGL que la memoria de los búferes se
	//encuentra en la tarjeta gráfica y no en la memoria del programa. Estas llamadas son un
	//poco costosas y dependiendo de cómo organicemos el render de nuestro juego,
	//podríamos sacarlas fuera y hacerlas sólo una vez por frame.

}


void cMesh::ProcessBoundingMesh() 
{
/*
#ifdef _DEBUG
	cout << " " << endl;
	cout << "[BOUNDING] File: " << macFile << endl;
	cout << "* NumMeshes = " <<  mMeshList.size() <<endl;
#endif
*/

/*
	for(unsigned int luiMeshIndex=0; luiMeshIndex<mMeshList.size(); luiMeshIndex++) 
	{
		cMesh* lpMesh = (cMesh*) mMeshList[luiMeshIndex].GetResource();
#ifdef _DEBUG
		std::cout << "  + Mesh[" << luiMeshIndex<<"].NumVertext = " << lpMesh->muiNumVertex << std::endl;
#endif
*/
		tBoundingMesh lBounding;
		cVec3 lvCenter = cVec3(0,0,0);
		//cVec3 lvMax = cVec3(0,0,0);
		//cVec3 lvMin = cVec3(0,0,0);
		//Yorman: Cambiado por Jesús que al parecer estaba mal
		cVec3 lvMax = cVec3(-99999999.0f,-99999999.0f,-99999999.0f);
		cVec3 lvMin = cVec3(99999999.0f,99999999.0f,99999999.0f);

		float lfX, lfY, lfZ;

		//Process bounding mesh
		for(unsigned int luiVertexIndex=0; luiVertexIndex<muiNumVertex; luiVertexIndex++)
		{ 
			cVec3* lpVertex = mpVertexPositionBuffer; 
			lfX = lpVertex[luiVertexIndex].x;
			lfY = lpVertex[luiVertexIndex].y;
			lfZ = lpVertex[luiVertexIndex].z;

			//if (lfX>lvMax.x) lvMax.x = lfX;
			//if (lfY>lvMax.y) lvMax.y = lfY;
			//if (lfZ>lvMax.z) lvMax.z = lfZ;
			//if (lfX<lvMin.x) lvMin.x = lfX;
 		//	if (lfY<lvMin.y) lvMin.y = lfY;
			//if (lfZ<lvMin.z) lvMax.z = lfZ;
			//Yorman: Cambiado por Jesús que al parecer estaba mal
			if (lfX > lvMax.x) lvMax.x = lfX;
			if (lfY > lvMax.y) lvMax.y = lfY;
			if (lfZ > lvMax.z) lvMax.z = lfZ;
			if (lfX < lvMin.x) lvMin.x = lfX;
 			if (lfY < lvMin.y) lvMin.y = lfY;
			if (lfZ < lvMin.z) lvMin.z = lfZ;
		}
		
		//lvCenter.x=(lvMax.x-abs(lvMin.x))/2;
		//lvCenter.y=(lvMax.y-abs(lvMin.y))/2;
		//lvCenter.z=(lvMax.z-abs(lvMin.z))/2;
		//Yorman: Cambiado por Jesús que al parecer estaba mal
		lvCenter.x= (lvMax.x + lvMin.x) / 2;
		lvCenter.y= (lvMax.y + lvMin.y) / 2;
		lvCenter.z= (lvMax.z + lvMin.z) / 2;

		lBounding.mfRadius=lvCenter.DistanceTo(lvMin);	//Calculate radius
		
		lBounding.mfAnchoX = abs(lvMax.x - lvMin.x) / 2.0f;
		lBounding.mfAnchoY = abs(lvMax.y - lvMin.y) / 2.0f;
		lBounding.mfAnchoZ = abs(lvMax.z - lvMin.z) / 2.0f;
		
		lBounding.mfCentroX = lvCenter.x;
		lBounding.mfCentroY = lvCenter.y;
		lBounding.mfCentroZ = lvCenter.z;

		mBoundingMesh = lBounding;

#ifdef _DEBUG
		std::cout << std::endl <<  "---------------------->" << macNameID  << std::endl;
		std::cout << "    > Bounding X:{" << lvMin.x << ", " << lvMax.x;
		std::cout << "} Y:{" << lvMin.y << ", " << lvMax.y;
		std::cout << "} Z:{" << lvMin.z << ", " << lvMax.z << "}";
		std::cout << ", Centro(" << lvCenter.x << ", " << lvCenter.y << ", " << lvCenter.z << ")";
		std::cout <<  ", Radio=" << lBounding.mfRadius << std::endl;
		std::cout << "Ancho ( " << lBounding.mfAnchoX << ", " << lBounding.mfAnchoY << ", " << lBounding.mfAnchoZ << ")" << std::endl;
		std::cout << "<----------------------" << std::endl;
#endif
	
	//}

	
}
