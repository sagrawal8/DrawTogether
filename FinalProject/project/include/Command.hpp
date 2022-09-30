/** 
 *  @file   Command.hpp 
 *  @brief  Represents an actionable command by the user.
 *  @author Mike and Archita Sundaray
 *  @date   2021-11-09
 ***********************************************/
#ifndef COMMAND_HPP
#define COMMAND_HPP

// Include our Third-Party SFML header
// #include ...
// Include standard library C++ libraries.
#include <string>
#include <SFML/Graphics.hpp>
// Project header files
// #include ...

// The command class
class Command{

protected:
    std::string m_commandDescription;
    int x;
    int y;
    sf::Color color;

public:
    Command(std::string commandDescription);
    //Parameterised Constructor
    Command(std::string commandDescription, int x, int y);
    // Destructor for a command
    virtual ~Command();

    // Returns true or false if the command was able to successfully
    // execute.
    // If it executes successfully, then that command is added to the
    // undo stack.
    // Each parameters also takes in a string name. While this may not be optimal,
    // it allows us to easily debug what each command is doing in a textual form.
    virtual bool execute() = 0;
    virtual bool undo() = 0;
//    virtual int getX() = 0;
//    virtual int getY() = 0;
};



#endif
