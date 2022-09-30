#include <App.hpp>
#include <Draw.hpp>
#include <Square.hpp>
#include <Triangle.hpp>
#include <Circle.hpp>
#include "clientnetwork.hpp"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

ClientNetwork::ClientNetwork(){
     logl("Chat Client Started");
}

void ClientNetwork::Connect(const char * address, unsigned short port){
     if(socket.connect(address, port) != sf::Socket::Done){
          logl("Could not connect to the server\n");
     }else{
          isConnected = true;
          logl("Connected to the server\n");
     }
}

void ClientNetwork::ReceivePackets(sf::TcpSocket * socket){
     while(true){
          if(socket->receive(last_packet) == sf::Socket::Done){
               std::string received_string; std::string sender_address; unsigned short sender_port;
               last_packet >> received_string >> sender_address >> sender_port;
               logl("From (" << sender_address << ":" << sender_port << "): " << received_string);
          }
          
          std::this_thread::sleep_for((std::chrono::milliseconds)100);
     }
}

void ClientNetwork::SendPacket(sf::Packet & packet){
     if(packet.getDataSize() > 0 && socket.send(packet) != sf::Socket::Done){
          logl("Could not send packet");
     }
}

// NOTE TO ALL: This is the same code as the update() function in main.cpp. I feel like it shouldn't need to be here
// and in our update() callback function, but this was the only way I could get it to work. I'm thinking we may be able
// to send the Commands straight over as Packets (I didn't get any syntactical errors when trying this out), but will
// need to test this idea thoroughly. ALSO how does one quit the server without a segfault?

