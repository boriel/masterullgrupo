/*

*/

#include "EffectManager.h"
#include "Effect.h"



//crea y registra el contexto de Cg. Adem�s se activa la opci�n necesaria
//para que Cg gestione autom�ticamente el estado de las texturas, por lo que nosotros no
//deberemos hacer en nuestro c�digo llamadas a glBindTexture, glActiveTexture,...
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


//la funci�n Reload s�lo se encarga de identificar qu� resources son v�lidos y llamar a su funci�n Reload
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