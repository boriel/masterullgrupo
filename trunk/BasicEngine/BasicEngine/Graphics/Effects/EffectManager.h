/*
Class: cEffectManager

Gestiona los resources del tipo Effect, se encarga de inicializar y 
liberar la librería CG, así como de almacenar su contexto (CGcontext).
*/

#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "../GLHeaders.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"

class cEffectManager : public cResourceManager, public cSingleton<cEffectManager> {
	public:
		friend class cSingleton<cEffectManager>;
		inline CGcontext GetCGContext() { return mCGContext; }
		void Reload(); //que se encargará de volver a cargar los ficheros de efectos, de esta forma podemos ir escribiendo y probando los efectos sin necesidad de reiniciar la aplicación
	
	protected:
		cEffectManager(); // Protected constructor

	private:
		virtual cResource * LoadResourceInternal( std::string lacNameID, const std::string &lacFile );
		CGcontext mCGContext;
};

#endif