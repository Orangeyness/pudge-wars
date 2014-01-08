#include "GameException.h"
#include <sstream>
#include <iomanip>

// Local helpers
std::string int_to_hex_string(int number);

GameException::GameException(int exceptionId)
{
	m_ExceptionId = exceptionId;

	m_Message = std::string("Game Exception Occured (ID: ") 
				+ int_to_hex_string(m_ExceptionId)
				+ std::string(")");
}

GameException::GameException(int exceptionId, std::string exceptionMessage)
{
	m_ExceptionId = exceptionId;

	m_Message = std::string("Game Exception Occured (ID: ") 
				+ int_to_hex_string(exceptionId)
				+ std::string("), ") 
				+ exceptionMessage;
}

GameException::GameException(int exceptionId, const char* exceptionMessage)
{
	m_ExceptionId = exceptionId;

	m_Message = std::string("Game Exception Occured (ID: ") 
				+ int_to_hex_string(exceptionId)
				+ std::string("), ")
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


// Converts number to a string with its hexadecimal representation
std::string int_to_hex_string(int number)
{
	std::stringstream stream;
	stream 	<< "0x" 
    		<< std::setfill ('0') << std::setw(sizeof(int)*2) 
    		<< std::hex << number;

	return stream.str();
}
