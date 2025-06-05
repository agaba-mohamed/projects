# Raytracer

![Illustration](https://developer.nvidia.com/blog/wp-content/uploads/2018/10/revid2screen8.png)

---

## ![France](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/fr.png "France") Version Française

### Présentation

Ce projet est un **moteur de lancer de rayons (raytracer)** écrit en C++.
Il permet de générer des scènes 3D en traçant les rayons lumineux dans un environnement défini par un fichier de configuration externe.

### Fonctionnalités obligatoires

#### Primitives

* Sphère
* Plan

#### Transformations

* Translation

#### Lumière

* Lumière directionnelle
* Lumière ambiante

#### Matériaux

* Couleur unie (flat shading)

#### Scène

* Ajout de primitives
* Définition de l’éclairage
* Configuration de la caméra

#### Interface

* Pas d'interface graphique (sortie image en format PPM)

### Utilisation

```bash
./raytracer <FICHIER_SCENE>
```

* **FICHIER\_SCENE** : fichier de configuration de la scène

---

### Fonctionnalités bonus

#### Primitives

* Cylindre, Cône
* Cylindre/Cône limités
* Tore, Tanglecube
* Triangles, fichiers `.OBJ`
* Fractales, Ruban de Möbius

#### Transformations

* Rotation, Échelle, Cisaillement
* Matrices de transformation
* Graphe de scène

#### Lumière

* Ombres portées
* Multiples lumières directionnelles ou ponctuelles
* Lumière colorée
* Modèle de Phong
* Occlusion ambiante

#### Matériaux

* Transparence, réfraction, réflexion
* Textures depuis fichier ou générées procéduralement (échiquier, Perlin)
* Normal mapping

#### Scène

* Scène imbriquée
* Anticrénelage (supersampling, adaptatif)

#### Optimisations

* Partitionnement spatial
* Multithreading
* Clustering

#### Interface

* Aperçu temps réel
* Rechargement automatique à la modification du fichier

---

### Format du fichier de scène

Exemple avec `libconfig++` :

```cfg
camera:
{
    resolution = { width = 1920; height = 1080; };
    position = { x = 0; y = -100; z = 20; };
    rotation = { x = 0; y = 0; z = 0; };
    fieldOfView = 72.0;
};

primitives:
{
    spheres = (
        { x = 60; y = 5; z = 40; r = 25; color = { r = 255; g = 64; b = 64; }; },
        { x = -40; y = 20; z = -10; r = 35; color = { r = 64; g = 255; b = 64; }; }
    );
    planes = (
        { axis = "Z"; position = -20; color = { r = 64; g = 64; b = 255; }; }
    );
};

lights:
{
    ambient = 0.4;
    diffuse = 0.6;
    point = ( { x = 400; y = 100; z = 500; } );
    directional = ();
};
```

---

### Architecture

#### Interfaces

Les primitives et sources lumineuses doivent implémenter des interfaces pour favoriser l’extensibilité.

#### Plugins

Le moteur peut charger des fonctionnalités supplémentaires à l’aide de bibliothèques dynamiques (`.so`).

#### Design Patterns

Utiliser au moins **2 design patterns** parmi :

* Factory, Builder, Composite, Decorator
* Observer, State, Mediator

Ils seront discutés lors de la soutenance.

---

### Bibliothèques autorisées

* `libconfig++` pour le parsing
* `SFML 2.5.1` pour l’affichage

Toute autre bibliothèque nécessite une validation.

---

### Compilation

#### Makefile

Un `make` à la racine doit générer `./raytracer` et les plugins dans `./plugins/`.

#### CMake

```bash
mkdir ./build/ && cd ./build/
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..
ls ./raytracer ./plugins/
```

---

## ![United Kingdom](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png "United Kingdom") English Version

### Overview

This project is a **raytracing engine** written in C++.
It generates 3D scenes by simulating light rays based on an external scene configuration file.

### Mandatory Features

#### Primitives

* Sphere
* Plane

#### Transformations

* Translation

#### Light

* Directional light
* Ambient light

#### Material

* Flat color shading

#### Scene

* Add primitives
* Setup lighting
* Configure camera

#### Interface

* No GUI, outputs a `.ppm` image file

### Usage

```bash
./raytracer <SCENE_FILE>
```

* **SCENE\_FILE**: path to the scene configuration file

---

### Bonus Features

#### Primitives

* Cylinder, Cone
* Limited Cylinder/Cone
* Torus, Tanglecube
* Triangles, `.OBJ` files
* Fractals, Möbius strip

#### Transformations

* Rotation, Scale, Shear
* Transformation matrices
* Scene graph

#### Light

* Drop shadows
* Multiple directional and point lights
* Colored lights
* Phong lighting model
* Ambient occlusion

#### Material

* Transparency, Refraction, Reflection
* File-based and procedural textures (chessboard, Perlin)
* Normal mapping

#### Scene Features

* Import nested scenes
* Antialiasing (supersampling, adaptive)

#### Optimizations

* Spatial partitioning
* Multithreading
* Clustering

#### Interface

* Live preview and generation display
* Hot reload on file change

---

### Scene File Format

Example using `libconfig++`:

```cfg
camera:
{
    resolution = { width = 1920; height = 1080; };
    position = { x = 0; y = -100; z = 20; };
    rotation = { x = 0; y = 0; z = 0; };
    fieldOfView = 72.0;
};

primitives:
{
    spheres = (
        { x = 60; y = 5; z = 40; r = 25; color = { r = 255; g = 64; b = 64; }; },
        { x = -40; y = 20; z = -10; r = 35; color = { r = 64; g = 255; b = 64; }; }
    );
    planes = (
        { axis = "Z"; position = -20; color = { r = 64; g = 64; b = 255; }; }
    );
};

lights:
{
    ambient = 0.4;
    diffuse = 0.6;
    point = ( { x = 400; y = 100; z = 500; } );
    directional = ();
};
```

---

### Architecture

#### Interfaces

Use interfaces for primitives and lights to keep the code extensible.

#### Plugins

The engine can be extended with `.so` dynamic libraries loaded at runtime (optional).

#### Design Patterns

Use at least **two design patterns**, e.g.:

* Factory, Builder, Composite, Decorator
* Observer, State, Mediator

These will be discussed during your project defense.

---

### Authorized Libraries

* `libconfig++` for scene parsing
* `SFML 2.5.1` for optional display

Any extra libraries require prior approval.

---

### Build Instructions

#### Makefile

A `make` command at the root should generate `./raytracer` and optional plugins in `./plugins/`.

#### CMake

```bash
mkdir ./build/ && cd ./build/
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..
ls ./raytracer ./plugins/
```
