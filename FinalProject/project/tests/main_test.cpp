//
// Created by Archita Sundaray on 11/11/21.
//
/**
 *  @file   main_test.cpp
 *  @brief  Unit Tests for our program
 *  @author Mike and Archita Sundaray
 *  @date   2021-11-11
 ***********************************************/

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <iostream>
#include <string>
// Project header files
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"


void initialization(void){
    std::cout << "Starting the App" << std::endl;
}

/*! \brief 	Initialize and destroy the program
*
*/
TEST_CASE("init and destroy"){
    App appObj1;
    appObj1.Init(&initialization);
}

/*! \brief 	Check if the pixel drawn has "Red" colour
* and another random pixel having "White" colour
*
*/
TEST_CASE("change pixel colour"){
    std::shared_ptr<App> appObj2 = std::make_shared<App>();
    appObj2->Init(&initialization);

    SECTION("Draw functionality check: ") {
        Command *newPixel = new Draw("draw", 50, 60, appObj2);
        appObj2->AddCommand(newPixel);
        appObj2->ExecuteCommand();
        appObj2->EmptyStack();

        REQUIRE(appObj2->GetImage().getPixel(50, 60) == sf::Color::White);
        REQUIRE(appObj2->GetImage().getPixel(51, 60) == sf::Color::White);
    }
}

/*! \brief 	Check if Undo worked on canvas
*
*/
TEST_CASE("check undo"){
    std::shared_ptr<App> appObj3 = std::make_shared<App>();
    appObj3->Init(&initialization);

    SECTION("Checking Draw functionality: ") {
        Command *newPixel = new Draw("draw", 50, 60, appObj3);
        appObj3->AddCommand(newPixel);
        appObj3->ExecuteCommand();
        appObj3->EmptyStack();

        Command *cmd = new Draw("draw", 51, 60, appObj3);
        appObj3->AddCommand(cmd);
        appObj3->ExecuteCommand();
        appObj3->EmptyStack();

        appObj3->UndoCommand();

        REQUIRE(appObj3->GetImage().getPixel(50, 60) == sf::Color::White);
        REQUIRE(appObj3->GetImage().getPixel(51, 60) == sf::Color::White);
    }
}

/*! \brief 	Check if Redo worked on canvas
*
*/
TEST_CASE("check Redo"){
    std::shared_ptr<App> appObj4 = std::make_shared<App>();
    appObj4->Init(&initialization);

    SECTION("Checking Draw functionality: ") {
        Command *newPixel = new Draw("draw", 50, 60, appObj4);
        appObj4->AddCommand(newPixel);
        appObj4->ExecuteCommand();
        appObj4->EmptyStack();

        Command *cmd = new Draw("draw", 51, 60, appObj4);
        appObj4->AddCommand(cmd);
        appObj4->ExecuteCommand();
        appObj4->EmptyStack();

        appObj4->UndoCommand();
        appObj4->RedoCommand();

        REQUIRE(appObj4->GetImage().getPixel(50, 60) == sf::Color::White);
        REQUIRE(appObj4->GetImage().getPixel(51, 60) == sf::Color::White);
    }
}

/*! \brief 	Check if there are no pixels left to be seen
*
*/
TEST_CASE("check multiple Undo actions"){
    std::shared_ptr<App> appObj5 = std::make_shared<App>();
    appObj5->Init(&initialization);

    SECTION("Checking Draw functionality: ") {
        Command *newPixel = new Draw("draw", 50, 60, appObj5);
        appObj5->AddCommand(newPixel);
        appObj5->ExecuteCommand();
        appObj5->EmptyStack();

        Command *cmd = new Draw("draw", 51, 60, appObj5);
        appObj5->AddCommand(cmd);
        appObj5->ExecuteCommand();
        appObj5->EmptyStack();

        appObj5->UndoCommand();
        appObj5->UndoCommand();

        REQUIRE(appObj5->GetImage().getPixel(50, 60) == sf::Color::White);
        REQUIRE(appObj5->GetImage().getPixel(51, 60) == sf::Color::White);
    }
}


