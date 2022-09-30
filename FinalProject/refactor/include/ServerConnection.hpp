//
// Created by Jason Miller on 12/14/21.
//

#ifndef SERVERCONNECTION_HPP
#define SERVERCONNECTION_HPP

#include <deque>
#include <vector>
#include <list>
#include <sfml/Network.hpp>
#include <Parser.hpp>

class ServerConnection {
private:
    std::list<sf::TcpSocket*> m_clients;
    sf::TcpListener             m_listener;
    sf::SocketSelector          m_selector;
    unsigned short              m_port;
    bool                        running;

    std::deque<sf::Packet>      m_commands;
    std::deque<sf::Packet>      m_undone;
    std::deque<sf::Packet>      m_history;
    Parser parser;

    void handlePacket(sf::Packet &packet);


public:
    ServerConnection();
    ~ServerConnection();
    void run();
    bool init();
    void receive();
    void broadcast();
    void sendPacket(sf::Packet& packet);
    void handleClientJoining();
};

#endif