void ClientNetwork::Run(std::shared_ptr<App> appObj){
     std::thread reception_thred(&ClientNetwork::ReceivePackets, this, &socket);
    sf::Event event;

//    if (isConnected) {
//        while (appObj->GetWindow().pollEvent(event)) {
//            //        if(event.type == sf::Event::MouseButtonPressed){
//            //            // Modify the pixel
//            //            App::mouseX = event.mouseMove.x;
//            //            App::mouseY = event.mouseMove.y;
//            //        }
//
//            // Pressing numbers 1 through 8 allows to draw in different colors
//            if (event.type == sf::Event::KeyPressed) {
//                switch (event.key.code) {
//                    case (sf::Keyboard::Num1):
//                        appObj->setColor(sf::Color::Black); //Num Key 1: Black
//                        break;
//                    case (sf::Keyboard::Num2):
//                        appObj->setColor(sf::Color::White); //Num Key 2: White
//                        break;
//                    case (sf::Keyboard::Num3):
//                        appObj->setColor(sf::Color::Red); //Num Key 3: Red
//                        break;
//                    case (sf::Keyboard::Num4):
//                        appObj->setColor(sf::Color::Green); //Num Key 4: Green
//                        break;
//                    case (sf::Keyboard::Num5):
//                        appObj->setColor(sf::Color::Blue); //Num Key 5: Blue
//                        break;
//                    case (sf::Keyboard::Num6):
//                        appObj->setColor(sf::Color::Yellow); //Num Key 6: Yellow
//                        break;
//                    case (sf::Keyboard::Num7):
//                        appObj->setColor(sf::Color::Magenta); //Num Key 7: Magenta
//                        break;
//                    case (sf::Keyboard::Num8):
//                        appObj->setColor(sf::Color::Cyan); //Num Key 8: Cyan
//                        break;
//                    case (sf::Keyboard::S):
//                        appObj->setMode(sf::Keyboard::S); // Switch to square mode
//                        break;
//                    case (sf::Keyboard::T):
//                        appObj->setMode(sf::Keyboard::T); // Switch to triangle mode
//                        break;
//                    case (sf::Keyboard::C):
//                        appObj->setMode(sf::Keyboard::C); // Switch to circle mode
//                        break;
//                    case (sf::Keyboard::X):
//                        appObj->setMode(sf::Keyboard::X); // Exit shape modes -> return to standard paint mode
//                        break;
//                    case (sf::Keyboard::Z):
//                        appObj->UndoCommand();
//                        break;
//                    case (sf::Keyboard::Y):
//                        appObj->RedoCommand();
//                        break;
//                    case (sf::Keyboard::Escape):
//                        appObj->GetWindow().close();
//                        exit(EXIT_SUCCESS);
//                    default:
//                        break;
//                }
//            }
//        }
//
//        // Pressing space bar will clear all pixels and will have a solid color with the last color selected
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//            appObj->GetImage().create(WINDOW_WIDTH, WINDOW_HEIGHT, appObj->GetColor());
//            appObj->GetTexture().loadFromImage(appObj->GetImage());
//            appObj->GetSprite().setTexture(appObj->GetTexture());
//        }
//
//        // We can otherwise handle events normally
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//            sf::Vector2i coordinate = sf::Mouse::getPosition(appObj->GetWindow());
//            if ((appObj->mouseX >= 0 and appObj->mouseX <= 600) and (appObj->mouseY >= 0 and appObj->mouseY <= 400)) {
//                appObj->mouseX = coordinate.x;
//                appObj->mouseY = coordinate.y;
//                sf::Vector2u window_size = appObj->GetWindow().getSize();
//
//                //rejecting same commands and commands outside the window
//                if ((coordinate.x != appObj->pmouseX || coordinate.y != appObj->pmouseY) and
//                    (coordinate.x >= 0 and coordinate.x <= window_size.x and coordinate.y >= 0 and
//                     coordinate.y <= window_size.y)) {
//
//                    // Modify the pixel or draw a shape
//                    Command *newPixel;
//                    if (appObj->GetMode() == sf::Keyboard::X) {
//                        newPixel = new Draw("draw", coordinate.x, coordinate.y, appObj);
//                    } else if (appObj->GetMode() == sf::Keyboard::S) {
//                        newPixel = new Square("square", coordinate.x, coordinate.y, appObj);
//                    } else if (appObj->GetMode() == sf::Keyboard::T) {
//                        newPixel = new Triangle("triangle", coordinate.x, coordinate.y, appObj);
//                    } else if (appObj->GetMode() == sf::Keyboard::C) {
//                        newPixel = new Circle("circle", coordinate.x, coordinate.y, appObj);
//                    }
//                    appObj->AddCommand(newPixel);
//                    appObj->ExecuteCommand();
//                    appObj->EmptyStack(); // to empty the stack after the execution of command
//                }
//            }
//        }
//
//
//        // Where was the mouse previously before going to the next frame
//        appObj->pmouseX = appObj->mouseX;
//        appObj->pmouseY = appObj->mouseY;
//    }

     while(true){
          if(isConnected){
              appObj->Loop(appObj);
              sf::Event event;

              while (appObj->GetWindow().pollEvent(event)) {
                  if (event.type == sf::Event::KeyPressed) {
                      switch (event.key.code) {
                          case (sf::Keyboard::Num1):
                              appObj->setColor(sf::Color::Black); //Num Key 1: Black
                               break;
                               case (sf::Keyboard::Num2):
                                appObj->setColor(sf::Color::White); //Num Key 2: White
                                break;
                            case (sf::Keyboard::Num3):
                                appObj->setColor(sf::Color::Red); //Num Key 3: Red
                                break;
                            case (sf::Keyboard::Num4):
                                appObj->setColor(sf::Color::Green); //Num Key 4: Green
                                break;
                            case (sf::Keyboard::Num5):
                                appObj->setColor(sf::Color::Blue); //Num Key 5: Blue
                                break;
                            case (sf::Keyboard::Num6):
                                appObj->setColor(sf::Color::Yellow); //Num Key 6: Yellow
                                break;
                            case (sf::Keyboard::Num7):
                                appObj->setColor(sf::Color::Magenta); //Num Key 7: Magenta
                                break;
                            case (sf::Keyboard::Num8):
                                appObj->setColor(sf::Color::Cyan); //Num Key 8: Cyan
                                break;
                            case (sf::Keyboard::S):
                                appObj->setMode(sf::Keyboard::S); // Switch to square mode
                                break;
                            case (sf::Keyboard::T):
                                appObj->setMode(sf::Keyboard::T); // Switch to triangle mode
                                break;
                            case (sf::Keyboard::C):
                                appObj->setMode(sf::Keyboard::C); // Switch to circle mode
                                break;
                            case (sf::Keyboard::X):
                                appObj->setMode(sf::Keyboard::X); // Exit shape modes -> return to standard paint mode
                                break;
                            case (sf::Keyboard::Z):
                                appObj->UndoCommand();
                                break;
                            case (sf::Keyboard::Y):
                                appObj->RedoCommand();
                                break;
                            case (sf::Keyboard::Escape):
                                appObj->GetWindow().close();
                                exit(EXIT_SUCCESS);
                            default:
                                break;
                        }
                    }
                }

//           Pressing space bar will clear all pixels and will have a solid color with the last color selected
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            appObj->GetImage().create(WINDOW_WIDTH, WINDOW_HEIGHT, appObj->GetColor());
            appObj->GetTexture().loadFromImage(appObj->GetImage());
            appObj->GetSprite().setTexture(appObj->GetTexture());
        }

        // We can otherwise handle events normally
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i coordinate = sf::Mouse::getPosition(appObj->GetWindow());
            if ((appObj->mouseX >= 0 and appObj->mouseX <= 600) and (appObj->mouseY >= 0 and appObj->mouseY <= 400)) {
                appObj->mouseX = coordinate.x;
                appObj->mouseY = coordinate.y;
                sf::Vector2u window_size = appObj->GetWindow().getSize();

                //rejecting same commands and commands outside the window
                if ((coordinate.x != appObj->pmouseX || coordinate.y != appObj->pmouseY) and
                    (coordinate.x >= 0 and coordinate.x <= window_size.x and coordinate.y >= 0 and
                     coordinate.y <= window_size.y)) {

                    // Modify the pixel or draw a shape
                    Command *newPixel;
                    if (appObj->GetMode() == sf::Keyboard::X) {
                        newPixel = new Draw("draw", coordinate.x, coordinate.y, appObj);
                    } else if (appObj->GetMode() == sf::Keyboard::S) {
                        newPixel = new Square("square", coordinate.x, coordinate.y, appObj);
                    } else if (appObj->GetMode() == sf::Keyboard::T) {
                        newPixel = new Triangle("triangle", coordinate.x, coordinate.y, appObj);
                    } else if (appObj->GetMode() == sf::Keyboard::C) {
                        newPixel = new Circle("circle", coordinate.x, coordinate.y, appObj);
                    }
                    appObj->AddCommand(newPixel);
                    appObj->ExecuteCommand();
                    appObj->EmptyStack(); // to empty the stack after the execution of command
                }
            }
        }


        // Where was the mouse previously before going to the next frame
        appObj->pmouseX = appObj->mouseX;
        appObj->pmouseY = appObj->mouseY;

               std::string user_input;
               std::getline(std::cin, user_input);

               sf::Packet reply_packet;
               reply_packet << user_input;

               SendPacket(reply_packet);
          }
     }
}
