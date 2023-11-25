# R-Type Game Documentation

## Overview

This document provides comprehensive information about the R-Type codebase, encompassing the architecture, core functionality, server-client communication, map builder, and associated protocols.

### R-Type Architecture

The R-Type game is structured into three main components: **Core**, **Server**, and **Client**. Additionally, there is a **Map Builder** tool.

#### Core

The Core component is responsible for managing entities within the game. Entities are objects with various characteristics, including collision, health, spawning, type, position, rendering, ID, and scripting. Users can create their entities using shared libraries. To create a new entity:

1. **Create a .kyks file:** Specifies the entity's components and characteristics.
2. **Create a script (if needed):** Contains setup and loop functions for entity initialization and continuous behavior.
3. **Modify CMake (if using a script):** Set the entity name in the "add_library" section.

#### Server

The Server component facilitates communication between clients, handling interactions and sending specific data to each client. Key modification areas include the `handleClients` function, which executes whenever a new client connects.

#### Client

The Client component allows users to play and visually experience their actions. The `parseId` function can be modified to handle server inputs.

#### Map Builder

The Map Builder tool creates an SFML window where users can draw game maps. Entities are loaded from ".kyks" files, and users can place entities on the grid. The map can be saved to a text file.

### R-Type Game

The R-Type game is a re-creation of the classic R-Type game in C++, featuring online multiplayer through a multi-threaded server using Asio and UDP protocol. The SFML library is used for the client.

#### Requirements

- CMake
- Conan

#### Dependencies

- sfml/2.6.0
- asio/1.18.0

#### Supported Platforms

- Linux
- Windows

#### Build

- **Linux:** Run `./build.sh` and then `make`.
- **Windows:** Run `./build.bat` and then `make`.

#### Usage Instructions

- `./rtype_server` to run the server.
- `./rtype_client` to run the client.

#### Controllers

| Header 1  | Header 2  |
|-----------|-----------|
| Move up   | Up arrow  |
| Move right| Right arrow|
| Move down | Down arrow|
| Move left | Left arrow|
| Shoot     | Space     |


This document is a document that explains of the rtype code , morevover that can be  used to add some features to the rtype game :

`Here is a diagram of the rtype arrchitecture : `
![image](https://github.com/EpitechPromo2026/B-CPP-500-MAR-5-1-rtype-zyad.othman/assets/91945721/f67d8571-4a0f-4e4a-b037-56e6d70c203a)

***

# The Core 

The Core is the part of the code that permit to add a few entities to the game.
An entity is a type of object that can be implemented, it depends on:
* The collision system
* The health system
* The spawning system
* The type
* The position system
* The render system
* The ID
* The scripting system
***
It is also the part that permits to the user to create his own entitites with the use of shared libraries.
To do that : 

## Create a .kyks
The first step is to create a .kyks file that will permit to the user to specify the components that the entity has to handle (rendering,position,hitbox,weapon,scripting,...) if you want the entity to be loaded from a map you can set a fileDesc and put his character in value and if you want it to have weapons you can set a weapon with the entity weapon in value.
## Create a script (if needed)
The script is a cpp file that contains two functions :
### The setup function
`extern "C" void setup(Entity *entity)
{
}
`
The setup function is a function that permits to initialize the entity (set a sound,set variables,...)
### The loop function
`extern "C" void loop(Entity *entity,Core *core)
{
}`
The loop function is a function that permits to move and add events to the entities with sopme algorithms for example
## Modify the CMAKE (if there is a script)
All you have to do in the cmake is to set the name of your entity in the "add_library"
***
# The Server

The server is the part of the code that communicates with all the clients and handle the communication between them.You can modify this part to add some features and send specific data's to each clients.The main part to modify in this file is the `handleClients` function.This function is launched everyitme a new client is connected (for example the ennemies are coded in this part).


# The Client

The client is the part of the code that permits to the user to play and have a graphical visualisation of his actions.You can modify this part to handle all the server inputs. To do that you can code in the `parseId` function.

# The Map Builder

The program creates an SFML window where the user can draw a game map. The user can select different entities to place on the map by pressing keys on the keyboard. The entities are loaded from "FileDisc :" from ".kyks" files located in the "entities" folder. When the user clicks on the grid, the selected entity is placed at the corresponding position. The map can be saved to a choosen text file.

This code provides a solid foundation for creating a game editor using the SFML library. Enhancements can be made by adding additional features such as handling more complex events, animation features, and more.


### TCP Protocol Documentation

This section outlines the custom TCP-like protocol for the R-Type game, covering connection establishment, login procedures, and logout operations.

#### Connection Establishment

- **220 - Connection Successful:** Indicates successful connection establishment.
- **401 - Connection Failed:** Indicates a failed connection attempt.

#### Login

- **USER - User Authentication:** Used for user authentication.
  - **Response:**
    - 230 - Authentication successful

- **GETROOMS - Get List of Rooms:** Retrieves the list of available rooms.
  - **Response:**
    - 240 - Room list retrieved successfully

- **GETROOMPARTICIPANTS - Get Room Participants:** Retrieves the list of participants in a room.
  - **Response:**
    - 250 - Participants list retrieved successfully

- **CREATEROOM - Create a Room:** Creates a new room.
  - **Response:**
    - 260 - Room creation successful
    - 402 - Room creation failed

- **JOIN - Join a Room:** Allows a user to join an existing room.
  - **Response:**
    - 270 - Joining the room was successful

- **START - Start a Room:** Initiates the start of a room.
  - **Response:**
    - 280 - Room started successfully

#### Logout

- **QUIT - Disconnect and Logout:** Disconnects and logs out.
  - **Response:**
    - 221 - Logout successful

- **LEAVE - Leave a Room:** Allows a user to leave a room.
  - **Response:**
    - 271 - Leaving the room was successful

### UDP Protocol Documentation

This section provides information on the custom UDP-based protocol used for sending packages in the R-Type game.

#### Package Structure

Each package consists of:

- **id:** Unique identifier.
- **x, y:** X and Y coordinates.
- **type:** Entity type.

Example:
```
id: 123 x:42 y:64 type:DATA
id: 123 shoot
```

#### Communication Flow

- **Sending a Package (Client):** Follow the specified format.
- **Server Response:** Depends on the server's behavior.

#### Error Handling

The UDP protocol may not provide extensive error handling. Both client and server should handle errors and ensure correct package formatting.

#### Security Considerations

UDP lacks the security features of TCP. Additional measures like encryption or authentication may be necessary.

#### Examples

- **Sending a Package (Client):**
  ```plaintext
  id: 123 x:42 y:64 type:DATA
  id: 123 shoot
  ```

- **Server Response (Sample Acknowledgment):**
  ```plaintext
  Received package: id: 123 x:42 y:64 type:DATA
  Received package: id: 123 shoot
  ```

## Conclusion

This comprehensive documentation provides insights into the R-Type game, including its architecture, components, protocols, and usage instructions. Ensure adherence to the outlined procedures for successful interaction with the game.


#### License

Avengers®

#### Authors

- [Zyad Othman](mailto:zyad.othman@epitech.eu "Zyad Othman")
- [Kylian Taguelmint](mailto:kylian.taguelmint@epitech.eu "Kylian Taguelmint")
- [Mohamed-Amine Agaba](mailto:mohamedamine.agaba@epitech.eu "Mohamed-Amine Agaba")
- [Lorenzo Langlois](mailto:lorenzo.langlois@epitech.eu "Lorenzo Langlois")
- [Alexandre Vassal](mailto:alexandre.vassal@epitech.eu "Alexandre Vassal")
