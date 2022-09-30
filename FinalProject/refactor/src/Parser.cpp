//
// Created by Emily Colladay on 12/11/21.
//

#include "Parser.hpp"
#include <vector>
#include <variant>
#include <SFML/Network.hpp>
#include "iostream"

/*
 * This helper method checks whether a string is a number
 * and returns true if yes, false if not.
 * It takes in a string as a parameter.
 * */
bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

/*
 * Constructor for Parser class.
 * */
Parser::Parser(){}

/*
 * This method splits a string on every space ie. " ".
 * It then pushes the words into a vector and returns the vector.
 * It takes in a string as a parameter
 * */
std::vector<std::string> Parser::split_sentence(std::string text) {
    std::string delim = " ";
    std::vector<std::string> words{};
    size_t pos = 0;

    while((pos = text.find(delim)) != std::string::npos){
        words.push_back(text.substr(0, pos));
        text.erase(0, pos + delim.length());
    }
    return words;
}

/*
 * This method is responsible for receiving a string and parsing it
 * appropriately using split_sentence() and storing it into a packet
 * awaiting to be sent to the server.
 * It takes in a string as a parameter.
 * */
sf::Packet Parser::parseToPacket(std::string& description){
    std::vector<std::string> words = split_sentence(description);
    sf::Packet packet;

    for (auto it = words.begin(); it != words.end(); it++) {
        if (isNumber(*it)) {
            sf::Uint32 val = std::stoul(*it);
            packet << val;
        } else packet << *it;
    }

    return packet;
}

/*
 * This method is responsible for parsing incoming packets coming in 
 * from the server and returns a vector.
 * It takes in a packet as a parameter.
 * */
std::vector<std::string> Parser::parsePacket(sf::Packet& packet) {
    std::string type;
    sf::Uint32 x, y, points, color;

    // packet should have type only or draw, x,y,points,color
    packet >> type;

    if (type == "RESET") {
        packet >> type;
        std::vector<std::string> vec {type};
        return vec;
    }
    packet >> x >> y >> points >> color;
    std::vector<std::string> res {type, std::to_string(x), std::to_string(y), std::to_string(points), std::to_string(color)};
    return res;
}


/*
 * This method is responsible for converting a Draw command that is
 * stored in a packet into an Undo command stored in another packet.
 * It returns the latter packet.
 * */
sf::Packet Parser::parseUndo(sf::Packet last){
    sf::Packet p;
    std::string undo = "UNDO";

    std::string type;
    sf::Uint32 x, y, points, color;

    last >> type >> x >> y >> points >> color;
    p << undo << x << y << points << color;
    return p;
}
