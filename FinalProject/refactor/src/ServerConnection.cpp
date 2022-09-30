//
// Created by Jason Miller on 12/14/21.
//

#include "ServerConnection.hpp"
#include <iostream>
#include "Parser.hpp"

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x
#define readInto(x) std::cin >> x

/*
 * Constructor for ServerConnection class.
 * */
ServerConnection::ServerConnection() {
    running = true;
}

/*
 * Destructor for ServerConnection class.
 * */
ServerConnection::~ServerConnection() {
    running = false;
}

/*
 * This method ensures that the server is up and running and can
 * handle client joining, receiving and sending of packets.
 * */
void ServerConnection::run() {
    while (!init()) logl("Error connecting to this port. Please try a different one");             // Keep prompting user for a port until success
    m_selector.add(m_listener);
    while (running) {
        if (m_selector.wait()) {
            if (m_selector.isReady(m_listener)) {
                // the listener is ready : there is a pending connection
                handleClientJoining();
            } else {                                                                              // Listener socket is not ready - test all other sockets (clients)
                receive();
                broadcast();
            }
        }
    }
}

/*
 * This method asks the server to listen in on a specific user-inputted 
 * port.
 * */
bool ServerConnection::init() {
    log("Please specify port number: ");
    readInto(m_port);
    return (m_listener.listen(m_port) == sf::Socket::Done);
}


/*
 * This method is responsible for receiving packets from clients.
 * It also aids in disconnecting clients from the server.
 * */
void ServerConnection::receive() {
    if (m_selector.wait()) {
        for (auto it = m_clients.begin(); it != m_clients.end(); ++it) {
            sf::TcpSocket &client = **it;
            if (m_selector.isReady(client)) {                                     // The client has sent some data, we can receive it
                sf::Packet packet;
                if (client.receive(packet) == sf::Socket::Disconnected) {
                    m_selector.remove(client);
                    client.disconnect();
                    it = m_clients.erase(it);
                    delete &client;
                } else handlePacket(packet);
            }
        }
    }
}

/*
 * This method is responsible for handling the commands coming in from the client.
 * Commands are of the following: Draw, Reset, Undo, Redo.
 * Based on the type of command received, server carries out operations on its stacks.
 * */
void ServerConnection::handlePacket(sf::Packet &packet) {
    if (packet.getDataSize() > 0) {
        std::string commandType;
        packet >> commandType;
        if (commandType == "DRAW") {                                    // DRAW
            m_commands.push_back(packet);
            m_undone.clear();
        } else if (commandType == "RESET") {                            // RESET
            m_commands.clear();
            m_undone.clear();
            m_history.clear();
        } else if (!m_history.empty() and commandType == "UNDO") {      // UNDO
            packet = m_history.back();
            m_history.pop_back();
            sf::Packet undone = parser.parseUndo(packet);
            m_undone.push_back(packet);
            sendPacket(undone);
        } else if (!m_undone.empty() and commandType == "REDO") {       // REDO
            sf::Packet redone = m_undone.back();
            m_undone.pop_back();
            m_commands.push_back(redone);
        }
    }
}

/*
 * This method carries out operations on the stacks held by the server based on
 * the incoming client message.
 * It is also added to the command history so that new clients can get up to speed 
 * with the rest.
 * */
void ServerConnection::broadcast() {
    while (!m_commands.empty()) {
        sf::Packet pop = m_commands.front();
        m_commands.pop_front();
        m_history.push_back(pop);
        sendPacket(pop);
    }
}

/*
 * This method is responsible to send the message from one client to all 
 * other clients in the form of packets.
 * It takes in a single argument 'packet' that is of Command type.
 * */
void ServerConnection::sendPacket(sf::Packet& packet) {
    if (m_selector.wait()) {
        for (auto it = m_clients.begin(); it != m_clients.end(); ++it) {
            sf::TcpSocket& client = **it;
            if (m_selector.isReady(client)) {
                if (client.send(packet) == sf::Socket::Disconnected) {
                    m_selector.remove(client);
                    client.disconnect();
                    it = m_clients.erase(it);
                    delete &client;
                }
            }
        }
    }
}

/*
 * This method ensures the joining of new clients to the server as well as
 * getting newly connected clients upto speed with what is already on the canvas.
 * */

void ServerConnection::handleClientJoining() {
    sf::TcpSocket* newClient = new sf::TcpSocket();
    if (m_listener.accept(*newClient) == sf::Socket::Done) {
        m_clients.push_back(newClient);  // Add new client to clients list
        newClient->setBlocking(false);
        m_selector.add(*newClient);

        for (auto it = m_history.crbegin(); it != m_history.crend(); ++it) {
            sf::Packet packet = *it;
            newClient->send(packet);
        }

    } else {
        delete newClient; // error - we don't get new connection - delete client
    }
}

