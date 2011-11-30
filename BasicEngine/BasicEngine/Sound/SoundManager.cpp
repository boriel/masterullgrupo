#include "SoundManager.h"
#include <time.h>

bool cSoundManager::Init(){
	// Initialize Framework
	ALFWInit();

	ALFWprintf("Pruebas de Espacializacion\n");

	if (!ALFWInitOpenAL())
	{
		ALFWprintf("OpenAL no se ha cargado correctamente.\n");
		ALFWShutdown();
		return false;
	}

	// Situamos al listener en el punto central.
	ALfloat ListenerPos[]={0.0,0.0,0.0};
	alListenerfv( AL_POSITION, ListenerPos); 
	alListener3f(AL_VELOCITY, 0.0,0.0,0.0);
	
	// Preparamos el estado con los efectos
	alDopplerFactor(true);
	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);

	// ! Activamos el sonido y la musica por defecto
	mIsSoundOn=true;
	mIsMusicOn=true;
	return true;
}
void cSoundManager::SetListenerPosition(cVec3 lPosition){
	ALfloat ListenerPos[]={lPosition.x,lPosition.y,lPosition.z};
	alListenerfv( AL_POSITION, ListenerPos); 
	alListener3f(AL_VELOCITY, 0.0,0.0,0.0);
}

// Esta funci�n devolver� el ID del sonido para poder reproducirlo por par�metro desde otro objeto
Sound *cSoundManager::AddSound(char *lFileName, bool isMusic){
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
			
	Sound *lNewSound=new Sound();
	lNewSound->Name=lFileName;
	lNewSound->Buffer=uiBuffer;
	lNewSound->Source=uiSource;

	if(isMusic){
		mMusic=new Sound;
		mMusic=lNewSound;
		// Bajamos un poco el volumen de la musica
		float newVolume = 0.2f;
		alSourcef(uiSource, AL_GAIN, newVolume);
	}
		// A�adimos el nuevo sonido a la lista
	else mSoundsList.push_back(lNewSound);
	return lNewSound;
}

void cSoundManager::PlaySoundBank(mSoundBank *lSoundBank, bool lRandom){
	if(mIsSoundOn){
		unsigned int luiIndex;
		if(lRandom){
			 /* initialize random seed: */
			srand ( time(NULL) );

			 /* generate secret number: */
			luiIndex= rand() % lSoundBank->size();
		}else luiIndex=1;

		// Reproducimos la fuente
		alSourcePlay( lSoundBank->at(luiIndex)->Source );
	}
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

void cSoundManager::PlayMusic(){
	if(mIsMusicOn){
		// Reproducimos la fuente
		alSourcePlay( mMusic->Source );
		//Hacemos sonar repetidamente la m�sica
		alSourcei( mMusic->Source ,AL_LOOPING,AL_TRUE);
	}
}

void cSoundManager::ChangeMusic(char *lFileName){
	// Eliminamos la musica
	alDeleteBuffers(1,&mMusic->Buffer);
	alDeleteSources(1,&mMusic->Source);
	delete mMusic;

	AddSound(lFileName,true);
	PlayMusic();

}

// Se parar� el sonido pasado por par�metro 
void cSoundManager::Stop(Sound *lSound){
	// Detenemos la fuente
	alSourceStop( lSound->Source );
}

void cSoundManager::StopMusic(){
	// Detenemos la fuente
	alSourceStop( mMusic->Source );
}

void cSoundManager::Update(float lfTimestep){
}

bool cSoundManager::Deinit(){
	// Hay que limpiar fuentes y buffers
	for (unsigned luiIndex = 0; luiIndex < mSoundsList.size(); ++luiIndex ) {
		alDeleteBuffers(1,&mSoundsList[luiIndex]->Buffer);
		alDeleteSources(1,&mSoundsList[luiIndex]->Source);
		delete mSoundsList[luiIndex];
	}
	mSoundsList.clear();

	// Eliminamos la musica
	alDeleteBuffers(1,&mMusic->Buffer);
	alDeleteSources(1,&mMusic->Source);
	ALFWShutdownOpenAL();

	ALFWShutdown();

	return 0;
}