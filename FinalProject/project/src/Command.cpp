/** 
 *  @file   Command.cpp 
 *  @brief  Implementation of Command.hpp
 *  @author Mike and Archita Sundaray
 *  @date   2021-11-09
 ***********************************************/

// Include our Third-Party SFML header
// #include ...
// Include standard library C++ libraries.
#include <string>
#include <memory>
// Project header files
#include "Command.hpp"

/*! \brief 	N/A
*
*/
Command::Command(std::string commandDescription) : m_commandDescription(commandDescription) {}

Command::Command(std::string commandDescription, int x, int y) : m_commandDescription(commandDescription) {}

/*! \brief 	N/A
*		
*/
Command::~Command(){
}
