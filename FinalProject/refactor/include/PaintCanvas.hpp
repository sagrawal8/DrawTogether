//
// Created by Jason Miller on 12/4/21.
//

#ifndef PAINTCANVAS_HPP
#define PAINTCANVAS_HPP

#include <SFML/Graphics.hpp>

#include <deque>

class PaintCanvas {
private:
    sf::Image*                   m_image;
    sf::Sprite*                  m_sprite;
    sf::Texture*                 m_texture;
    sf::RenderWindow*            m_window;
    int                          m_window_width, m_window_height;
    std::deque<sf::CircleShape>  m_shapes;

    bool CheckCoordinates(int x, int y);


public:
    // Constructors & Destructor //
    PaintCanvas(int width = 600, int height = 400);
    PaintCanvas(const PaintCanvas& orig);
    ~PaintCanvas();

    // Getters //
    sf::Image&        GetImage();
    sf::Sprite&       GetSprite();
    sf::Texture&      GetTexture();
    sf::RenderWindow& GetWindow();
    sf::Color         GetPixelColor(int x,int y);
    int               GetWindowWidth();
    int               GetWindowHeight();
    std::deque<sf::CircleShape>* GetShapes();

    // Setters //
    bool SetPixelColor(int x, int y, sf::Color);
    bool AddShape(int x, int y, sf::Color, int points);
    bool RemoveLastShape();
    bool ResetCanvas();

    void Refresh();
    void LoopOnce();
};

#endif // PAINTCANVAS_HPP
