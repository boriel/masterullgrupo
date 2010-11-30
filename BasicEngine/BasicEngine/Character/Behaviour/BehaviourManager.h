#ifndef BEHAVIOURMANAGER_H
#define BEHAVIOURMANAGER_H

#include <list>

#include "../../Utility/Singleton.h"
#include "behaviourbase.h"

enum eBehaviours {
	eCHASER_NO_ORIENTATION = 0,
	eCHASER_SNAP_ORIENTATION,
	eCHASER_WITH_ORIENTATION,
	ePATROL,

	eBEHAVIOURS_Count
};


class cBehaviourManager: public cSingleton<cBehaviourManager> {

private:
	typedef std::list<cBehaviourBase*> cBehaviourList;
	typedef cBehaviourList::iterator cBehaviourListIt;

	cBehaviourList mBehaviours; //Lista de comportamientos

public:
	bool Init();
	bool Deinit();

	cBehaviourBase* CreateBehaviour( eBehaviours leBehaviour );
	void DestroyBehaviour(cBehaviourBase* lpBehaviour);
};


#endif
