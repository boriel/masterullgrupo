/*
Calse GenericDevice. Contiene una serie de m�todos que debe debe implementar un dispositivo para ser soportado
					por el InputManager. Esta interfaz esta trabaja con dispositivos en modo encuesta, lo que 
					significa que nuestra aplicaci�n pregunta cada cierto tiempo acerca del estado del dispositivo.
*/

#ifndef GenericDevice_H
#define GenericDevice_H


class cGenericDevice
{
	public:
		virtual void Init() = 0;
		virtual void Deinit(void) = 0;
		virtual void Update(void) = 0;
		virtual float Check(unsigned luiEntry) = 0;
		virtual bool IsValid(void) = 0;

};


#endif