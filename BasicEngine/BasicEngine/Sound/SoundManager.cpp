#include "SoundManager.h"

bool cSoundManager::Init(){
	// Initialize Framework
	ALFWInit();

	ALFWprintf("Pruebas de Espacializacion\n");

	if (!ALFWInitOpenAL())
	{
		ALFWprintf("OpenAL no se ha cargado correctamente.\n");
		ALFWShutdown();
		return 0;
	}
/*
	// Generamos los AL Buffer
	alGenBuffers( 1, &uiBufferPasos );
	alGenBuffers( 1, &uiBufferSirena);
	alGenBuffers( 1, &uiBufferEntorno);
	
	// Cargamos los wav
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(PASOS), uiBufferPasos))ALFWprintf("Fallo al cargar %s\n", ALFWaddMediaPath(PASOS));
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(SIRENA), uiBufferSirena))ALFWprintf("Fallo al cargar %s\n", ALFWaddMediaPath(SIRENA));
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(ENTORNO), uiBufferEntorno))ALFWprintf("Fallo al cargar %s\n", ALFWaddMediaPath(ENTORNO));
	
	// Generamos las fuentes para reproducir los buffers y las situamos en sus posiciones iniciales
    alGenSources( 1, &uiSourcePasos );
	alGenSources( 1, &uiSourceSirena );
	alGenSources( 1, &uiSourceEntorno );
	
	// Ponemos los pasos que comiencen a la izquierda y delante
	ALfloat PasosPos[]={-10.0,0.0,1.0};
	alSourcef(uiSourcePasos,AL_GAIN, 1);
	alSourcef(uiSourcePasos,AL_REFERENCE_DISTANCE, 2.0);
	alSourcefv( uiSourcePasos, AL_POSITION,PasosPos);
	
	// La Sirena estará delante y a la izquierda, además de modificar los valores de propagación del sonido
	ALfloat SirenaPos[]={-50.0,0.0,120.0};
	alSourcef(uiSourceSirena,AL_GAIN, ALfloat(0.4));
	alSource3f(uiSourceSirena,AL_VELOCITY,0.0, 0.0, -10.0);
	alSourcef(uiSourceSirena,AL_REFERENCE_DISTANCE,30.0);
	alSourcef(uiSourceSirena,AL_MAX_DISTANCE, 90.0);
	alSourcefv( uiSourceSirena, AL_POSITION,SirenaPos);
	
	// El entorno estará situado en la misma posición del listener
	ALfloat EntornoPos[]={0.0,0.0,0.0};
	alSourcef(uiSourceEntorno,AL_GAIN, 0.5);
	alSourcefv( uiSourceEntorno, AL_POSITION,EntornoPos);
	*/

	// Situamos al listener en el punto central.
	ALfloat ListenerPos[]={0.0,0.0,0.0};
	alListenerfv( AL_POSITION, ListenerPos); 
	alListener3f(AL_VELOCITY, 0.0,0.0,0.0);
	
	// Preparamos el estado con los efectos
	alDopplerFactor(true);
	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
}

void cSoundManager::AddSound(){
	// Generamos el AL Buffer
	alGenBuffers( 1, &uiBufferPasos );
	
	// Cargamos el wav
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(ENTORNO), uiBufferPasos))ALFWprintf("cSoundManager::AddSound() ---> Fallo al cargar %s\n", ALFWaddMediaPath(ENTORNO));
	
	// Generamos las fuentes para reproducir los buffers y las situamos en sus posiciones iniciales
    alGenSources( 1, &uiSourcePasos );

	// Linkamos los buffers a las fuentes
	alSourcei( uiSourcePasos, AL_BUFFER, uiBufferPasos );
}

// Se reproducirá el sonido pasado por parámetro 
void cSoundManager::Play(){
	// Reproducimos la fuente
    alSourcePlay( uiSourcePasos );

	//Hacemos sonar repetidamente el sonido
	alSourcei(uiSourcePasos,AL_LOOPING,AL_TRUE);
}

void cSoundManager::Update(float lfTimestep){
	
}
bool cSoundManager::Deinit(){
	// Limpiamos fuentes y buffers
	alSourceStop(uiSourcePasos);
    alDeleteSources(1, &uiSourcePasos);
	alDeleteBuffers(1, &uiBufferPasos);
	alSourceStop(uiSourceSirena);
    alDeleteSources(1, &uiSourceSirena);
	alDeleteBuffers(1, &uiBufferSirena);
	alSourceStop(uiSourceEntorno);
    alDeleteSources(1, &uiSourceEntorno);
	alDeleteBuffers(1, &uiBufferEntorno);
	
	ALFWShutdownOpenAL();

	ALFWShutdown();

	return 0;
}