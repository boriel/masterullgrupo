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

	// Situamos al listener en el punto central.
	ALfloat ListenerPos[]={0.0,0.0,0.0};
	alListenerfv( AL_POSITION, ListenerPos); 
	alListener3f(AL_VELOCITY, 0.0,0.0,0.0);
	
	// Preparamos el estado con los efectos
	alDopplerFactor(true);
	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);

	// Activamos el sonido
	mIsSoundOn=true;
}

// Esta funci�n devolver� el ID del sonido para poder reproducirlo por par�metro desde otro objeto
Sound *cSoundManager::AddSound(char *lFileName){
	ALuint uiBuffer;
	ALuint uiSource;
	// Generamos el AL Buffer
	alGenBuffers( 1, &uiBuffer );
	
	// Cargamos el wav. Internamente accede a /Data/Sounds. lFileName es el nombre del fichero en s�.
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(lFileName), uiBuffer))ALFWprintf("cSoundManager::AddSound() ---> Fallo al cargar %s\n", ALFWaddMediaPath(lFileName));
	
	// Generamos las fuentes para reproducir los buffers y las situamos en sus posiciones iniciales
    alGenSources( 1, &uiSource );

	// Linkamos los buffers a las fuentes
	alSourcei( uiSource, AL_BUFFER, uiBuffer );
	
	// A�adimos el nuevo sonido a la lista
	Sound *lNewSound=new Sound();
	lNewSound->Name=lFileName;
	lNewSound->Buffer=uiBuffer;
	lNewSound->Source=uiSource;
	mSoundsList.push_back(lNewSound);

	return lNewSound;
}

// Se reproducir� el sonido pasado por par�metro 
void cSoundManager::Play(Sound *lSound, bool lLoop){
	if(mIsSoundOn){
		// Reproducimos la fuente
		alSourcePlay( lSound->Source );
	
		if(lLoop){
			//Hacemos sonar repetidamente el sonido
			alSourcei( lSound->Source ,AL_LOOPING,AL_TRUE);
		}
	}
}

// Se parar� el sonido pasado por par�metro 
void cSoundManager::Stop(Sound *lSound){
	// Detenemos la fuente
	alSourceStop( lSound->Source );
}

void cSoundManager::Update(float lfTimestep){
}

bool cSoundManager::Deinit(){
	// Hay que limpiar fuentes y buffers
	for (unsigned luiIndex = 0; luiIndex < mSoundsList.size(); ++luiIndex ) {
		alDeleteBuffers(1,&mSoundsList[luiIndex]->Buffer);
		alDeleteSources(1,&mSoundsList[luiIndex]->Source);
	}
	mSoundsList.clear();

	ALFWShutdownOpenAL();

	ALFWShutdown();

	return 0;
}