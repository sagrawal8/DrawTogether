//
// Created by Jason Miller on 12/5/21.
//

#include <iostream>
#include "ClientController.hpp"
#include "ServerConnection.hpp"

/*
 * This method starts a client.
 * */
void TCPClient(){
	ClientController client;
	std::cout<<"Client initiated. On to run()" << std::endl;
	client.run();
}

/*
 * This method starts a server.
 * */
void TCPServer(){
	ServerConnection server;
    std::cout<<"1. Server initiated. On to run()" << std::endl;
	server.run();
}

/*
 * This methods asks the user whether they want to start a server or client.
 * */
int main() {
	std::string role = "";
	std::cout << "Enter (s) for server, enter (c) for client: ";
	std::cin >> role;
	
	if(role[0] == 's') {
		TCPServer();
	}
	else if(role[0] == 'c') {
		TCPClient();
	}
	
    return 0;
}
