//
// Created by Jason Miller on 12/2/21.
//

#include <SFML/Network.hpp>

#ifndef SERVER_HPP
#define SERVER_HPP

class Server {
private:
    sf::IpAddress m_ip;


    int handleClientJoining();
    int handleClientLeaving();

public:
    Server(sf::IpAddress ipAddress);
    ~Server();
};

#endif SERVER_HPP
