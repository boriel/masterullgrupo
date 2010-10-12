/*
Class Camera.h. 
		Esta clase contendrá la cámera, que es lo que se nos muestra en la pantalla.
		
*/

#ifndef Camera_H
#define Camera_H

#include "..\MathLib\MathLib.h"


class cCamera
{

	private:
		cMatrix mView;
		cMatrix mProj;
		cMatrix mViewProj;


	public:
		void Init();

		inline void RefreshViewProj() { mViewProj = mView * mProj; } //Actualiza la matrix mViewProj

		void SetLookAt (const cVec3 &lvPosition, const cVec3 &lvTarget, const cVec3 &lvUpWorld);
		void SetOrtho (float lfLeft, float lfRight, float lfBottom, float lfTop, float lfZNear, float lfZNFar);
		void SetPerspective (float lfFVOVY_Rad, float lfAspect, float lfZNear, float lfZFar);


		//Nos devuelven información relativa a la orientación y posición de la cámara
		cVec3 GetFront ()			const { mView.GetFront();			}
		cVec3 GetLeft ()			const { mView.GetLeft();			}
		cVec3 GetRight ()			const { mView.GetRight();			}
		cVec3 GetUp ()				const { mView.GetUp();				}
		cVec3 Getposition ()	const { mView.GetPosition();	}

		//Nos devuelven las matrices con las que trabajamos
		const cMatrix &GetView() const { return mView; }
		const cMatrix &GetProj() const { return mProj; }
		const cMatrix &GetViewProj() const { return mViewProj; }

};



#endif