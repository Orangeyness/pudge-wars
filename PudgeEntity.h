#ifndef _PUDGE_ENTITY_
#define _PUDGE_ENTITY_

#include "GameEntityInterface.h"

class PudgeEntity : public GameEntityInterface
{
	private:
		int x;
		int y;

	public:
		PudgeEntity();
		virtual entityrtn_t update();
		virtual void draw();

};

#endif
