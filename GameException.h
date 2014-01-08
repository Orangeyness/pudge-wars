#ifndef _GAME_EXCEPTION_
#define _GAME_EXCEPTION_

#include "ExceptionIds.h"

#include <exception>
#include <string>

class GameException : public std::exception
{
	private:
		int m_ExceptionId;
		std::string m_Message;

	public:
		GameException(int exceptionId);
		GameException(int exceptionId, std::string exceptionMessage);
		GameException(int exceptionId, const char* exceptionMessage);

		virtual const char* what() const noexcept;
		int exceptionId() const noexcept;

};


#endif
