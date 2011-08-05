/* File: Effect.cpp */

#include "Effect.h"
#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>
#include "EffectManager.h"
#include "../Textures/Texture.h"
#include <Windows.h>

//Lo primero que hacemos en esta función es inicializar los atributos de la clase. Después
//cargamos el fichero de efectos y comprobamos que no se ha producido error alguno
//durante la carga. Si no se han producido errores, pasamos a comprobar si los profiles
//de las techniques están soportadas por la tarjeta gráfica. Si todo va bien, la función
//devolverá true.

bool cEffect::Init( const std::string &lacNameID, const std::string &lacFile ) {
	// Initialization of the class attributes
	macFile = lacFile;
	macLastTecnique = "";
	mEffect = NULL;
	mTechnique = NULL;
	mCurrentPass = NULL;
	mbLoaded = false;
	macLastTecnique = "Technique"; //temporal Yorman quitar!!

	// Loading of the effect
	CGcontext lCGContext = cEffectManager::Get().GetCGContext();
	mEffect= cgCreateEffectFromFile(lCGContext, lacFile.c_str(), NULL);

	if (!mEffect) {
		OutputDebugString("Unable to create effect!\n");
		const char *lacListing = cgGetLastListing(lCGContext);
		if (lacListing) {
			char lacBuffer[512];
			sprintf(lacBuffer, "%s\n", lacListing );
			OutputDebugString( lacBuffer );
		}
		return false;
	}

	// Check if the techniques are valid
	CGtechnique lTechnique = cgGetFirstTechnique(mEffect);
	while (lTechnique) {
		if (cgValidateTechnique(lTechnique) == CG_FALSE) {
			char lacBuffer[512];
			sprintf(lacBuffer, "Technique %s did not validate. Skipping.\n",
			cgGetTechniqueName(lTechnique));
			OutputDebugString( lacBuffer );
		}
		lTechnique = cgGetNextTechnique(lTechnique);
	}
	
	mbLoaded = true;
	return true;
}

void cEffect::Deinit() { //La función Deinit libera el effecto y resetea los atributos de la clase
	cgDestroyEffect( mEffect );
	macLastTecnique = "";
	mEffect = NULL;
	mTechnique = NULL;
	mCurrentPass = NULL;
}

void cEffect::Reload() {
	Deinit();
	Init( GetNameID(), macFile );
}


//sólo se encarga de llamar a la función de Cg que busca una tecnique por nombre y guardarla si hay éxito
bool cEffect::SetTechnique( const std::string &lacTechnique ) {
	if ( macLastTecnique != lacTechnique ) {
		// Set Technique
		mTechnique=cgGetNamedTechnique( mEffect, lacTechnique.c_str() );
		if ( mTechnique ) {
			macLastTecnique = lacTechnique;
			return true;
		}
	}
	return false;
}

//Las funciones para establecer la pasada actual
bool cEffect::SetFirstPass() {
	if ( mTechnique ) {
		mCurrentPass = cgGetFirstPass(mTechnique);
		if ( mCurrentPass ) {
			cgSetPassState(mCurrentPass);
			return true;
		}
	}
	return false;
}

bool cEffect::SetNextPass() {
	if ( mTechnique ) {
		assert( mCurrentPass );
		cgResetPassState(mCurrentPass);
		mCurrentPass = cgGetNextPass(mCurrentPass);
		if (mCurrentPass) {
			cgSetPassState(mCurrentPass);
			return true;
		}
	}
	return false;
}


void cEffect::SetParam(const std::string &lacName, const cMatrix& lMatrix ) {
	CGparameter lParam = cgGetNamedEffectParameter(mEffect,	lacName.c_str());
	if (lParam) cgSetMatrixParameterfc(lParam, lMatrix.AsFloatPointer());
}

void cEffect::SetParam(const std::string &lacName, float lParamValue ) {
	CGparameter lParam = cgGetNamedEffectParameter(mEffect,	lacName.c_str());
	if (lParam) cgSetParameter1f(lParam, lParamValue);
}

void cEffect::SetParam(const std::string &lacName, const cVec3& lParamValue ) {
	CGparameter lParam = cgGetNamedEffectParameter(mEffect,	lacName.c_str());
	if (lParam) cgSetParameter3fv(lParam, lParamValue.AsFloatPointer());
}

void cEffect::SetParam(const std::string &lacName, const cVec4& lParamValue ) {
	CGparameter lParam = cgGetNamedEffectParameter(mEffect, lacName.c_str());
	if (lParam) cgSetParameter4fv(lParam, lParamValue.AsFloatPointer());
}

void cEffect::SetParam(const std::string &lacName, cResourceHandle lParamValue ) {
	CGparameter lParam = cgGetNamedEffectParameter(mEffect,	lacName.c_str());
	if (lParam) {
		assert(lParamValue.IsValidHandle());
		cTexture * lpTexture = (cTexture*)lParamValue.GetResource();
		unsigned luiTextureHandle = lpTexture->GetTextureHandle();
		cgGLSetupSampler(lParam, luiTextureHandle);
	}
}

//Los efectos Cg son un poco restrictivos a la hora de pasar un array de flotantes al
//shader y te exigen que rellenes todo el buffer disponible en el shader, de lo contrario
//dará un error y no realizará la acción. Es por eso que se comprueba el tamaño del
//buffer a rellenar y si es mayor que el que intentamos setear entonces usamos un array
//auxiliar para rellenar todo el buffer.
void cEffect::SetParam(const std::string &lacName, const float * lfParam, unsigned liCount )
{
	static const unsigned kuiAuxiliarBuffer = 256 * 4;
	static float gFullArray[kuiAuxiliarBuffer];
	CGparameter lParam = cgGetNamedEffectParameter(mEffect, lacName.c_str());
	
	if (lParam)
	{
		int liNRows = cgGetParameterRows(lParam);
		int liNCols = cgGetParameterColumns(lParam);
		int liASize = cgGetArrayTotalSize(lParam);
		int liNTotal = liNRows * liNCols;
		
		if (liASize > 0)
		{
			liNTotal *= liASize;
			
			if ( liCount < (unsigned) liNTotal )
			{
				assert(kuiAuxiliarBuffer > liNTotal);
				assert(kuiAuxiliarBuffer > liCount);
				memcpy(gFullArray, lfParam, sizeof(float) * liCount);
				cgSetParameterValuefr(lParam, liNTotal, gFullArray);
			}
			else
			{
				cgSetParameterValuefr(lParam, liCount, lfParam);
			}
			CGerror err = cgGetError();
			
			if (err != CG_NO_ERROR)
			{
				OutputDebugString(cgGetErrorString( err ));
				OutputDebugString("\n");
			}
		}
	}
}
