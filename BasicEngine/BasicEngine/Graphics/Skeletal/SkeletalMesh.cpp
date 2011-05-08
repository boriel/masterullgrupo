
#include "SkeletalMesh.h"
#include "../GLHeaders.h"
#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>
#include "SkeletalCoreModel.h"
#include "../GraphicManager.h"
#include "../../MathLib/MathLib.h"
#include "..\..\Utility\ResourceHandle.h"
#include "..\Materials\Material.h"
#include "..\Effects\Effect.h"

//include "cal3d\skeleton.h"



bool cSkeletalMesh::Init( const std::string &lacNameID, void * lpMemoryData, int liDataType )
{
	cSkeletalCoreModel * lpCoreModel = (cSkeletalCoreModel *)lpMemoryData;
	lpCoreModel->CreateInstance(this);
	return true;
}

void cSkeletalMesh::Deinit()
{
	delete mpCal3DModel;
}

void cSkeletalMesh::Update(float lfTimestep)
{
	mpCal3DModel->update(lfTimestep);
}

bool cSkeletalMesh::PlayAnim(const std::string & lacAnimName, float lfWeight, float lfDelayIn, float lfDelayOut)
{
	// Search for the animation
	sAnimationDef* lpDef = mpCoreModel->GetAnimationDef(lacAnimName);
	if (lpDef)
	{
		if (lpDef->meAnimType == eAnimType_Cycle)
		{
			// Blend the cycle
			mpCal3DModel->getMixer()->blendCycle( lpDef->miAnimID,
			lfWeight, lfDelayIn );
		}
		else
		{
			// It´s an action
			mpCal3DModel->getMixer()->executeAction( lpDef->miAnimID,
			lfDelayIn, lfDelayOut, lfWeight );
		}

		return true;
	}

	return false;
}
	

void cSkeletalMesh::StopAnim(const std::string & lacAnimName,	float lfDelayOut)
{
	sAnimationDef* lpDef= mpCoreModel->GetAnimationDef(lacAnimName);
	if (lpDef)
	{
		if (lpDef->meAnimType == eAnimType_Cycle)
		{
			// Blend the cycle
			mpCal3DModel->getMixer()->clearCycle(lpDef->miAnimID,
			lfDelayOut);
		}
		else
		{
			// It´s an action
			mpCal3DModel->getMixer()->removeAction( lpDef->miAnimID,
			lfDelayOut);
		}
	}
}

//se resetea la matriz de mundo y se le solicita a Cal3D que de una
//lista de líneas (representadas como X1, Y1, Z1, X2, Y2, Z2). Además, establece un límite
//de 120 bones en el modelo (esto se podía cambiar a un array dinámico si es necesario).
//Una vez se tienen las líneas que representan los bones, se renderiza la línea. Lo único
//que es un poco más raro es la escala que se aplica a la matriz de mundo, pero esto es
//porque el modelo que estamos empleando es muy grande, por lo que lo escalamos a
//0.01. Cuando se empleen modelos con la escala correcta, se puede eliminar este
//escalado.
void cSkeletalMesh::RenderSkeleton(void)
{
	cMatrix lWorld;
	lWorld.LoadIdentity();
	lWorld.LoadScale(0.01f);
	cGraphicManager::Get().SetWorldMatrix(lWorld);
	unsigned luiBoneCount = mpCal3DModel->getSkeleton()->getCoreSkeleton()->getVectorCoreBone().size();
	assert(luiBoneCount < 120);
	float mafLines[120] [6];
	int liBones = mpCal3DModel->getSkeleton()->getBoneLines(&mafLines[0][0]);
	
	for (int liIndex = 0; liIndex < liBones; ++liIndex)
	{
		cVec3 lvP1(mafLines[liIndex][0], mafLines[liIndex][1],mafLines[liIndex][2]);
		cVec3 lvP2(mafLines[liIndex][3], mafLines[liIndex][4],mafLines[liIndex][5]);
		cGraphicManager::Get().DrawLine( lvP1, lvP2, cVec3(1.0f, 1.0f, 1.0f));
	}

	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
}




