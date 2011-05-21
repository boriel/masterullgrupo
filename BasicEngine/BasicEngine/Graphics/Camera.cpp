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
//lvPosition : donde está la camara, 
//lvTarget: punto al que mira la cámara
//lvUpWorld: vector dirección up de la cámara
void cCamera::SetLookAt (const cVec3 &lvPosition, const cVec3 &lvTarget, const cVec3 &lvUpWorld)
{
	mView.LoadLookAt(lvPosition, lvTarget, lvUpWorld);
	RefreshViewProj();
}


//Matriz de proyeccíón ortogonal (con esta los objetos lejanos y cercanos se ven del mismo tamaño)
//lfLeft, lfRight, lfBottom, lfTop: Tamaño del área a renderizar 
//lfZNear, lfZNFar: el clipping con respecto a la distancia de la cámara, que mostrará por pantalla todo lo que se encuentre entre estos dos valores
void cCamera::SetOrtho (float lfLeft, float lfRight, float lfBottom, float lfTop, float lfZNear, float lfZNFar)
{
	mProj.LoadOrtho(lfLeft, lfRight, lfBottom, lfTop, lfZNear, lfZNFar);
	RefreshViewProj();
}

//Matriz perspectiva (los objetos lejanos se muestran más pequeño)
//lfFVOVY_Rad: el ángulo de apertura de la cárama con respecto al eje Y
//lfAspect: la relación de aspecto entre el ancho y el alto
//lfZNear, lfZNFar: el clipping con respecto a la distancia de la cámara, que mostrará por pantalla todo lo que se encuentre entre estos dos valores
void cCamera::SetPerspective (float lfFVOVY_Rad, float lfAspect, float lfZNear, float lfZFar)
{
	mProj.LoadPerpective (lfFVOVY_Rad, lfAspect, lfZNear, lfZFar);
	RefreshViewProj();
}