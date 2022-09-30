//
// Created by Kate Everett on 11/27/21.
//

#ifndef BASESHAPE_HPP
#define BASESHAPE_HPP

#include "Command.hpp"
#include "App.hpp"
#include <memory>

class BaseShape : public Command {
    std::string name;

    bool execute() override;
    bool undo() override;

protected:
    std::shared_ptr<App> appObj;
    sf::CircleShape* m_shape;
public:

    //Parameterised Constructor to accept x and y co-ordinates
    BaseShape(std::string name, int x, int y, std::shared_ptr<App> appObj);
    virtual ~BaseShape() override;
};

#endif
