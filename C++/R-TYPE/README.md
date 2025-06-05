# R-Type

![Illustration](https://m.media-amazon.com/images/I/911DV9FiRTL.png)

---

## ![France](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/fr.png "France") Version Française

### Présentation

Ce document fournit une documentation complète sur le code du jeu **R-Type**, en couvrant l’architecture, le fonctionnement, les protocoles de communication client-serveur, l’éditeur de cartes, et les entités.

---

### Architecture du jeu

Le projet R-Type est divisé en plusieurs composants principaux :

* **Core**
* **Serveur**
* **Client**
* **Map Builder**

#### Core

Le **Core** gère les entités du jeu. Chaque entité peut avoir :

* Un système de collisions
* Un système de points de vie
* Un comportement de génération (spawn)
* Un type
* Une position
* Un rendu (sprite)
* Un identifiant unique (ID)
* Un script (comportement personnalisé)

##### Pour créer une entité :

1. **Créer un fichier `.kyks`** pour définir ses composants (rendu, arme, script…)
2. **Créer un script (si nécessaire)** avec deux fonctions :

   * `setup` : initialisation de l’entité
   * `loop` : comportement de l’entité à chaque frame
3. **Modifier le `CMakeLists.txt`** pour l'ajouter avec `add_library`.

#### Serveur

Le serveur gère la communication avec les clients.
Il envoie et reçoit les informations via UDP et TCP.
La fonction clé est `handleClients`, appelée à chaque connexion client.

#### Client

Le client permet au joueur d’interagir avec le jeu.
Il affiche le rendu graphique avec SFML et traite les entrées serveur via `parseId`.

#### Map Builder

Un éditeur de cartes interactif basé sur SFML.

* Les entités sont chargées depuis les fichiers `.kyks`
* Possibilité de les placer sur une grille
* Sauvegarde dans un fichier texte

---

### Jeu R-Type

Version multijoueur en ligne du célèbre jeu R-Type.
C++, SFML pour le rendu, serveur multithreadé avec Asio (UDP).

#### Pré-requis

* CMake
* Conan

#### Dépendances

* `sfml/2.6.0`
* `asio/1.18.0`

#### Plateformes supportées

* Linux
* Windows

#### Compilation

* **Linux** :

  ```bash
  ./build.sh && make
  ```
* **Windows** :

  ```bash
  ./build.bat && make
  ```

#### Lancement

```bash
./rtype_server  # Lancer le serveur
./rtype_client  # Lancer le client
```

#### Contrôles

| Action    | Touche        |
| --------- | ------------- |
| Monter    | Flèche haut   |
| Descendre | Flèche bas    |
| Gauche    | Flèche gauche |
| Droite    | Flèche droite |
| Tirer     | Espace        |

---

### Protocole TCP

Gère l’authentification, les salons, et la communication client.

| Commande            | Réponse           |
| ------------------- | ----------------- |
| USER                | 230 OK            |
| GETROOMS            | 240 OK            |
| GETROOMPARTICIPANTS | 250 OK            |
| CREATEROOM          | 260 OK / 402 Fail |
| JOIN                | 270 OK            |
| START               | 280 OK            |
| QUIT                | 221 OK            |
| LEAVE               | 271 OK            |

---

### Protocole UDP

Utilisé pour les entités en temps réel.

#### Format de paquet

```
id: 123 x:42 y:64 type:DATA
id: 123 shoot
```

#### Sécurité

Pas de garantie comme TCP. Prévoir une vérification côté serveur.

---

### Conclusion

Ce document vous guide dans la structure du projet R-Type, utile pour contribuer ou étendre le jeu.

### Licence

Avengers®

### Auteurs

- [Zyad Othman](mailto:zyad.othman@epitech.eu "Zyad Othman")
- [Kylian Taguelmint](mailto:kylian.taguelmint@epitech.eu "Kylian Taguelmint")
- [Mohamed-Amine Agaba](mailto:mohamedamine.agaba@epitech.eu "Mohamed-Amine Agaba")
- [Lorenzo Langlois](mailto:lorenzo.langlois@epitech.eu "Lorenzo Langlois")
- [Alexandre Vassal](mailto:alexandre.vassal@epitech.eu "Alexandre Vassal")

---

## ![United Kingdom](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png "United Kingdom") English Version

### Overview

This document provides complete documentation for the **R-Type** game project, including architecture, protocols, core systems, map editor, and usage instructions.

---

### Game Architecture

The project includes the following main components:

* **Core**
* **Server**
* **Client**
* **Map Builder**

#### Core

Manages all entities in the game. Each entity can have:

* Collision system
* Health system
* Spawning system
* Type
* Position system
* Rendering system
* Unique ID
* Scripting behavior

##### To create a new entity:

1. **Create a `.kyks` file** describing the components (render, hitbox, weapon, etc.)
2. **Create a script (if needed)** with two functions:

   * `setup(Entity*)` for initialization
   * `loop(Entity*, Core*)` for behavior
3. **Edit CMake** and add the new entity with `add_library`.

#### Server

Handles all communication between clients.
The key function is `handleClients`, triggered on client connection.
Entities like enemies are managed here.

#### Client

Provides graphical display and user input handling.
You can handle server messages via the `parseId` function.

#### Map Builder

A simple SFML-based level editor:

* Entities are loaded from `.kyks` files
* Users can place them on a grid
* Maps are saved as plain text

---

### R-Type Game

A C++ re-creation of the classic R-Type game, supporting online multiplayer using UDP with Asio and SFML.

#### Requirements

* CMake
* Conan

#### Dependencies

* `sfml/2.6.0`
* `asio/1.18.0`

#### Supported Platforms

* Linux
* Windows

#### Build

* **Linux**:

  ```bash
  ./build.sh && make
  ```
* **Windows**:

  ```bash
  ./build.bat && make
  ```

#### Running the Game

```bash
./rtype_server  # Start server
./rtype_client  # Start client
```

#### Controls

| Action     | Key         |
| ---------- | ----------- |
| Move up    | Up arrow    |
| Move down  | Down arrow  |
| Move left  | Left arrow  |
| Move right | Right arrow |
| Shoot      | Spacebar    |

---

### TCP Protocol

Used for login, room management, and session control.

| Command             | Response          |
| ------------------- | ----------------- |
| USER                | 230 OK            |
| GETROOMS            | 240 OK            |
| GETROOMPARTICIPANTS | 250 OK            |
| CREATEROOM          | 260 OK / 402 Fail |
| JOIN                | 270 OK            |
| START               | 280 OK            |
| QUIT                | 221 OK            |
| LEAVE               | 271 OK            |

---

### UDP Protocol

Used for real-time updates (e.g. position, shooting).

#### Package Format

```
id: 123 x:42 y:64 type:DATA
id: 123 shoot
```

#### Security

As UDP is unreliable, validation should be done server-side.

---

### Conclusion

This documentation explains the R-Type codebase and how to extend or work with it efficiently.

### License

Avengers®

### Authors

- [Zyad Othman](mailto:zyad.othman@epitech.eu "Zyad Othman")
- [Kylian Taguelmint](mailto:kylian.taguelmint@epitech.eu "Kylian Taguelmint")
- [Mohamed-Amine Agaba](mailto:mohamedamine.agaba@epitech.eu "Mohamed-Amine Agaba")
- [Lorenzo Langlois](mailto:lorenzo.langlois@epitech.eu "Lorenzo Langlois")
- [Alexandre Vassal](mailto:alexandre.vassal@epitech.eu "Alexandre Vassal")
  
