//
// Created by Jason Miller on 12/12/21.
//

#ifndef CLIENTCONNECTION_HPP
#define CLIENTCONNECTION_HPP

#include <SFML/Network.hpp>
#include "Parser.hpp"

class ClientConnection {
private:
    sf::TcpSocket m_socket;
    sf::Packet    m_packet;
    Parser        m_parser;

public:
    // Constructors & Destructors //
    ClientConnection();
    ~ClientConnection();

    //
    void                     connect(const std::string& ipAddress, unsigned short port);
    void                     send(std::string message);
    std::vector<std::string> receive();
};

#endif //CLIENTCONNECTION_HPP
