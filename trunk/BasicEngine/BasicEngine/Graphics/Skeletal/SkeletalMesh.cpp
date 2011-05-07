
#include "SkeletalMesh.h"
#include "../GLHeaders.h"
#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>
#include "SkeletalCoreModel.h"
#include "../GraphicManager.h"
#include "../../MathLib/MathLib.h"

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



