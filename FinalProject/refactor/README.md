# Program Structure and Functionality

This program is a collaborative paint program which allows clients to draw together, with the added ability to undo or redo, and reset the canvas. For the purpose of storing the draw history, our program utilizes two stacks to appropriately push or pop draw commands, depending on the request of a client. For this, we are using a Client-Server model, where the server acts as the command and action handler.

## Client

The client can draw and add shapes, request the last actions to be undone or redone, or reset the canvas to white. This is sent to the server so that it can communicate these changes to all other clients in the network.

### Actions:
1. Draw command - a pixel is changed to the given color by the client. 
2. Undo command - the last command in the m_command stack is popped and undone. Client requests this from server.
3. Redo command - the last undone command (requested by any client) is redone. This must also be requested.
4. Draw shapes - rather than one pixel, a Shape object is added to the canvas where the client is drawing.
5. Change color - client can choose the color they would like to draw on the canvas with.
6. Reset Canvas - in the case of the client wanting to start over but not exit the program, they may request a reset. This will empty the canvas to white.

## Server

The server connects clients and manages their actions, receiving incoming commands and broadcasting them out to all others, which creates a collaborative canvas experience. The server houses the commands and undo stacks, which represent the history of the canvas. These will be cleared if a client requests a reset via pushing the space bar.


## Video
https://youtu.be/q3MTME9hOYI

### Actions:
1. Connect clients - server listens for new clients and stores a list of active clients
2. Receive actions - when a client draws on the canvas or requests an undo/redo/reset, the server receives this and takes the necessary action while managing the canvas history. For reset, it will empty the history stacks.
3. Send actions - after receiving a command, the server will send out the appropriate packet out to all clients containing the necessary information for them to execute the correct changes to their PaintCanvas. This will update all canvases to reflect one another, creating a collaborative experience.
