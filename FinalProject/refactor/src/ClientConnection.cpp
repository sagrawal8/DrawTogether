//
// Created by Jason Miller on 12/12/21.
//

#include <iostream>
#include "ClientConnection.hpp"

#define logl(x) std::cout << x << std::endl

ClientConnection::ClientConnection() {

}

ClientConnection::~ClientConnection() {
    m_socket.disconnect();
}

/*
 * This method ensures that socket connection with the server is set up by
 * taking in two parameters - IP address and port number.
 * */
void ClientConnection::connect(const std::string& ipAddress, unsigned short port) {
    std::cout << "Client: trying to connect to" << ipAddress << ", " << port << std::endl;
    sf::Socket::Status status = m_socket.connect(ipAddress, port, sf::seconds(4.0));
    m_socket.setBlocking(false);
    m_socket.setBlocking(false);
    if (status == sf::Socket::Done) logl("Successfully connected to server.");
    else logl("Error connecting to server.");
}

/*
 * This method sends a log message if we fail while sending
 * packets to server.
 * */
void ClientConnection::send(std::string message) {
    sf::Packet packet = m_parser.parseToPacket(message);
    if (m_socket.send(packet) != sf::Socket::Done) {
        logl("ERROR SENDING PACKET TO SERVER");
    }
    else {
        logl("Packet  message is "+ message);
        //logl("Packet successfully sent! Server will now store it.");
    }
}

/*
 * This method receives the packets being sent by the Server
 * and decodes them, in order to draw on canvas.
 * */
std::vector<std::string> ClientConnection::receive() {
    if (m_socket.receive(m_packet) == sf::Socket::Done) {
        // Receive the packet and decode the received string
        std::vector<std::string> packet = m_parser.parsePacket(m_packet);
        return packet;
    }
    return {};
};
