//
// Created by Kate Everett on 12/4/21.
//

#ifndef PAINTCANVAS_HPP
#define PAINTCANVAS_HPP

// Member Attributes/Methods of the shared Paint Canvas

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class PaintCanvas {

private:
//    Member Attributes
    // Main image
    sf::Image *m_image;
    // Create a sprite that we overlay
    // on top of the texture.
    sf::Sprite *m_sprite;
    // Texture sent to the GPU for rendering
    sf::Texture *m_texture;
    // Our rendering window
    sf::RenderWindow *m_window;

    sf::Color m_color;
    sf::Keyboard::Key m_mode;

//    TODO: Do we need these callback functions? I feel like we could potentially move the code
//           from these functions that are in main directly into these methods in here since
//           we're factoring out the command stuff. Alternatively, we could move the code from
//           main into the CommandHistory class?
//    Member functions
    // Store the address of our function pointer
    // for each of the callback functions.
//    std::function<void(void)> m_initFunc;
//    std::function<void(std::shared_ptr<App> appObj)> m_updateFunc;
//    std::function<void(std::shared_ptr<App> appObj)> m_drawFunc;

public:
//    Member Variables
    unsigned int pmouseX, pmouseY, mouseX, mouseY;

//    Member Fucnctions
      // Default Constructor/Destructor
          PaintCanvas();

    sf::Image &GetImage();
    sf::Texture &GetTexture();
    sf::RenderWindow &GetWindow();
    sf::Sprite &GetSprite();

    sf::Color GetColor();
    void setColor(sf::Color color);

    sf::Keyboard::Key GetMode();
    void setMode(sf::Keyboard::Key mode);
};

#endif
