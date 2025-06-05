# MinilibC

---

## ![France](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/fr.png "France") Version Française

### Présentation

**MinilibC** est un projet scolaire consistant à recréer une mini-librairie C en assembleur x86-64.
L'objectif est de réimplémenter certaines fonctions standard de la libc et de les utiliser dynamiquement grâce à `LD_PRELOAD`.

### Objectif pédagogique

Ce projet permet de comprendre :

* Le fonctionnement des bibliothèques dynamiques (`.so`)
* Le mécanisme de `LD_PRELOAD` sous Linux
* L’écriture de code bas niveau en assembleur
* La structure interne de fonctions de la libc

### Fonctions implémentées

* `memcpy`
* `memset`
* `strchr`
* `strcmp`
* `strlen`
* `strncmp`

Les comportements respectent les spécifications des man pages (`man 3 <fonction>`).

### Compilation

```bash
make
```

Génère le fichier `libminilibc.so`.

### Utilisation

```bash
LD_PRELOAD=./libminilibc.so ./votre_programme
```

### Dépendances

* `nasm`
* `ld`
* `make`

### Licence

Projet réalisé dans le cadre d’un cours — librement réutilisable à des fins pédagogiques.

---

## ![United Kingdom](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png "United Kingdom") English Version

### Overview

**MinilibC** is a school project to rebuild a small C library in x86-64 assembly.
The goal is to re-implement selected libc functions and use them dynamically via `LD_PRELOAD`.

### Educational Objective

This project helps to understand:

* How dynamic libraries (`.so`) work
* The Linux `LD_PRELOAD` mechanism
* Low-level assembly programming
* Internal behavior of libc functions

### Implemented Functions

* `memcpy`
* `memset`
* `strchr`
* `strcmp`
* `strlen`
* `strncmp`

Each function follows the behavior defined in the Linux man pages (`man 3 <function>`).

### Build

```bash
make
```

This generates the `libminilibc.so` shared object.

### Usage

```bash
LD_PRELOAD=./libminilibc.so ./your_program
```

### Dependencies

* `nasm`
* `ld`
* `make`

### License

Project completed as part of a university course — free to use for educational purposes.

