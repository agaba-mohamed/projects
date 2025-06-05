# ftrace – Unix System Programming

![Illustration](https://cdn.thenewstack.io/media/2020/08/9860a611-granulate_ftrace_image.png)

---

## ![France](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/fr.png "France") Version Française

### Présentation

**ftrace** est un outil de traçage dynamique en C, inspiré de `strace` et `ltrace`.  
Il utilise des fonctionnalités bas niveau du noyau Linux (comme `ptrace`, `elf`, `libbfd`, etc.) pour intercepter l’exécution d’un programme, analyser son comportement et afficher :

- Les appels système (`syscalls`)
- Les appels de fonctions internes et externes (librairies dynamiques)
- Les signaux reçus (`SIGINT`, `SIGSEGV`, etc.)
- Les adresses mémoire liées aux appels

Ce projet met en pratique la programmation système Unix et l’analyse dynamique de binaire ELF.

---

### Fonctionnalités principales

- Suivi des appels de fonctions avec adresse d’entrée et de sortie
- Détection des appels système avec arguments et valeurs de retour
- Affichage des signaux reçus pendant l’exécution
- Résolution des noms de symboles (si disponibles)
- Analyse de bibliothèques partagées (fichiers `.so`)

---

### Structure du projet

- `src/` – Code source principal (analyse ELF, `ptrace`, parsing, affichage)

---

### Compilation

```bash
make
````

Le binaire `ftrace` sera généré à la racine du projet.

---

### Utilisation

```bash
./ftrace <commande>
```

Exemple :

```bash
./ftrace ls
```

Le programme interceptera toutes les fonctions et appels système générés par `ls`.

---

### Exemple de sortie

```text
Entering function main at 0x42ff231
Entering function my_putstr at 0x42ff9fd
Syscall write (0x1, 0xff3210123, 0x1) = 0x1
Leaving function my_putchar
Received signal SIGWINCH
Leaving function my_putchar
Entering function printf at 0x877621fda31
```

---

### Aide

```bash
./ftrace --help
```

Affiche les options disponibles pour filtrer ou modifier la sortie.

---

### Technologies utilisées

* `ptrace` – pour attacher et tracer le processus enfant
* `libbfd` – pour lire les symboles depuis les exécutables ELF
* `elf.h` – pour manipuler les en-têtes ELF
* `dlfcn.h` – pour charger dynamiquement les symboles
* `signal.h` – pour intercepter les signaux

---

### Objectifs pédagogiques

* Compréhension du format ELF
* Utilisation de `ptrace` pour le debugging
* Interception des appels système et analyse mémoire
* Travail avec les bibliothèques dynamiques
* Gestion fine des processus et signaux

---

### Licence

Projet pédagogique — librement réutilisable à des fins éducatives.


---

## ![United Kingdom](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png "United Kingdom") English Version

### Overview

**ftrace** is a low-level function tracing tool in C, similar in concept to `strace` and `ltrace`.
It uses Linux system programming interfaces (`ptrace`, ELF headers, libbfd, etc.) to dynamically analyze and display:

* System calls (syscalls)
* Function entries and exits
* Received signals (e.g., `SIGINT`, `SIGSEGV`)
* Shared library calls and addresses

This project focuses on mastering Unix process tracing and binary analysis.

---

### Main Features

* Trace internal and external function calls with entry/exit addresses
* Intercept syscalls with arguments and return values
* Detect and log received signals
* Resolve symbols from binaries and shared libraries
* Analyze `.so` library calls dynamically

---

### Project Structure

* `src/` – Main logic for ELF parsing, tracing, signal handling, output formatting

---

### Build Instructions

```bash
make
```

Generates the `ftrace` binary at the project root.

---

### Usage

```bash
./ftrace <command>
```

Example:

```bash
./ftrace ls
```

This intercepts and prints detailed trace information from the `ls` command.

---

### Sample Output

```text
Entering function main at 0x42ff231
Entering function my_putstr at 0x42ff9fd
Syscall write (0x1, 0xff3210123, 0x1) = 0x1
Leaving function my_putchar
Received signal SIGWINCH
Leaving function my_putchar
Entering function printf at 0x877621fda31
```

---

### Help

```bash
./ftrace --help
```

Displays available options for controlling output verbosity and filters.

---

### Technologies Used

* `ptrace` – to attach and trace child processes
* `libbfd` – for ELF binary symbol reading
* `elf.h` – to manipulate ELF headers
* `dlfcn.h` – to dynamically resolve shared symbols
* `signal.h` – for catching runtime signals

---

### Educational Goals

* Deep understanding of the ELF binary format
* Use of `ptrace` for real-time program introspection
* Memory and syscall inspection
* Dynamic linking and shared object analysis
* Process and signal management at system level

---

### License

Educational project — free to reuse for learning purposes.

---

