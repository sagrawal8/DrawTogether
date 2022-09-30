//
// Created by Kate Everett on 11/27/21.
//

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <string>
#include <memory>
#include "BaseShape.hpp"

class Triangle : public BaseShape {
    std::string name;

//    int getX() override;
//    int getY() override;

public:

    //Parameterised Constructor to accept x and y co-ordinates
    Triangle(std::string name, int x, int y, std::shared_ptr<App> appObj);
};

#endif
