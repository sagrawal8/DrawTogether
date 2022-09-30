//
// Created by Kate Everett on 11/27/21.
//

#include <Circle.hpp>
#include <memory>

Circle::Circle(std::string name, int x, int y, std::shared_ptr <App> appObj) : BaseShape(name, x, y, appObj) {
    // Initialize Circle object
    this->m_shape->setPointCount(30);
}

