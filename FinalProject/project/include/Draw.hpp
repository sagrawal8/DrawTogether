/** 
 *  @file   Draw.hpp 
 *  @brief  Drawing actions interface. 
 *  @author Mike and Archita Sundaray
 *  @date   2021-11-09
 ***********************************************/
#ifndef DRAW_H
#define DRAW_H

// Include our Third-Party SFML header
// #include ...
// Include standard library C++ libraries.
#include <string>
// Project header files
#include "Command.hpp"

// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.
//
// In our Draw class note that we have also explicitly marked the
// functions as 'override' to indicate that these functions are
// overriding the behavior of functions in a base class
// that are implemented as virtual.
class Draw : public Command {
    std::string name;
    std::shared_ptr<App> appObj;

    bool execute() override;
    bool undo() override;
//    int getX() override;
//    int getY() override;

public:
    // Constructor for name
    Draw(std::string name);

    //Parameterised Constructor to accept x and y co-ordinates
    Draw(std::string name, int x, int y, std::shared_ptr<App> appObj);
};

#endif
