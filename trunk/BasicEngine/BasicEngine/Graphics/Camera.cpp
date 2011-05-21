#include "Camera.h"

//Inicializacion
void cCamera::Init()
{
	mView.LoadIdentity();
	mProj.LoadIdentity();
	mViewProj.LoadIdentity();
}

//FUNCIONES

//Con esto definiremos la matrz vista
//lvPosition : donde est� la camara, 
//lvTarget: punto al que mira la c�mara
//lvUpWorld: vector direcci�n up de la c�mara
void cCamera::SetLookAt (const cVec3 &lvPosition, const cVec3 &lvTarget, const cVec3 &lvUpWorld)
{
	mView.LoadLookAt(lvPosition, lvTarget, lvUpWorld);
	RefreshViewProj();
}


//Matriz de proyecc��n ortogonal (con esta los objetos lejanos y cercanos se ven del mismo tama�o)
//lfLeft, lfRight, lfBottom, lfTop: Tama�o del �rea a renderizar 
//lfZNear, lfZNFar: el clipping con respecto a la distancia de la c�mara, que mostrar� por pantalla todo lo que se encuentre entre estos dos valores
void cCamera::SetOrtho (float lfLeft, float lfRight, float lfBottom, float lfTop, float lfZNear, float lfZNFar)
{
	mProj.LoadOrtho(lfLeft, lfRight, lfBottom, lfTop, lfZNear, lfZNFar);
	RefreshViewProj();
}

//Matriz perspectiva (los objetos lejanos se muestran m�s peque�o)
//lfFVOVY_Rad: el �ngulo de apertura de la c�rama con respecto al eje Y
//lfAspect: la relaci�n de aspecto entre el ancho y el alto
//lfZNear, lfZNFar: el clipping con respecto a la distancia de la c�mara, que mostrar� por pantalla todo lo que se encuentre entre estos dos valores
void cCamera::SetPerspective (float lfFVOVY_Rad, float lfAspect, float lfZNear, float lfZFar)
{
	mProj.LoadPerpective (lfFVOVY_Rad, lfAspect, lfZNear, lfZFar);
	RefreshViewProj();
}