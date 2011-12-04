#include "ChaserWithOrientationBehaviour.h"

void cChaserWithOrientationBehaviour::Update(float lfTimestep)
{
	float lfCosAngle;
	float lfAngle;
	float lfAngleDisplacement;

	//Calcular el vector distancia (diferencia entre la posici�n del
	//perseguidor y la posici�n del objetivo a perseguir)
	cVec3 lDistanceVec = mTarget - mpCharacter->GetPosition();
	float lfDistance = lDistanceVec.Length();
	
	cPlane lPlane;

	//Si la distancia al objetivo es pr�cticamente cero, lo ha alcanzado.
	//Debemos poner esta condici�n, ya que debido a errores de precisi�n,
	//es posible que nunca se alcance una distancia 0.0f al objetivo y el
	//perseguidor permanezca dando vueltas alrededor de �l.
	if (lDistanceVec.Length() < 0.1f) {
		mpCharacter->SetPosition(mTarget);
		return;
	}

	//Para mover la orientaci�n del perseguidor es necesario calcular el
	//�ngulo que hay entre el Front del perseguidor y el vector Distance
	//(el cual marca la direcci�n en la que est� el objetivo). Usaremos
	//para ello el Dot Product que nos devuelve el coseno del �ngulo que
	//buscamos.
	lfCosAngle = Dot(mpCharacter->GetFront(), lDistanceVec.Normalize() );

	//El Dot Product (producto escalar) devuelve el coseno del �ngulo
	//entre dos vectores si �stos est�n normalizados. Debe devolver un
	//valor entre [-1,1]. En ocasiones, por problemas internos de redondeo
	//da valores algo mayores (como 1.0000001f) que pueden dar problemas.
	//Por ello a�adimos el siguiente c�digo:
	if ( lfCosAngle > 1.0f )
		lfCosAngle = 1.0f;
	else if (lfCosAngle < -1.0f )
		lfCosAngle = -1.0f;

	//Ahora podemos calcular cu�l es ese �ngulo, es decir, cu�ntos
	//radianes se debe girar el perseguidor para alinearse con el punto
	//objetivo teniendo en cuenta la orientaci�n actual(sabemos que el
	//valor de lfCosAngle va a estar entre [-1,1] con lo que no tendremos
	//problemas al llamar a acosf)
	lfAngle = acosf(lfCosAngle);

	//Calcular cu�ntos radianes se puede mover el perseguidor en este
	//frame teniendo en cuenta su velocidad angular
	lfAngleDisplacement = mpCharacter->GetAngSpeedX() * lfTimestep;

	//Si la cantidad de radianes que el personaje se puede mover este
	//frame (acorde a su velocidad angular) es menor que la cantidad de
	//radianes que deber�a girar para alinearse al objetivo, restringimos
	//la rotaci�n que vamos a realizar

	if (lfAngle > lfAngleDisplacement)
		lfAngle = lfAngleDisplacement;
	
	//Ahora se sabe cu�ntos radianes se debe mover el perseguidor, pero
	//�hacia qu� lado?�A su derecha o hacia su izquierda? Para ello se
	//debe hacer un Test del plano. Pasos:

	//Necesitamos el vector Right del perseguidor que ser� la normal del
	//plano que tenemos que usar. Este plano contiene al vector Front del
	//personaje y nos servir� para determinar si el punto objetivo est� a
	//la izquierda o derecha del perseguidor.

	//Hacemos el Test de plano. Si la posici�n del perseguidor esta
	//contenido en el plano (=0), a la derecha del Front (<0) o a la
	//izquierda del Front (>0)

	lPlane.Init(mpCharacter->GetRight(), mpCharacter->GetPosition());
	if ( lPlane.PointTest(mTarget) < 0.0f )
		mpCharacter->SetYaw(mpCharacter->GetYaw() + lfAngle);
	else
		mpCharacter->SetYaw(mpCharacter->GetYaw() - lfAngle);

	//Calcular la distancia que se mover� el perseguidor teniendo en
	//cuenta su velocidad m�xima
	float lfDisplacement = mpCharacter->GetSpeed() * lfTimestep;

	mpCharacter->SetPosition(mpCharacter->GetPosition() + (lfDisplacement * mpCharacter->GetFront()));
}

