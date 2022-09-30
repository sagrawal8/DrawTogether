//
// Created by Kate Everett on 12/4/21.
//

#include "PaintCanvas.hpp"

PaintCanvas::PaintCanvas() {
    this->pmouseX = 0;
    this->pmouseY = 0;
    this->mouseX = 0;
    this->mouseY = 0;

    this->m_window = nullptr;
    this->m_image = new sf::Image;
    this->m_sprite = new sf::Sprite;
    this->m_texture = new sf::Texture;
}

/*! \brief 	Return a reference to our m_image, so that
*		we do not have to publicly expose it.
*
*/
sf::Image& PaintCanvas::GetImage() {
    return *m_image;
}

/*! \brief 	Return a reference to our m_Texture so that
*		we do not have to publicly expose it.
*
*/
sf::Texture& PaintCanvas::GetTexture() {
    return *m_texture;
}

/*! \brief 	Return a reference to our m_window so that we
*		do not have to publicly expose it.
*
*/
sf::RenderWindow& PaintCanvas::GetWindow() {
    return *m_window;
}

sf::Color PaintCanvas::GetColor() {
    return m_color;
}

void PaintCanvas::setColor(sf::Color color) {
    this->m_color = color;
}

sf::Sprite &PaintCanvas::GetSprite() {
    return *m_sprite;
}

