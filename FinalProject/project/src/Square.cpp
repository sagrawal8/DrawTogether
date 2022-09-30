//
// Created by Kate Everett on 11/27/21.
//

#include <Square.hpp>
#include "App.hpp"
#include <memory>

#include "helper.hpp"



Square::Square(std::string name, int x, int y, std::shared_ptr<App> appObj) : BaseShape(name, x, y, appObj){
    // Initialize Square object
    this->m_shape->setPointCount(4);
}




