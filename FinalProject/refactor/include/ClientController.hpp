//
// Created by Jason Miller on 12/11/21.
//

#ifndef CLIENTCONTROLLER_HPP
#define CLIENTCONTROLLER_HPP

#include <SFML/Network.hpp>

#include "PaintCanvas.hpp"
#include "ClientConnection.hpp"

class ClientController {
private:
    sf::Color        m_marker_color;
    ClientConnection m_connection;
    int              m_shape_point_count;

    void PollClientWindow(PaintCanvas &paintCanvas);
    bool CheckValidCoordinates(sf::Vector2i coordinates, PaintCanvas &paintCanvas);
    void Consume(std::vector<std::string> &message, PaintCanvas &paintCanvas);
public:
    ClientController();
    void run();
};

#endif //CLIENTCONTROLLER_HPP
