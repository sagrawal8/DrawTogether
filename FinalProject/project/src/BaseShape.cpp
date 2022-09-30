//
// Created by Kate Everett on 11/27/21.
//

#include <BaseShape.hpp>
#include <string>
#include <iostream>
#include <memory>

BaseShape::BaseShape(std::string name, int x, int y, std::shared_ptr<App> appObj) : Command(name, x, y) {
    this->name = name;
    this->x = x;
    this->y = y;
    this->appObj = appObj;
    this->color = this->appObj->GetColor();

    this->m_shape = new sf::CircleShape();

    this->m_shape->setPosition(this->x, this->y);
    this->m_shape->setRadius(25);
    this->m_shape->setOutlineThickness(5);
    this->m_shape->setOutlineColor(this->color);
}

bool BaseShape::execute() {
    this->appObj->getQueue()->push_back(*m_shape);
    return true;
}

bool BaseShape::undo() {
    this->appObj->getQueue()->pop_back();
    return true;
}

BaseShape::~BaseShape() {
    delete m_shape;
}



