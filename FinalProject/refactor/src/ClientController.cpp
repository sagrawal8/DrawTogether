//
// Created by Jason Miller on 12/11/21.
//

#include <iostream>

#include "ClientController.hpp"

/*
 * Constructor for ClientController. 
 * This method gets the client connected to the server by asking 
 * the user for the IP address and port number.
 * */
ClientController::ClientController() {
    m_marker_color = sf::Color::Black;
    m_shape_point_count = 0;

    std::string ip;
    std::cout << "Please enter your IP Address (\"xxx.xxx.xxx.xxx\"): ";
    std::cin >> ip;

    unsigned short port;
    std::cout << "Please enter a port to connect to: ";
    std::cin >> port;

    m_connection.connect(ip, port);
}

/*
 * The loop that keeps running on the client end and is responsible for
 * refreshing the window with incoming commands as well as receiving incoming
 * commands from other clients.
 * */
void ClientController::run() {
PaintCanvas pc;

    while (pc.GetWindow().isOpen()) {
        pc.GetWindow().clear();

        pc.LoopOnce();
        pc.Refresh();
        pc.GetWindow().display();

        std::vector<std::string> command = m_connection.receive();

        if (command.size() > 0) Consume(command, pc);
        PollClientWindow(pc);
    }
}

/*
 * This method acts upon the received message in run().
 * An UNDO command sets the received pixel to White.
 * A Draw or Redo draws or adds a shape on the Canvas.
 * */
void ClientController::Consume(std::vector<std::string> &message, PaintCanvas &paintCanvas) {
     // Check for RESET
        if (message.size() == 1) {
            paintCanvas.ResetCanvas();
        }
        else if (message.size() == 5) {
            // UNDO
            if (message[0] == "UNDO") {
                // Check if UNDO is for pixel or shape
                if (std::stoi(message[3]) == 0) {
                    paintCanvas.SetPixelColor(std::stoi(message[1]), std::stoi(message[2]), sf::Color::White);
                }
                else {
                    paintCanvas.RemoveLastShape();
                }
            }
            else if (message[0] == "DRAW" or message[0] == "REDO") {
                // Check if DRAW/REDO is for pixel or shape
                if (std::stoi(message[3]) == 0) {
                    paintCanvas.SetPixelColor(std::stoi(message[1]), std::stoi(message[2]), sf::Color(sf::Uint32(std::stoul(message[4]))));
                }
                else {
                    paintCanvas.AddShape(std::stoi(message[1]), std::stoi(message[2]), sf::Color(sf::Uint32(std::stoul(message[4]))), std::stoi(message[3]));
                }
            }
        }
}

/*
 * This method checks for the kind of key pressed by the user.
 * The user can undo command(s) on hitting "Z",
 * can redo command(s) on hitting "Y",
 * can reset to blank canvas on hitting space-bar,
 * can draw shapes such as - square, triangle, circle on hitting "S", "T" and "C" respectively,
 * and can finally change colours based on various num keys (1-8) being pressed.
 *
 * If a mouse click is detected on paint canvas then it captures the mouse location
 * and draws it.
 * */
void ClientController::PollClientWindow(PaintCanvas& paintCanvas) {
    sf::Event event;
    while (paintCanvas.GetWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            paintCanvas.GetWindow().close();
            // TODO - close connection. Make sure all things are de-allocated properly
            std::cout << "Exiting normally...\n";
            exit(EXIT_SUCCESS);
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                paintCanvas.GetWindow().close();
                // TODO - close connection. Make sure all things are de-allocated properly
                std::cout << "Exiting normally...\n";
                exit(EXIT_SUCCESS);
            }

            if (event.key.code == sf::Keyboard::Z) {        // UNDO
                m_connection.send("UNDO ");
            }

            if (event.key.code == sf::Keyboard::Y) {        // REDO
                m_connection.send("REDO ");
            }

            if (event.key.code == sf::Keyboard::Space) {    // Reset to blank canvas
                m_connection.send("RESET ");
            }

            if (event.key.code == sf::Keyboard::S) {        // SQUARE
                this->m_shape_point_count = 4;
            }

            if (event.key.code == sf::Keyboard::T) {        // TRIANGLE
                this->m_shape_point_count = 3;
            }

            if (event.key.code == sf::Keyboard::C) {        // CIRCLE
                this->m_shape_point_count = 30;
            }

            if (event.key.code == sf::Keyboard::X) {        // EXIT SHAPE MODE
                this->m_shape_point_count = 0;
            }

            if (event.key.code == sf::Keyboard::Num1) {     // CHANGE COLOR TO BLACK
                this->m_marker_color = sf::Color::Black;
            }

            if (event.key.code == sf::Keyboard::Num2) {     // CHANGE COLOR TO WHITE
                this->m_marker_color = sf::Color::White;
            }

            if (event.key.code == sf::Keyboard::Num3) {     // CHANGE COLOR TO RED
                this->m_marker_color = sf::Color::Red;
            }

            if (event.key.code == sf::Keyboard::Num4) {     // CHANGE COLOR TO GREEN
                this->m_marker_color = sf::Color::Green;
            }

            if (event.key.code == sf::Keyboard::Num5) {     // CHANGE COLOR TO BLUE
                this->m_marker_color = sf::Color::Blue;
            }

            if (event.key.code == sf::Keyboard::Num6) {     // CHANGE COLOR TO YELLOW
                this->m_marker_color = sf::Color::Yellow;
            }

            if (event.key.code == sf::Keyboard::Num7) {     // CHANGE COLOR TO MAGENTA
                this->m_marker_color = sf::Color::Magenta;
            }

            if (event.key.code == sf::Keyboard::Num8) {     // CHANGE COLOR TO CYAN
                this->m_marker_color = sf::Color::Cyan;
            }
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i coordinates = sf::Mouse::getPosition(paintCanvas.GetWindow());
        if (CheckValidCoordinates(coordinates, paintCanvas)) {
            m_connection.send("DRAW " + std::to_string(coordinates.x) + " " + std::to_string(coordinates.y) + " " + std::to_string(m_shape_point_count) + " " + std::to_string(m_marker_color.toInteger()) + " ");
        }
    }
}

/*
 * This method checks the validity of mouse co-ordinates, ensuring
 * that the mouse click(s) happen within the bounds of the canvas.
 * */
bool ClientController::CheckValidCoordinates(sf::Vector2i coordinates, PaintCanvas& m_paint_canvas) {
    if (coordinates.x <= 0 || coordinates.y <= 0 ||
        coordinates.x >= m_paint_canvas.GetWindowWidth() || coordinates.y >= m_paint_canvas.GetWindowHeight())
        return false;
    return true;
}
