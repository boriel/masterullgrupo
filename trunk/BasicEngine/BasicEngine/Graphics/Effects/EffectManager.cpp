/*

*/

#include "EffectManager.h"
#include "Effect.h"



//crea y registra el contexto de Cg. Además se activa la opción necesaria
//para que Cg gestione automáticamente el estado de las texturas, por lo que nosotros no
//deberemos hacer en nuestro código llamadas a glBindTexture, glActiveTexture,...
cEffectManager::cEffectManager()
{
	mCGContext = cgCreateContext();
	cgGLRegisterStates(mCGContext);
	cgGLSetManageTextureParameters(mCGContext, CG_TRUE);
}


cResource * cEffectManager::LoadResourceInternal( std::string lacNameID, const std::string &lacFile )
{
	cEffect * lpEffect = new cEffect();

	if ( !lpEffect->Init( lacNameID, lacFile ) )
	{
		delete lpEffect;
		return NULL;
	}
	return lpEffect;
}


//la función Reload sólo se encarga de identificar qué resources son válidos y llamar a su función Reload
void cEffectManager::Reload()
{
	for (unsigned luiIndex = 0; luiIndex < muiMaxSize; ++luiIndex)
	{
		// Is a valid resource?
		if ( maResources[luiIndex].muiKey != kuiInvalidKey )
		{
			// Check that all is right
			assert( maResources[luiIndex].mpResource );
			assert( maResources[luiIndex].mpResource->IsLoaded() );
			// Reload the resource
			maResources[luiIndex].mpResource->Reload();
		}
	}
}