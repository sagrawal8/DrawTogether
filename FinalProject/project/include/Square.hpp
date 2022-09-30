//
// Created by Kate Everett on 11/27/21.
//

#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "App.hpp"
#include "BaseShape.hpp"
#include <memory>

class Square : public BaseShape {
    std::string name;

//    int getX() override;
//    int getY() override;

public:

    //Parameterised Constructor to accept x and y co-ordinates
    Square(std::string name, int x, int y, std::shared_ptr<App> appObj);
};

#endif
