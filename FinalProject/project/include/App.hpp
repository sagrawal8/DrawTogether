/** 
 *  @file   App.hpp 
 *  @brief  App class interface
 *  @author Mike and Archita Sundaray
 *  @date   2021-11-09
 ***********************************************/
#ifndef APP_HPP
#define APP_HPP

// Project header files
// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <queue>
#include <stack>
#include <functional>
#include <memory>
#include "Command.hpp"

class App {

private:
// Member variables
    // Queue stores the next command to do.
    std::stack<Command *> m_commands;
    // Stack that stores the last action to occur.
    std::stack<Command *> m_undo;

    // Shape queue
    std::deque<sf::CircleShape> m_shapes;

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

// Member functions
    // Store the address of our function pointer
    // for each of the callback functions.
    std::function<void(void)> m_initFunc;
    std::function<void(std::shared_ptr<App> appObj)> m_updateFunc;
    std::function<void(std::shared_ptr<App> appObj)> m_drawFunc;

public:
// Member Variables
    // Keeps track of the previous mouse and current mouse positions
    // 'pmouse' is where the mouse previously was.
    // 'mouse' records where the mouse currently is.
    // Note: Occasionally I break my rules of always having a getter/setter
    //	 function for each member variable if there's reason to.
    //   	 There is some overhead associated with calling these functions,
    // 	 and even with 'inline' there is no guarantee that the functions
    //  	 do get inlined. Other commercial and open source APIs seem
    // 	 to do this on occasion--use your digression and expression to
    // 	 make an informed choice if exposing these variables is safe, fast,
    // 	 and going to be more maintainable in the long run. In the end--it's
    // 	 still risky to expose anything as public.
    unsigned int pmouseX, pmouseY, mouseX, mouseY;

// Member functions
    // Default constructor which is public
    App();
    ~App();

    void AddCommand(Command *c);
    void ExecuteCommand();
    void UndoCommand();
    void RedoCommand();
    void EmptyStack();

    sf::Image &GetImage();
    sf::Texture &GetTexture();
    sf::RenderWindow &GetWindow();
    sf::Sprite &GetSprite();

    sf::Color GetColor();
    void setColor(sf::Color color);

    sf::Keyboard::Key GetMode();
    void setMode(sf::Keyboard::Key mode);

    std::deque<sf::CircleShape>* getQueue();

    //void Destroy();
    void Init(std::function <void()> initFunction);
    void UpdateCallback(std::function <void(std::shared_ptr<App> appObj)> updateFunction);
    void DrawCallback(std::function <void(std::shared_ptr<App> appObj)> drawFunction);
    void Loop(std::shared_ptr<App> appObj);
    void printUndos();

};


#endif
