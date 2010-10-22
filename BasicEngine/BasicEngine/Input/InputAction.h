/*
Clase InputAction.h. Esta clase representa el estado de las acciones l�gicas (Saltar, Aceptar, Salir, ...). 
*/

#ifndef InputAction_H
#define InputAction_H


class cInputAction
{
	private:
		float mfValue;
		float mfTimePressed;
		bool mbIsPressed;
		bool mbWasPressed;
		bool mbBecomeReleased;
		bool mbBecomePressed;



	public:
		void Init (void);
		void Deinit();
		void Update (float lfTimestep, float lfValue);
		inline bool GetIsPressed(void) const      { return mbIsPressed;      } //Indica si la acci�n esta activa o pulsada
		inline bool GetIsReleased(void) const     { return !mbIsPressed;     } //Indica si la acci�n no est� activa o no pulsada
		inline bool GetBecomePressed(void) const  { return mbBecomePressed;  } //Indica si la acci�n ha pasado de inactiva a activa. Solo devuelve true en el primer frame que la acci�n este activa.
		inline bool GetBecomeReleased(void) const { return mbBecomeReleased; } //Indica si la acci�n ha pasado de activa a inactiva. Solo devuelve true en el primer frame que la acci�n este inactiva.
		inline float GetPressedTime(void) const    { return mfTimePressed;   } //Devuelve el tiempo que la accion lleva activa
		inline float GetValue(void) const          { return mfValue;         }




};


#endif