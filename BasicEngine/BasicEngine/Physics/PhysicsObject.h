/*
clase 
	Representa un fisica de un objeto determinado
*/

#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H


#include <string>

#include "PhysicObjectType.h"
#include "..\MathLib\MathLib.h"

#include "btBulletDynamicsCommon.h" 

class cPhysicsObject 
{
	public:
		//void Init( const std::string &lacNameID);
		virtual void Update() {};
		//void Deinit(void);
		std::string GetNameID(void) { return macNameID; }
		ePhysicObjectType GetType(void) { return meType; }
		
		//cVec3 GetPosition ();
		//Sacados de btlDebugDraw
		void RenderTransformDebug(const btTransform& lbtTransform, btScalar lbtOrthoLen);
		void RenderBoxDebug(const btVector3& lbtMin, const btVector3& lbtMax, const btTransform& lbtTransform, const btVector3& lbtColor);
		void RenderPlaneDebug(const btVector3& lbtPlaneNormal, btScalar lbtPlaneConst, const btTransform& lbtTransform, const btVector3& lbtColor);
		void RenderObjectDebug();  //Probablemente no usada!

		cVec3 GetPosition ();
		cQuaternion GetQuatRotation();
		btQuaternion CambiarEje (const cQuaternion &lRotQuat);


	protected:
		std::string macNameID;
		ePhysicObjectType meType;

		btRigidBody* mpbtRigidBody;   //Cuerpo rigido o posicion
		btCollisionShape* mpbtShape;  //malla de collsion  (solo una malla)
		//btAlignedObjectArray<btCollisionShape*> mapbtCollisionShapes;  //No hecho todavía, pero por aqui van los tiros!!!!
		btScalar mbtMass;
		btVector3 mbtFallInertia;

		//btQuaternion CambiarEje(cVec3 lbtRot, float lfAngulo); //con esto le damos la vuelta al eje , ya que a saber como vienen las figuras NO USADO!!!!!!
		

};

#endif