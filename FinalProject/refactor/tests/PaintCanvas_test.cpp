//
// Created by Jason Miller on 12/4/21.
//

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include <SFML/Network.hpp>

#include "PaintCanvas.hpp"
#include "Parser.hpp"
#include "iostream"

TEST_CASE("Initialize and destroy") {
    PaintCanvas paintCanvas;
}

TEST_CASE("Test no-arg constructor, default conditions") {
    PaintCanvas paintCanvas;
    REQUIRE(paintCanvas.GetWindowWidth() == 600);
    REQUIRE(paintCanvas.GetWindowHeight() == 400);
    REQUIRE(paintCanvas.GetWindow().getSize().x == 600);
    REQUIRE(paintCanvas.GetWindow().getSize().y == 400);
    REQUIRE(paintCanvas.GetPixelColor(0,0) == sf::Color::White);
    REQUIRE(paintCanvas.GetPixelColor(300,300) == sf::Color::White);
    REQUIRE(paintCanvas.GetPixelColor(599,399) == sf::Color::White);
    REQUIRE(paintCanvas.GetPixelColor(600,399) == sf::Color::Transparent);
    REQUIRE(paintCanvas.GetPixelColor(599,400) == sf::Color::Transparent);
    REQUIRE(paintCanvas.GetPixelColor(600,400) == sf::Color::Transparent);
    REQUIRE(paintCanvas.GetPixelColor(601,300) == sf::Color::Transparent);
    REQUIRE(paintCanvas.GetPixelColor(300,401) == sf::Color::Transparent);
}

TEST_CASE("Test arg constructor") {
    PaintCanvas paintCanvas(500,500);
    REQUIRE(paintCanvas.GetWindowWidth() == 500);
    REQUIRE(paintCanvas.GetWindowHeight() == 500);
    REQUIRE(paintCanvas.GetWindow().getSize().x == 500);
    REQUIRE(paintCanvas.GetWindow().getSize().y == 500);
    REQUIRE(paintCanvas.GetPixelColor(0,0) == sf::Color::White);
    REQUIRE(paintCanvas.GetPixelColor(300,300) == sf::Color::White);
    REQUIRE(paintCanvas.GetPixelColor(499,499) == sf::Color::White);
    REQUIRE(paintCanvas.GetPixelColor(499,500) == sf::Color::Transparent);
    REQUIRE(paintCanvas.GetPixelColor(500,499) == sf::Color::Transparent);
    REQUIRE(paintCanvas.GetPixelColor(500,500) == sf::Color::Transparent);
}

TEST_CASE("Test SetPixelColor") {
    PaintCanvas paintCanvas(500,500);
    paintCanvas.SetPixelColor(1, 1, sf::Color::Blue);
    REQUIRE(paintCanvas.GetPixelColor(1,1) == sf::Color::Blue);
    paintCanvas.SetPixelColor(1, 1, sf::Color::Red);
    REQUIRE(paintCanvas.GetPixelColor(1,1) == sf::Color::Red);
}

TEST_CASE("Test AddShape") {
    PaintCanvas paintCanvas(500,500);
    paintCanvas.AddShape(250, 250, sf::Color::Blue, 3);

    std::deque<sf::CircleShape>* shapes = paintCanvas.GetShapes();
    sf::CircleShape shape = shapes->front();

    REQUIRE(shape.getPointCount() == 3);
    REQUIRE(shape.getOutlineColor() == sf::Color::Blue);
}

TEST_CASE("Test RemoveShape") {
    PaintCanvas paintCanvas(500,500);
    paintCanvas.AddShape(250, 250, sf::Color::Blue, 3);
    paintCanvas.RemoveLastShape();

    REQUIRE(paintCanvas.GetShapes()->empty());
}

TEST_CASE("Test parseToPacket") {
    Parser parser;
    std::string s("DRAW 250 250 0 ");
    s.append(std::to_string(sf::Color::Blue.toInteger()) + " ");
    sf::Packet packet = parser.parseToPacket(s);

    sf::Uint32 x, y, points, color;
    std::string command;
    packet >> command >> x >> y >> points >> color;

    REQUIRE(command == "DRAW");
    REQUIRE(x == 250);
    REQUIRE(y == 250);
    REQUIRE(points == 0);
    REQUIRE(color == sf::Color::Blue.toInteger());
}

TEST_CASE("Test parsePacket") {
    Parser parser;
    sf::Packet packet;

    packet << "DRAW" << sf::Uint32 (250) << sf::Uint32 (250) << sf::Uint32 (3) << sf::Color::Blue.toInteger();
    std::vector<std::string> command = parser.parsePacket(packet);

    REQUIRE(command[0] == "DRAW");
    REQUIRE(command[1] == "250");
    REQUIRE(command[2] == "250");
    REQUIRE(command[3] == "3");
    REQUIRE(std::stoi(command[4]) == sf::Color(sf::Uint32(std::stoi(command[4]))).toInteger());
}