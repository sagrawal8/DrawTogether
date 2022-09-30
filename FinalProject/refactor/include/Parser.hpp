#include <vector>
#include <variant>
#include <SFML/Network.hpp>
#pragma once



class Parser{
private:
    static std::vector<std::string> split_sentence(std::string text);

public:
    Parser();

    // For Client to Server
    sf::Packet parseToPacket(std::string& description); // this is for clients to draw or add a shape and send that info to server
    // will need to create Packet and add info: DRAW, x, y, Color


    // For Client from Server
    sf::Packet parseUndo(sf::Packet packet);

    std::vector<std::string> parsePacket(sf::Packet& packet);

};