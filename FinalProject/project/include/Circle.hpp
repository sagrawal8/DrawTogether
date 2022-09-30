//
// Created by Kate Everett on 11/27/21.
//

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <string>
#include <memory>
#include "BaseShape.hpp"

class Circle : public BaseShape {
    std::string name;

//    int getX() override;
//    int getY() override;

public:

    //Parameterised Constructor to accept x and y co-ordinates
    Circle(std::string name, int x, int y, std::shared_ptr<App> appObj);
};

#endif
