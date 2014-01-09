#include "GameEngine.h"
#include "GameStateInterface.h"
#include "GameException.h"
#include "ExceptionIds.h"

#include "gtest/gtest.h"

class TestGameState : public GameStateInterface
{
	private:
		static int allocated_;

	public:
		bool m_Paused;
		int m_UpdateCount;
		int m_DrawCount;

		TestGameState() 
		{
 			m_Paused = false; 
			m_UpdateCount = 0;
			m_DrawCount = 0;
		}

		virtual void pause() { m_Paused = true; }
		virtual void resume() { m_Paused = false; }
		virtual void update(GameEngine* game) 
		{ 
			m_UpdateCount ++; 
			if (m_UpdateCount == 10) game->quit();
		}
		virtual void draw(GameEngine* game) { m_DrawCount++; }

		void* operator new(size_t allocation_size) 
		{
			allocated_++;
			return malloc(allocation_size);
		}

		void operator delete(void* block, size_t /* allocation_size */) 
		{
			allocated_--;
			free(block);
		}

		static int allocated() { return allocated_; }
};

int TestGameState::allocated_ = 0;

TEST(GameEngine, NoGameStateCausesException) 
{
	bool caughtException = false;

	GameEngine ge;
	ge.initialise();
	
	try 
	{	
		ge.run();
	}
	catch(GameException& e)
	{
		caughtException = true;
		ASSERT_EQ(e.exceptionId(), EXCEP_STATE_UNEXPECTED_EMPTY);
	}
	
	ASSERT_TRUE(caughtException);
}

TEST(GameEngine, PushedStateRunsToCompletion) 
{
	bool caughtException = false;

	TestGameState* state = new TestGameState(); 

	GameEngine ge;
	ge.initialise();
	ge.pushState(state);

	try 
	{	
		ge.run();
	}
	catch(GameException& e)
	{
		caughtException = true;
	}
	
	ASSERT_TRUE(!caughtException);
	ASSERT_EQ(state->m_UpdateCount, 10);
}

TEST(GameEngine, BackgroundStatesGetPaused)
{
	TestGameState* stateA = new TestGameState(); 
	TestGameState* stateB = new TestGameState(); 
	TestGameState* stateC = new TestGameState(); 

	GameEngine ge;
	ge.pushState(stateA);

	ASSERT_FALSE(stateA->m_Paused);

	ge.pushState(stateB);

	ASSERT_TRUE(stateA->m_Paused);
	ASSERT_FALSE(stateB->m_Paused);

	ge.pushState(stateC);

	ASSERT_TRUE(stateA->m_Paused);
	ASSERT_TRUE(stateB->m_Paused);
	ASSERT_FALSE(stateC->m_Paused);
}

TEST(GameEngine, LastPushedStateIsRunWhenNoPopping)
{
	bool caughtException = false;

	TestGameState* stateA = new TestGameState(); 
	TestGameState* stateB = new TestGameState(); 
	TestGameState* stateC = new TestGameState(); 

	GameEngine ge;
	ge.initialise();
	ge.pushState(stateA);
	ge.pushState(stateB);
	ge.pushState(stateC);

	try 
	{	
		ge.run();
	}
	catch(GameException& e)
	{
		caughtException = true;
	}
	
	ASSERT_TRUE(!caughtException);
	ASSERT_EQ(stateC->m_UpdateCount, 10);
	ASSERT_EQ(stateB->m_UpdateCount, 0);
	ASSERT_EQ(stateA->m_UpdateCount, 0);
}

TEST(GameEngine, PoppingResumeStates)
{
	TestGameState* stateA = new TestGameState(); 
	TestGameState* stateB = new TestGameState(); 
	TestGameState* stateC = new TestGameState(); 

	GameEngine ge;
	ge.pushState(stateA);
	ge.pushState(stateB);
	ge.pushState(stateC);

	ASSERT_TRUE(stateA->m_Paused);
	ASSERT_TRUE(stateB->m_Paused);
	ASSERT_FALSE(stateC->m_Paused);

	ge.popState();

	ASSERT_TRUE(stateA->m_Paused);
	ASSERT_FALSE(stateB->m_Paused);

	ge.popState();

	ASSERT_FALSE(stateA->m_Paused);
}

TEST(GameEngine, PoppingDeletesTopState)
{
	TestGameState* stateA = new TestGameState(); 
	TestGameState* stateB = new TestGameState(); 
	TestGameState* stateC = new TestGameState(); 

	ASSERT_EQ(TestGameState::allocated(), 3);

	GameEngine ge;
	ge.pushState(stateA);
	ge.pushState(stateB);
	ge.pushState(stateC);

	ge.popState();
	ASSERT_EQ(TestGameState::allocated(), 2);

	ge.popState();
	ASSERT_EQ(TestGameState::allocated(), 1);

	ge.popState();
	ASSERT_EQ(TestGameState::allocated(), 0);
}

TEST(GameEngine, PoppingWithNoStateThrowsException)
{
	bool caughtException = false;

	GameEngine ge;
	try 
	{	
		ge.popState();
	}
	catch(GameException& e)
	{
		caughtException = true;
		ASSERT_EQ(e.exceptionId(), EXCEP_STATE_UNEXPECTED_EMPTY);
	}
	
	ASSERT_TRUE(caughtException);
}

TEST(GameEngine, changeState)
{
	TestGameState* stateA = new TestGameState(); 
	TestGameState* stateB = new TestGameState(); 
	TestGameState* stateC = new TestGameState(); 

	ASSERT_EQ(TestGameState::allocated(), 3);

	GameEngine ge;
	ge.pushState(stateA);
	ge.pushState(stateB);
	ge.changeState(stateC);

	ASSERT_EQ(TestGameState::allocated(), 2);

	ge.initialise();
	ge.run();
	
	ASSERT_EQ(stateC->m_UpdateCount, 10);
	ASSERT_EQ(stateA->m_UpdateCount, 0);
}

TEST(GameEngine, DeletingGameEngineCleansUpState)
{
	TestGameState* stateA = new TestGameState(); 
	TestGameState* stateB = new TestGameState(); 
	TestGameState* stateC = new TestGameState(); 

	GameEngine* ge = new GameEngine();
	ge->pushState(stateA);
	ge->pushState(stateB);
	ge->pushState(stateC);

	ASSERT_EQ(TestGameState::allocated(), 3);

	delete ge;

	ASSERT_EQ(TestGameState::allocated(), 0);
}

TEST(GameEngine, DeletingGameEngineDoesntRedeletePoppedStates)
{
	TestGameState* stateA = new TestGameState(); 
	TestGameState* stateB = new TestGameState(); 
	TestGameState* stateC = new TestGameState(); 

	GameEngine* ge = new GameEngine();
	ge->pushState(stateA);
	ge->pushState(stateB);
	ge->pushState(stateC);

	ASSERT_EQ(TestGameState::allocated(), 3);

	ge->popState();
	ge->popState();

	ASSERT_EQ(TestGameState::allocated(), 1);

	delete ge;

	ASSERT_EQ(TestGameState::allocated(), 0);
}
