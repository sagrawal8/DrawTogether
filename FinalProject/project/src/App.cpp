/** 
 *  @file   App.cpp 
 *  @brief  Main class for program
 *  @author Mike and Archita Sundaray
 *  @date   2021-11-09
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
//#include <SFML/OpenGL.hpp>
// Include standard library C++ libraries.
#include <cassert>
#include <memory>
#include <iostream>
// Project header files
#include "App.hpp"
#include "helper.hpp"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

//Constructor
App::App() {
    this->pmouseX = 0;
    this->pmouseY = 0;
    this->mouseX = 0;
    this->mouseY = 0;

    this->m_window = nullptr;
    this->m_image = new sf::Image;
    this->m_sprite = new sf::Sprite;
    this->m_texture = new sf::Texture;
}

//Destructor
App::~App() {
    print("App destroyed");
    delete m_image;
    delete m_sprite;
    delete m_texture;

    while (!this->m_shapes.empty()) {
        m_shapes.pop_back();
    }

    while (!this->m_commands.empty()) {
        m_commands.pop();
    }

    while (!this->m_undo.empty()) {
        m_undo.pop();
    }
}

/*! \brief 	When we draw, we would prefer to add
*		a command to a data structure.
*
*/
void App::AddCommand(Command* c) {
    m_commands.push(c);
}

/*! \brief 	We should execute commands in a data structure
*		by picking up the top element and executing it.
*
*
*/
void App::ExecuteCommand() {
    Command *cmd = m_commands.top();
    cmd->execute();
}

/*! \brief 	We should undo commands in a data structure
*		by picking and popping the top element from m_commands
*       stack to m_undo stack.
*
*/
void App::UndoCommand() {
    if (!m_commands.empty()) {
        Command *undoCmd = m_commands.top();
        m_commands.pop();
        m_undo.push(undoCmd);
        undoCmd->undo();
    } else {
        print("No more commands to undo! Stop hitting 'Z'.");
    }
}

/*! \brief 	We should redo commands in a data structure
*		by picking up elements from m_undo stack and putting it
*       back onto m_commands stack to execute it.
*
*/
void App::RedoCommand() {
    if (!m_undo.empty()) {
        Command *redoCmd = m_undo.top();
        m_undo.pop();
        App::AddCommand(redoCmd);
        App::ExecuteCommand();
    } else {
        print("No more commands to redo! Stop hitting 'Y'.");
    }
}

/*! \brief 	We should empty the stack when
*		new commands are entered
*
*/
void App::EmptyStack() {
    while (m_undo.size() > 0) {
        m_undo.pop();
    }
}


/*! \brief 	Return a reference to our m_image, so that
*		we do not have to publicly expose it.
*
*/
sf::Image& App::GetImage() {
    return *m_image;
}

/*! \brief 	Return a reference to our m_Texture so that
*		we do not have to publicly expose it.
*
*/
sf::Texture& App::GetTexture() {
    return *m_texture;
}

/*! \brief 	Return a reference to our m_window so that we
*		do not have to publicly expose it.
*
*/
sf::RenderWindow& App::GetWindow() {
    return *m_window;
}

sf::Color App::GetColor() {
    return m_color;
}

void App::setColor(sf::Color color) {
    this->m_color = color;
}

sf::Sprite &App::GetSprite() {
    return *m_sprite;
}

/*! \brief 	Destroy we manually call at end of our program.
*
*/
//void App::Destroy() {
//    delete m_image;
//    delete m_sprite;
//    delete m_texture;
//}

/*! \brief 	Initializes the App and sets up the main
*		rendering window(i.e. our canvas.)
*/
void App::Init(std::function <void()> initFunction) {
    // Setup the context
    //sf::ContextSettings settings(24, 8, 4, 2, 2);
    // Create our window
    m_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mini-Paint Project v1.3",sf::Style::Titlebar);
    m_window->setVerticalSyncEnabled(true);
    //m_window->setActive(true);
    // Create an image which stores the pixels we will update
    m_image->create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color::White);
    assert(m_image != nullptr && "m_image != nullptr");
    // Create a texture which lives in the GPU and will render our image
    m_texture->loadFromImage(*m_image);
    assert(m_texture != nullptr && "m_texture != nullptr");
    // Create a sprite which is the entity that can be textured
    m_sprite->setTexture(*m_texture);
    assert(m_sprite != nullptr && "m_sprite != nullptr");
    // Set our initialization function to pedrform any user
    // initialization
    m_initFunc = initFunction;

    //setting default pixel colour to White
    m_color = sf::Color::White;

    // Default draw mode is individual pixels (X)
    m_mode = sf::Keyboard::X;
}

/*! \brief 	Set a callback function which will be called
		each iteration of the main loop before drawing.
*
*/
void App::UpdateCallback(std::function <void(std::shared_ptr<App> appObj)> updateFunction) {
    m_updateFunc = updateFunction;
}

/*! \brief 	Set a callback function which will be called
		each iteration of the main loop after update.
*
*/
void App::DrawCallback(std::function <void(std::shared_ptr<App> appObj)> drawFunction) {
    m_drawFunc = drawFunction;
}

/*! \brief Get current drawing mode of the App.
*
*/
sf::Keyboard::Key App::GetMode() {
    return m_mode;
}

/*! \brief Set current drawing mode of the App.
*
*/
void App::setMode(sf::Keyboard::Key mode) {
    m_mode = mode;
}

/*! \brief Get queue holding shapes on the screen.
*
*/
std::deque<sf::CircleShape>* App::getQueue() {
    return &m_shapes;
}

/*! \brief 	The main loop function which handles initialization
		and will be executed until the main window is closed.
		Within the loop function the update and draw callback
		functions will be called.
*
*/
void App::Loop(std::shared_ptr<App> appObj) {
    // Call the init function
    m_initFunc();

    // Start the main rendering loop
    while(m_window->isOpen()) {
        // Clear the window
        m_window->clear();
        // Updates specified by the user
        m_updateFunc(appObj);
        // Additional drawing specified by user
        m_drawFunc(appObj);
        // Update the texture
        // Note: This can be done in the 'draw call'
        // Draw to the canvas
        m_window->draw(*m_sprite);

        // Display any shapes
        for (auto & m_shape : m_shapes) {
            m_window->draw(m_shape);
        }
        // Display the canvas
        m_window->display();
    }
}







