//
// Created by Jason Miller on 12/4/21.
//

#include <sfml/Graphics.hpp>
#include "PaintCanvas.hpp"
#include <cassert>

/*
 * Constructor for PaintCanvas. This method initializes the window height and width along with
 * initializing window, image, texture and sprite.
 * Takes in two parameters - width and height of window.
 * */
PaintCanvas::PaintCanvas(int width, int height) {
    m_window_width = width;
    m_window_height = height;

    // Create our window
    m_window = new sf::RenderWindow(sf::VideoMode(m_window_width, m_window_height), "Mini-Paint Project v1.3");
    m_window->setVerticalSyncEnabled(true);

    // Create an image which stores the pixels we will update
    m_image = new sf::Image;
    m_image->create(m_window_width, m_window_height, sf::Color::White);
    assert(m_image != nullptr && "m_image != nullptr");

    // Create a texture which lives in the GPU and will render our image
    m_texture = new sf::Texture;
    m_texture->loadFromImage(*m_image);
    assert(m_texture != nullptr && "m_texture != nullptr");

    // Create a sprite which is the entity that can be textured
    m_sprite = new sf::Sprite;
    m_sprite->setTexture(*m_texture);
    assert(m_sprite != nullptr && "m_sprite != nullptr");
}

/*
 * Destructor for PaintCanvas.
 * */
PaintCanvas::~PaintCanvas() {
    delete m_image;
    delete m_sprite;
    delete m_texture;
}

/*
 * Getter method for Image.
 * */
sf::Image& PaintCanvas::GetImage() {
    return *m_image;
}

/*
 * Getter method for Sprite.
 * */
sf::Sprite& PaintCanvas::GetSprite() {
    return *m_sprite;
}

/*
 * Getter method for Texture.
 * */
sf::Texture& PaintCanvas::GetTexture() {
    return *m_texture;
}

/*
 * Getter method for Window.
 * */
sf::RenderWindow& PaintCanvas::GetWindow() {
    return *m_window;
}

/*
 * Getter method for Window Width.
 * */
int PaintCanvas::GetWindowWidth() {
    return m_window_width;
}

/*
 * Getter method for Window Height.
 * */
int PaintCanvas::GetWindowHeight() {
    return m_window_height;
}

/*
 * This method is responsible for getting the pixel color at
 * coordinates (x,y).
 * Takes in two parameters: x coordinate and y coordinate.
 * */
sf::Color PaintCanvas::GetPixelColor(int x, int y) {
    if (!CheckCoordinates(x,y)) return sf::Color::Transparent;
    return m_image->getPixel(x, y);
}

/*
 * This method is responsible for setting the pixel color at
 * coordinates (x,y).
 * Takes in two parameters: x coordinate and y coordinate.
 * */
bool PaintCanvas::SetPixelColor(int x, int y, sf::Color color) {
    if (!CheckCoordinates(x,y) || GetPixelColor(x,y) == color) return false;
    m_image->setPixel(x, y, color);

    return true;
}

/*
 * This method is responsible for resetting the canvas to its original state.
 * ie. a blank white canvas.
 * */
bool PaintCanvas::ResetCanvas(){
    m_image->create(m_window_width, m_window_height, sf::Color::White);
    m_texture->loadFromImage(*m_image);
    m_sprite->setTexture(*m_texture);
    return true;
}

/*
 * This method is responsible for adding a shape to the canvas.
 * It takes in four parameters: x coordinate, y coordinate, color and points.
 * Points determines what shape is drawn ie. Square, circle, triangle.
 * */
bool PaintCanvas::AddShape(int x, int y, sf::Color color, int points) {
    if (!CheckCoordinates(x, y)) return false;
    sf::CircleShape shape(5, points);
    shape.setOutlineThickness(10);
    shape.setOutlineColor(color);
    shape.setPosition(x, y);
    if (!m_shapes.empty()) {
        sf::CircleShape top = m_shapes.back();
        bool equalRadius = top.getRadius() == shape.getRadius();
        bool equalPoints = top.getPointCount() == shape.getPointCount();
        bool equalCoordinates = top.getPosition() == shape.getPosition();
        bool equalColor = top.getOutlineColor() == shape.getOutlineColor();
        bool equalThickness = top.getOutlineThickness() == shape.getOutlineThickness();
        if (equalRadius && equalPoints && equalCoordinates && equalColor && equalThickness) return false;
    }
    m_shapes.push_back(shape);
    return true;
}

/*
 * This method removes the last shape from the m_shapes deque.
 * */
bool PaintCanvas::RemoveLastShape() {
    if (m_shapes.empty()) return false;
    m_shapes.pop_back();
    return true;
}

/*
 * This method checks whether the passed in coordinates are within the window.
 * Takes in two parameters: x coordinate, y coordinate.
 * */
bool PaintCanvas::CheckCoordinates(int x, int y) {
    if (x < 0 || x > m_window_width || y < 0 || y > m_window_height) return false;
    return true;
}

/*
 * This method draws the shapes in m_shapes stack on the canvas.
 * */
void PaintCanvas::LoopOnce() {
    m_window->draw(*m_sprite); // Update the texture
    for (auto& shape : m_shapes) m_window->draw(shape);
}

/*
 * This method loads and refreshes the texture using the image.
 * */
void PaintCanvas::Refresh() {
    static int refreshRate = 0;
    ++refreshRate;

    if (refreshRate > 10) {
        m_texture->loadFromImage(*m_image);
        refreshRate = 0;
    }
}

/*
 * Getter method for the queue that stores the shapes.
 * */
std::deque<sf::CircleShape>* PaintCanvas::GetShapes() {
    return &m_shapes;
}
