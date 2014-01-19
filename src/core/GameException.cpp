#include "core/GameException.h"

GameException::GameException(int exceptionId)
{
	m_ExceptionId = exceptionId;
	m_LineNumber = -1;
	
	m_Message = std::string("Game Exception Occured (ID: ") 
				+ int_to_hex_string(m_ExceptionId)
				+ std::string(")");
}

GameException::GameException(int exceptionId, std::string exceptionMessage)
{
	m_ExceptionId = exceptionId;
	m_LineNumber = -1;

	m_Message = std::string("Game Exception Occured (ID: ") 
				+ int_to_hex_string(exceptionId)
				+ std::string("), ") 
				+ exceptionMessage;
}

GameException::GameException(int exceptionId, const char* exceptionMessage)
{
	m_ExceptionId = exceptionId;
	m_LineNumber = -1;

	m_Message = std::string("Game Exception Occured (ID: ") 
				+ int_to_hex_string(exceptionId)
				+ std::string("), ")
				+ std::string(exceptionMessage);
}

GameException::GameException(int exceptionId, int line, const char* file)
{
	m_ExceptionId = exceptionId;
	m_LineNumber = line;

	m_Message = std::string("Game Exception Occured (ID: ") 
				+ int_to_hex_string(m_ExceptionId)
				+ std::string(") on line #")
				+ std::to_string(m_LineNumber)
				+ std::string(" in file ")
				+ std::string(file);
}

GameException::GameException(int exceptionId, std::string exceptionMessage, int line, const char* file)
{
	m_ExceptionId = exceptionId;
	m_LineNumber = line;

	m_Message = std::string("Game Exception Occured (ID: ") 
				+ int_to_hex_string(m_ExceptionId)
				+ std::string(") on line #")
				+ std::to_string(m_LineNumber)
				+ std::string(" in file ")
				+ std::string(file)
				+ std::string(". ")
				+ exceptionMessage;
}

GameException::GameException(int exceptionId, const char* exceptionMessage, int line, const char* file)
{
	m_ExceptionId = exceptionId;
	m_LineNumber = line;

	m_Message = std::string("Game Exception Occured (ID: ") 
				+ int_to_hex_string(m_ExceptionId)
				+ std::string(") on line #")
				+ std::to_string(m_LineNumber)
				+ std::string(" in file ")
				+ std::string(file)
				+ std::string(". ")
				+ std::string(exceptionMessage);
}

const char* GameException::what() const noexcept
{
	return m_Message.c_str();
}

int GameException::exceptionId() const noexcept
{
	return m_ExceptionId;
}

