#include "pudge-wars/pudge-states/PudgeState.h"

#include "core/GameException.h"

PudgeState::PudgeState() : m_NextState(NULL) { }
PudgeState::~PudgeState()
{
	if (m_NextState != NULL)
		delete m_NextState;
}

bool PudgeState::readyToChangeState() 
{ 
	return m_NextState != NULL; 
}

void PudgeState::changeState(PudgeState* next) 
{
	if (m_NextState != NULL) 
		THROW_GAME_EXCEPTION(EXCEP_STATE_ALREADY_CHANGED);

	m_NextState = next;
}

PudgeState* PudgeState::nextState()
{
	PudgeState* next = m_NextState;
	m_NextState = NULL;

	return next;
}


void PudgeState::attachHook(PudgeEntity& pudge, int hookId, const Vector2D& hookPosition)
{
	changeState(new PudgeOnHookState(pudge, hookPosition));
}

void PudgeState::moveToHook(PudgeEntity& pudge, const Vector2D& hookPosition) { }
void PudgeState::dettachHook(PudgeEntity& pudge) { }

void PudgeState::enter(PudgeEntity& pudge) { }
void PudgeState::exit(PudgeEntity& pudge) { }

