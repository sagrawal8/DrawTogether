/** 
 *  @file   main.cpp 
 *  @brief  Entry point into the program.
 *  @author Mike and Archita Sundaray
 *  @date   2021-11-09
 ***********************************************/

// Compile: Use a CMakeLists.txt to generate a build file or you can try compiling with:
// g++ -std=c++17 ./src/*.cpp -I./include/ -o App -lsfml-graphics -lsfml-window -lsfml-system
//
// Note:	If your compiler does not support -std=c++17,
//		    then try -std=c++14 then -std=c++11.
//
// HOW TO RUN
//
// ./App

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
// Include standard library C++ libraries.
#include <iostream>
#include <string>
#include <Square.hpp>
#include <Triangle.hpp>
#include <Circle.hpp>
#include <memory>
#include <SFML/Network.hpp>
// Project header files
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"
#include "clientnetwork.hpp"
#include "servernetwork.hpp"
#include "helper.hpp"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

/*! \brief 	Call any initialization functions here.
*		This might be for example setting up any
*		global variables, allocating memory,
*		dynamically loading any libraries, or
*		doing nothing at all.
*
*/
void initialization(void){
    std::cout << "Starting the App" << std::endl;
}

/*! \brief 	The update function presented can be simplified.
*		I have demonstrated two ways you can handle events,
*		if for example we want to add in an event loop.
*
*/
void update(std::shared_ptr<App> appObj){
    // Update our canvas
    sf::Event event;

    while(appObj->GetWindow().pollEvent(event)) {
//        if(event.type == sf::Event::MouseButtonPressed){
//            // Modify the pixel
//            App::mouseX = event.mouseMove.x;
//            App::mouseY = event.mouseMove.y;
//        }

        // Pressing numbers 1 through 8 allows to draw in different colors
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case (sf::Keyboard::Num1):
                    appObj->setColor(sf::Color::Black); //Num Key 1: Black
                    break;
                case (sf::Keyboard::Num2):
                    appObj->setColor(sf::Color::White); //Num Key 2: White
                    break;
                case (sf::Keyboard::Num3):
                    appObj->setColor(sf::Color::Red); //Num Key 3: Red
                    break;
                case (sf::Keyboard::Num4):
                    appObj->setColor(sf::Color::Green); //Num Key 4: Green
                    break;
                case (sf::Keyboard::Num5):
                    appObj->setColor(sf::Color::Blue); //Num Key 5: Blue
                    break;
                case (sf::Keyboard::Num6):
                    appObj->setColor(sf::Color::Yellow); //Num Key 6: Yellow
                    break;
                case (sf::Keyboard::Num7):
                    appObj->setColor(sf::Color::Magenta); //Num Key 7: Magenta
                    break;
                case (sf::Keyboard::Num8):
                    appObj->setColor(sf::Color::Cyan); //Num Key 8: Cyan
                    break;
                case (sf::Keyboard::S):
                    appObj->setMode(sf::Keyboard::S); // Switch to square mode
                    break;
                case (sf::Keyboard::T):
                    appObj->setMode(sf::Keyboard::T); // Switch to triangle mode
                    break;
                case (sf::Keyboard::C):
                    appObj->setMode(sf::Keyboard::C); // Switch to circle mode
                    break;
                case (sf::Keyboard::X):
                    appObj->setMode(sf::Keyboard::X); // Exit shape modes -> return to standard paint mode
                    break;
                case (sf::Keyboard::Z):
                    appObj->UndoCommand();
                    break;
                case (sf::Keyboard::Y):
                    appObj->RedoCommand();
                    break;
                case (sf::Keyboard::Escape):
                    appObj->GetWindow().close();
                    exit(EXIT_SUCCESS);
                default:
                    break;
            }
        }
    }

    // Pressing space bar will clear all pixels and will have a solid color with the last color selected
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        appObj->GetImage().create(WINDOW_WIDTH, WINDOW_HEIGHT, appObj->GetColor());
        appObj->GetTexture().loadFromImage(appObj->GetImage());
        appObj->GetSprite().setTexture(appObj->GetTexture());
    }

    // We can otherwise handle events normally
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i coordinate = sf::Mouse::getPosition(appObj->GetWindow());
        if ((appObj->mouseX >= 0 and appObj->mouseX <= 600) and (appObj->mouseY >= 0 and appObj->mouseY <= 400)) {
            appObj->mouseX = coordinate.x;
            appObj->mouseY = coordinate.y;
            sf::Vector2u window_size = appObj->GetWindow().getSize();

            //rejecting same commands and commands outside the window
            if ((coordinate.x != appObj->pmouseX || coordinate.y != appObj->pmouseY) and
                (coordinate.x >= 0 and coordinate.x <= window_size.x and coordinate.y >= 0 and
                coordinate.y <= window_size.y)) {

                // Modify the pixel or draw a shape
                Command* newPixel;
                if (appObj->GetMode() == sf::Keyboard::X) {
                    newPixel = new Draw("draw", coordinate.x, coordinate.y, appObj);
                } else if (appObj->GetMode() == sf::Keyboard::S) {
                    newPixel = new Square("square", coordinate.x, coordinate.y, appObj);
                } else if (appObj->GetMode() == sf::Keyboard::T) {
                    newPixel = new Triangle("triangle", coordinate.x, coordinate.y, appObj);
                } else if (appObj->GetMode() == sf::Keyboard::C) {
                    newPixel = new Circle("circle", coordinate.x, coordinate.y, appObj);
                }
                appObj->AddCommand(newPixel);
                appObj->ExecuteCommand();
                appObj->EmptyStack(); // to empty the stack after the execution of command
            }
        }
    }


    // Where was the mouse previously before going to the next frame
    appObj->pmouseX = appObj->mouseX;
    appObj->pmouseY = appObj->mouseY;
}


/*! \brief 	The draw call
*
*/
void draw(std::shared_ptr<App> appObj) {
    // Static variable
    static int refreshRate = 0;
    ++refreshRate;	// Increment


    // We load into our texture the modified pixels
    // But we only do so every 10 draw calls to reduce latency of transfer
    // between the GPU and CPU.
    // Ask yourself: Could we do better with sf::Clock and refresh once
    // 	 	 every 'x' frames?
    if(refreshRate>10) {
        appObj->GetTexture().loadFromImage(appObj->GetImage());
        refreshRate =0;
    }
}
 
void TCPClient(std::shared_ptr<App> appObj){
	ClientNetwork client_network;
	client_network.Connect("localHost",2000);
	client_network.Run(appObj);
}

void TCPServer(){
	ServerNetwork server_network(2000, false);
	server_network.Run();
}

void TCPnetwork(std::shared_ptr<App> appObj){
	std::string role = "undefined";
	std::cout <<"Enter (s) for server, enter (c) for client"<< std::endl;
	std::cin >> role;

	if(role[0] == 's')
	{
		TCPServer();
	}
	else if(role[0] == 'c'){
		TCPClient(appObj);
	}
}

/*! \brief 	The entry point into our program.
*
*/
int main() {



    // Call any setup function
    // Passing a function pointer into the 'init' function.
    // of our application.
    std::shared_ptr<App> appObj = std::make_shared<App>();

    appObj->Init(&initialization);
    // Setup your keyboard
    appObj->UpdateCallback(&update);
    // Setup the Draw Function
    appObj->DrawCallback(&draw);
    TCPnetwork(appObj);
    // Call the main loop function
//    appObj->Loop(appObj);
    // Destroy our app
    //appObj.Destroy();
    return 0;
}


