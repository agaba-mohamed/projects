# TCP Protocol Documentation

This document provides information on the custom TCP-like protocol, including its various commands and responses for establishing connections, login procedures, and logout operations.

## Connection Establishment

### 220 - Connection Successful
This code indicates a successful connection establishment.

### 401 - Connection Failed
This code indicates a failed connection attempt.

## Login

### USER - User Authentication
This command is used to authenticate a user.

- **Response:**
  - 230 - Authentication successful

### GETROOMS - Get List of Rooms
This command retrieves the list of available rooms.

- **Response:**
  - 240 - Room list retrieved successfully

### GETROOMPARTICIPANTS - Get Room Participants
This command retrieves the list of participants in a room.

- **Response:**
  - 250 - Participants list retrieved successfully

### CREATEROOM - Create a Room
This command is used to create a new room.

- **Response:**
  - 260 - Room creation successful
  - 402 - Room creation failed

### JOIN - Join a Room
This command allows a user to join an existing room.

- **Response:**
  - 270 - Joining the room was successful

### START - Start a Room
This command initiates the start of a room.

- **Response:**
  - 280 - Room started successfully

## Logout

### QUIT - Disconnect and Logout
This command is used to disconnect and log out.

- **Response:**
  - 221 - Logout successful

### LEAVE - Leave a Room
This command allows a user to leave a room.

- **Response:**
  - 271 - Leaving the room was successful