//Básicamente lo que haremos será establecer los buffers y llamar a la función de
//renderizado de OpenGL de forma similar a como ya lo hicimos en la función de cMesh.
//Lo único que merece la pena reseñar es que el buffer de pesos se pasará al effecto como
//buffer de color y el buffer de índices de hueso como coordenada de textura adicional:
void cSkeletalMesh::RenderMesh()
{
	// Position
	glBindBuffer(GL_ARRAY_BUFFER, mpCoreModel->mVboVertices);
	assert(glGetError() == GL_NO_ERROR);
	glVertexPointer(3, GL_FLOAT, sizeof(float) * 3, 0);
	assert(glGetError() == GL_NO_ERROR);

	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, mpCoreModel->mVboNormals);
	assert(glGetError() == GL_NO_ERROR);
	glNormalPointer(GL_FLOAT, sizeof(float) * 3, 0);
	assert(glGetError() == GL_NO_ERROR);

	// This line has been added  (esto tengo que verlo, porque no teniamos la funcion creada, lo que había era un metodo virtaul implementado en la clase con un ; solamente)
	//-----------------------------------------------------------------

	// Set all the UV channels to the render
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	assert(mpCoreModel->maVboTexture.size() <= 3);
	static GLenum meTextureChannelEnum[] = { GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3 };

	for(unsigned luiTexCoordChannel = 0; luiTexCoordChannel < mpCoreModel->maVboTexture.size();	++luiTexCoordChannel)
	{
		// Texture coordinates
		glClientActiveTexture(meTextureChannelEnum[luiTexCoordChannel]);
		glBindBuffer(GL_ARRAY_BUFFER,
		mpCoreModel->maVboTexture[luiTexCoordChannel]);
		assert(glGetError() == GL_NO_ERROR);
		glTexCoordPointer(2, GL_FLOAT, sizeof(float)*2, 0);
		assert(glGetError() == GL_NO_ERROR);
	}

	// Bone Index
	glClientActiveTexture(
	meTextureChannelEnum[mpCoreModel->maVboTexture.size()]);
	glBindBuffer(GL_ARRAY_BUFFER, mpCoreModel->mVboBoneIx);
	assert(glGetError() == GL_NO_ERROR);
	glTexCoordPointer(4, GL_FLOAT, sizeof(float)*4, 0);
	assert(glGetError() == GL_NO_ERROR);
	
	// Weights
	glBindBuffer(GL_ARRAY_BUFFER, mpCoreModel->mVboWeight);
	assert(glGetError() == GL_NO_ERROR);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(unsigned char) * 4, 0);
	assert(glGetError() == GL_NO_ERROR);
	
	// Index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mpCoreModel->mVboIndex);
	assert(glGetError() == GL_NO_ERROR);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawRangeElements(GL_TRIANGLES,	0,	mpCoreModel->muiIndexCount,	mpCoreModel->muiIndexCount,	GL_UNSIGNED_INT,	NULL);
	
	assert(glGetError() == GL_NO_ERROR);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

//se componen las matrices para cada hueso y se setean comoparámetro en el efecto
void cSkeletalMesh::PrepareRender(cResourceHandle lMaterial)
{
	struct sMatrix3x4 
	{
		float r00, r01, r02, tx;
		float r10, r11, r12, ty;
		float r20, r21, r22, tz;
	};

	sMatrix3x4 lMatrices[ 80 ];
	typedef std::vector< CalBone * > cVBones;
	const cVBones &lBones = mpCal3DModel->getSkeleton()->getVectorBone( );
	
	int liBoneCount = lBones.size();
	assert(liBoneCount <= 80);
	for( unsigned luiIndex = 0;	luiIndex < (unsigned)liBoneCount;	++luiIndex )
	{
		const CalMatrix &lCalMatrix =	lBones[ luiIndex ]->getTransformMatrix( );
		const CalVector &lCalTrans = lBones[ luiIndex ]->getTranslationBoneSpace( );
		
		// Convert the CalMatrix in a 3x4 transposed matrix
		lMatrices[ luiIndex ].r00 = lCalMatrix.dxdx;
		lMatrices[ luiIndex ].r01 = lCalMatrix.dxdy;
		lMatrices[ luiIndex ].r02 = lCalMatrix.dxdz;
		lMatrices[ luiIndex ].tx = lCalTrans.x;
		lMatrices[ luiIndex ].r10 = lCalMatrix.dydx;
		lMatrices[ luiIndex ].r11 = lCalMatrix.dydy;
		lMatrices[ luiIndex ].r12 = lCalMatrix.dydz;
		lMatrices[ luiIndex ].ty = lCalTrans.y;
		lMatrices[ luiIndex ].r20 = lCalMatrix.dzdx;
		lMatrices[ luiIndex ].r21 = lCalMatrix.dzdy;
		lMatrices[ luiIndex ].r22 = lCalMatrix.dzdz;
		lMatrices[ luiIndex ].tz = lCalTrans.z;
	}

	cMaterial* lpMaterial = (cMaterial*)lMaterial.GetResource();
	cEffect * lpEffect = (cEffect *)lpMaterial->GetEffect().GetResource();
	lpEffect->SetParam("BonesRow", &lMatrices[0].r00,	lBones.size( ) * 12 );

}