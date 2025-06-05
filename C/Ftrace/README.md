# ftrace – Unix System Programming

![Illustration](https://cdn.thenewstack.io/media/2020/08/9860a611-granulate_ftrace_image.png)

---

## ![France](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/fr.png "France") Version Française

### Présentation

**ftrace** est un outil de traçage dynamique de fonctions écrit en C.  
Il permet d'analyser l'exécution d’un programme, en affichant les appels système, les appels de fonctions internes, les signaux reçus, ainsi que les appels vers des bibliothèques partagées.

### Structure du projet

- `src/` – Contient les fichiers source de l'application

### Compilation

```bash
make
````

Le binaire `ftrace` sera généré à la racine du projet.

### Utilisation

```bash
./ftrace <commande>
```

Exemple :

```bash
./ftrace ls
```

Ce qui affichera les appels système, les entrées/sorties de fonctions, et les signaux déclenchés par la commande `ls`.

### Format de sortie

```text
1. Entering function main at 0x42ff231
2. Entering function my_putstr at 0x42ff9fd
3. Syscall write (0x1, 0xff3210123, 0x1) = 0x1
4. Leaving function my_putchar
5. Received signal SIGWINCH
6. Leaving function my_putchar
7. Entering function printf at 0x877621fda31
```

### Aide

```bash
./ftrace --help
```

---

## ![United Kingdom](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png "United Kingdom") English Version

### Overview

**ftrace** is a dynamic function tracing tool written in C.
It analyzes a running program and displays system calls, function entries/exits, received signals, and calls to shared libraries.

### Project Structure

* `src/` – Contains the source code files

### Build

```bash
make
```

This compiles the `ftrace` binary at the project root.

### Usage

```bash
./ftrace <command>
```

Example:

```bash
./ftrace ls
```

This will trace and print system calls, function calls, and signals triggered by the `ls` command.

### Output Format

```text
1. Entering function main at 0x42ff231
2. Entering function my_putstr at 0x42ff9fd
3. Syscall write (0x1, 0xff3210123, 0x1) = 0x1
4. Leaving function my_putchar
5. Received signal SIGWINCH
6. Leaving function my_putchar
7. Entering function printf at 0x877621fda31
```

### Help

```bash
./ftrace --help
```
