/** 
 *  @file   Draw.cpp 
 *  @brief  Draw implementation, all drawing actions are commands. 
 *  @author Mike and Archita Sundaray
 *  @date   2021-10-10
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
// Include standard library C++ libraries.
// #include ...
// Project header files
#include "App.hpp"
#include "Draw.hpp"
#include <memory>

#include "helper.hpp"

//int Draw::getX() {
//    return x;
//}

//int Draw::getY() {
//    return y;
//}

/*! \brief 	N/A
*
*/
bool Draw::execute(){
    // App setPixel get all from App::
    print("Execute operation");
    appObj->GetImage().setPixel(x, y, this->color);
    return true;
}

/*! \brief 	N/A
*
*/
bool Draw::undo(){
    print("Undo operation");
    appObj->GetImage().setPixel(x, y, sf::Color::White);
    return true;
}

// Constructor for name and set
Draw::Draw(std::string name) : Command(name) {}

//Parameterised Constructor
Draw::Draw(std::string name, int x, int y, std::shared_ptr<App> appObj) : Command(name, x, y) {
    this->name = name;
    this->x = x;
    this->y = y;
    this->appObj = appObj;
    this->color = this->appObj->GetColor();
}

//checking if same command was executed again
//bool operator == (appObj.mouseX, appObj.mouseY) {
//    if (appObj.pmouseX != appObj.mouseX and appObj.pmouseY != appObj.mouseY) {
//        return true;
//    }
//}