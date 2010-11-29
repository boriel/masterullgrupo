/*
#include "Mesh.h"

#include "../GLHeaders.h"
#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>

bool cMesh::Init (const std::string &lacNameID, void* lpMemoryData, int luiTypeID)
{

	//En primer lugar crearemos el buffer de �ndices
	
	aiMesh* lpAiMesh = (aiMesh*)lpMemoryData;

	glGenBuffers(1, &mVboVertices);
	assert(glGetError() == GL_NO_ERROR);


	//Una vez que hemos creado el buffer,
	//debemos indicarle a OpenGL que las siguientes llamadas se refieren al buffer de
	//v�rtices, por lo que ejecutamos:

	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	assert(glGetError() == GL_NO_ERROR);

	//Y por �ltimo inicializamos el buffer con la siguiente llamada:
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * lpAiMesh->mNumVertices,	lpAiMesh->mVertices, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);


	//El primer par�metro de la llamada le indica a OpenGL que es un array buffer normal y
	//no uno de �ndices. A continuaci�n se le indica cuanta memoria tiene que copiar en el
	//buffer, por lo que se multiplica el n�mero de v�rtices por el n�mero de flotantes que
	//tiene cada v�rtice (X, Y, Z) por el tama�o que tiene un flotante, todo esto junto da la
	//cantidad de bytes que se deben copiar. El tercer par�metro es el comienzo de la
	//memoria donde se encuentran los v�rtices dentro de la estructura de la escena (en este
	//caso la estructura encaja con lo que necesitamos, ya que es una array de posiciones X,
	//Y, Z). El �ltimo par�metro le indica a la tarjeta gr�fica que el buffer se debe almacenar
	//en memoria de video y que la aplicaci�n no acceder� directamente al buffer para
	//modificar los datos que hay en �l contenidos. Con esto ya tenemos listo el buffer de
	//posiciones. El buffer de normales es bastante similar:
	
	glGenBuffers(1, &mVboNormals);
	assert(glGetError() == GL_NO_ERROR);

	// Check that the mesh has normals
	assert(lpAiMesh->HasNormals());
	glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
	assert(glGetError() == GL_NO_ERROR);
	glBufferData(GL_ARRAY_BUFFER,	sizeof(float) * 3 * lpAiMesh->mNumVertices,	lpAiMesh->mNormals, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);

	//El c�digo anterior muestra un error si la malla no cuenta con normales
	//Al igual que en el caso de las posiciones,
	//las normales est�n convenientemente almacenadas en la escena, por lo que la
	//inicializaci�n del buffer es bastante simple. Esto no sucede con las coordenadas de
	//textura, por lo que tenemos que componer primero el buffer en memoria:


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


	//El c�digo anterior crea el buffer en memoria con los datos en la distribuci�n que
	//necesitamos. Si nos fijamos, estamos aplicando una conversi�n a las coordenadas Y de
	//la textura. Esto es porque OpenGL y DirectX tienen invertidos entre s� este par�metro.
	//Por lo que es necesario invertirlo para que se muestre correctamente. Una vez que
	//tenemos el buffer, se aplica un c�digo similar al ya visto con las posiciones y las
	//normales:

	glGenBuffers(1, &mVboTexture);
	assert(glGetError() == GL_NO_ERROR);
	glBindBuffer(GL_ARRAY_BUFFER, mVboTexture);
	assert(glGetError() == GL_NO_ERROR);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * luiTexCoordFloats,
	lpTexCoordinates, GL_STATIC_DRAW);
	assert(glGetError() == GL_NO_ERROR);

	delete [] lpTexCoordinates;


	//El c�digo mostrado s�lo considera que hay un juego de coordenadas de texturas, si
	//hubiera m�s, habr�a que repetir este c�digo por cada juego de coordenadas. Ya s�lo nos
	//queda la carga del buffer de �ndices, que tambi�n nos fuerza a componer primero el
	//buffer en memoria:

	// Index
	muiIndexCount = lpAiMesh->mNumFaces * 3;
	unsigned* lpIndex = new unsigned[ muiIndexCount ];
	luiIndex = 0;
	for(unsigned luiFaceIndex=0;luiFaceIndex<lpAiMesh->mNumFaces;++luiFaceIndex )
	{
		// Make sure that each face has 3 vertex
		assert(lpAiMesh->mFaces[luiFaceIndex].mNumIndices == 3 );
		lpIndex[luiIndex++] = lpAiMesh->mFaces[luiFaceIndex].mIndices[0];
		lpIndex[luiIndex++] = lpAiMesh->mFaces[luiFaceIndex].mIndices[1];
		lpIndex[luiIndex++] = lpAiMesh->mFaces[luiFaceIndex].mIndices[2];
	}


	//Y creamos el buffer de �ndices:
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
	
	//F�jense que el primer par�metro de las llamadas es distinto al de los casos anteriores,
	//esto es porque OpenGL necesita que se le indique el buffer es un buffer de �ndices.


}



void cMesh::Deinit()
{
	glDeleteBuffers(1, &mVboVertices);
	glDeleteBuffers(1, &mVboTexture);
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
	
	// Texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, mVboTexture);
	assert(glGetError() == GL_NO_ERROR);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float)*2, 0);
	assert(glGetError() == GL_NO_ERROR);
	
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
	//la malla le indicamos a OpenGL cuales con los b�feres que debe utilizar. Las llamadas
	//a glEnableClientState sirve para indicarle a OpenGL que la memoria de los b�feres se
	//encuentra en la tarjeta gr�fica y no en la memoria del programa. Estas llamadas son un
	//poco costosas y dependiendo de c�mo organicemos el render de nuestro juego,
	//podr�amos sacarlas fuera y hacerlas s�lo una vez por frame.

}
*/