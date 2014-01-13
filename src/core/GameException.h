#ifndef H_GAME_EXCEPTION_
#define H_GAME_EXCEPTION_

#include "GameConstants.h"

#include <exception>
#include <string>

class GameException : public std::exception
{
	private:
		int m_ExceptionId;
		std::string m_Message;
		int m_LineNumber;
	
	public:
		GameException(int exceptionId);
		GameException(int exceptionId, std::string exceptionMessage);
		GameException(int exceptionId, const char* exceptionMessage);
		GameException(int exceptionId, int line, const char* file);
		GameException(int exceptionId, std::string exceptionMessage, int line, const char* file);
		GameException(int exceptionId, const char* exceptionMessage, int line, const char* file);

		virtual const char* what() const noexcept;
		int exceptionId() const noexcept;
};

#ifdef DEBUG
	#define THROW_GAME_EXCEPTION(...) throw GameException(__VA_ARGS__, __LINE__, __FILE__)
	#define THROW_GAME_EXCEPTION(...) throw GameException(__VA_ARGS__, __LINE__, __FILE__)
#else
	#define THROW_GAME_EXCEPTION(...) throw GameException(__VA_ARGS__)
	#define THROW_GAME_EXCEPTION(...) throw GameException(__VA_ARGS__)
#endif


#endif
