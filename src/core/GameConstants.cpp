#include "GameConstants.h"

#include <sstream>
#include <iomanip>

// Converts number to a string with its hexadecimal representation
std::string int_to_hex_string(int number)
{
	std::stringstream stream;
	stream 	<< "0x" 
    		<< std::setfill ('0') << std::setw(sizeof(int)*2) 
    		<< std::hex << number;

	return stream.str();
}
