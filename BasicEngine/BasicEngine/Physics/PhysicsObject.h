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

using namespace std;

class cPhysicsObject 
{
	public:
		void Init(const cVec3 &lPosition, const cQuaternion &lRotacionInicial);
		void ApplyImpulse(const cVec3 &lImpulse);

		virtual void Update() {};
		//void Deinit(void);
		std::string GetNameID(void) { return macNameID; }
		ePhysicObjectType GetType(void) { return meType; }
		
		//cVec3 GetPosition ();
		//Sacados de btlDebugDraw
		//void RenderTransformDebug(const btTransform& lbtTransform, btScalar lbtOrthoLen);
		//void RenderBoxDebug(const btVector3& lbtMin, const btVector3& lbtMax, const btTransform& lbtTransform, const btVector3& lbtColor);
		//void RenderPlaneDebug(const btVector3& lbtPlaneNormal, btScalar lbtPlaneConst, const btTransform& lbtTransform, const btVector3& lbtColor);
		//void RenderObjectDebug();  //Probablemente no usada!
		//void RenderAllObjectDebug ();  //No usado
		//void RenderObjectDebug(const btTransform& worldTransform, const btCollisionShape* shape, const btVector3& color);
		btRigidBody* LocalCreateRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape);
		//void LoadObjectsXmlCollision();

		//inline void SetTypeObject (string lsType) { msType = lsType; }
		//inline std::string GetTypeObject () { return msType; }
		//inline void SetModelName (string lsModelName) { msModelName = lsModelName; }
		//inline std::string GetModelName () {return msModelName; }


		cVec3 GetPosition ();
		cQuaternion GetQuatRotation();
		btQuaternion CambiarEje (const cQuaternion &lRotQuat);
		bool CreateBoxShape(cVec3 lVec3);


	protected:
		std::string macNameID;
		ePhysicObjectType meType;

		//std::string msModelName;
		//std::string msType;
		std::string msFilename;

		btRigidBody* mpbtRigidBody;   //Cuerpo rigido o posicion
		btCollisionShape* mpbtShape;  //malla de collsion  (solo una malla)
		//btAlignedObjectArray<btCollisionShape*> mapbtCollisionShapes;  //No hecho todav�a, pero por aqui van los tiros!!!!
		btScalar mbtMass;
		btVector3 mbtFallInertia;

		//btQuaternion CambiarEje(cVec3 lbtRot, float lfAngulo); //con esto le damos la vuelta al eje , ya que a saber como vienen las figuras NO USADO!!!!!!
		
		//Para el Vehicle
		btScalar	m_defaultContactProcessingThreshold;
};

#endif