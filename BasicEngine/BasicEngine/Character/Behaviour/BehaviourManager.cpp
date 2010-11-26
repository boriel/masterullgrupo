#include "BehaviourManager.h"
#include "ChaserNoOrientation.h"
#include "ChaserSnapOrientation.h"
#include "ChaserWithOrientation.h"

bool cBehaviourManager::Init()
{
	return true;
}


void cBehaviourManager::DestroyBehaviour(cBehaviourBase *lpBehaviour)
{
	for (cBehaviourListIt i = mBehaviours.begin(); i != mBehaviours.end(); i++) {
		if ((*i) == lpBehaviour) {
			mBehaviours.erase(i);
			break;
		}
	}
}


cBehaviourBase* cBehaviourManager::CreateBehaviour( eBehaviours leBehaviour )
{
	cBehaviourBase *result;

	switch (leBehaviour) {

		case eCHASER_NO_ORIENTATION:
			result = new cChaserNoOrientation();
			break;

		case eCHASER_SNAP_ORIENTATION:
			result = new cChaserSnapOrientation();
			break;

		case eCHASER_WITH_ORIENTATION:
			result = new cChaserWithOrientation();
			break;

		default:
			// Aquí debería ir una excepción
			throw;
	}

	mBehaviours.push_back(result);

	return result;
}


bool cBehaviourManager::Deinit()
{
	while (!mBehaviours.empty()) {
		DestroyBehaviour(*mBehaviours.begin());
	}

	return true;
}
