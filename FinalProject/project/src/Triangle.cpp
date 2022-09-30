//
// Created by Kate Everett on 11/27/21.
//

#include <Triangle.hpp>
#include <memory>

Triangle::Triangle(std::string name, int x, int y, std::shared_ptr <App> appObj) : BaseShape(name, x, y, appObj) {
    // Initialize Triangle object
    this->m_shape->setPointCount(3);
}

