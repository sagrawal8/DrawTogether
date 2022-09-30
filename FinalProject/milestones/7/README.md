# Building Software

- [ ] Instructions on how to build your software should be written in this file
	- This is especially important if you have added additional dependencies.
	- Assume someone who has not taken this class (i.e. you on the first day) would have read, build, and run your software from scratch.
- You should have at a minimum in your project
	- [ ] A CMakeLists.txt in a root directory
    	- [ ] This should generate a 'release' version of your software
  - [ ] Run your code with the latest version of cppcheck before commiting your code (could be a github action)
  - [ ] (Optional) Run your code with the latest version of clang-tidy  (could be a github action)

*Modify this file to include instructions on how to build and run your software. Specify which platform you are running on. Running your software involves launching a server and connecting at least 2 clients to the server.*

Navigate to the bin/ directory via terminal and call `cmake ..`. Then, call `make App`. This will generate an executable.

First, start the server by calling `./App`. Specify `s` for server and then specify the port number at which clients will connect. The server will start.

Then, call `./App` again. This time, specify `c` for client. If you want to connect to a localhost'ed server, specify `localhost` when prompted for an IP address. Otherwise, specify the IP address of the server machine, followed by the port number specified when initializing the server. Repeat these steps to connect further clients.

