# Dante's Star – Maze Generator and Solver

![Illustration](https://labyrinth.tech/assets/media/news/labyrinth-generation-algorithm.jpg)

---

## ![France](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/fr.png "France") Version Française

### Présentation

**Dante’s Star** est un projet de génération et de résolution de labyrinthes inspiré de *La Divine Comédie* de Dante Alighieri. Le joueur ou l'algorithme doit progresser à travers **neuf cercles de l'Enfer**, chacun représentant un défi algorithmique croissant.

### Structure du projet

- `generator/` – Contient le code source et le binaire pour générer les labyrinthes.  
- `solver/` – Contient le code source et le binaire pour résoudre les labyrinthes.  
- `generalfiles/` – Code source partagé entre les deux modules.

### Compilation

```bash
make generator
make solver
````

### Génération de labyrinthe

```bash
./generator/generator x y [perfect]
```

* `x` et `y` : dimensions du labyrinthe
* `perfect` (optionnel) : génère un labyrinthe parfait (par défaut : imparfait)

### Résolution de labyrinthe

```bash
./solver/solver maze.txt
```

Affiche la solution du labyrinthe. Si aucune solution n’est trouvée : `no solution found`.

### Les neuf cercles de l'Enfer

| Cercle         | Fonction / Objectif                          |
| -------------- | -------------------------------------------- |
| 1. Limbe       | Génération initiale du labyrinthe            |
| 2. Luxure      | Premiers algorithmes de résolution           |
| 3. Gourmandise | Génération de labyrinthes imparfaits (amas)  |
| 4. Avarice     | Génération de labyrinthes parfaits           |
| 5. Colère      | Résolution des labyrinthes générés           |
| 6. Hérésie     | Optimisation des algorithmes de recherche    |
| 7. Violence    | Mesure de la complexité des labyrinthes      |
| 8. Fraude      | Implémentation d’heuristiques                |
| 9. Trahison    | Résolution finale avec recherche heuristique |

### Exécution

1. Cloner le dépôt
2. Aller à la racine du projet
3. Compiler avec `make`
4. Générer et résoudre un labyrinthe avec les commandes indiquées

---

## ![United Kingdom](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png "United Kingdom") English Version

### Overview

**Dante’s Star** is a maze generation and solving project inspired by *The Divine Comedy* by Dante Alighieri. The program guides you through **nine circles of Hell**, each representing a new computational challenge.

### Project Structure

* `generator/` – Source and binary for maze generation
* `solver/` – Source and binary for maze solving
* `generalfiles/` – Shared code used by both components

### Build Instructions

```bash
make generator
make solver
```

### Maze Generation

```bash
./generator/generator x y [perfect]
```

* `x`, `y`: Maze dimensions
* `perfect`: Optional; generates a perfect maze (default: imperfect)

### Maze Solving

```bash
./solver/solver maze.txt
```

Prints the solution to standard output. If no solution is found, outputs: `no solution found`.

### The Nine Circles of Hell

| Circle       | Challenge Description                     |
| ------------ | ----------------------------------------- |
| 1. Limbo     | Initial maze generation                   |
| 2. Lust      | Basic solving algorithms                  |
| 3. Gluttony  | Imperfect maze generation (with clusters) |
| 4. Greed     | Perfect maze generation                   |
| 5. Wrath     | Maze resolution logic                     |
| 6. Heresy    | Search algorithm optimization             |
| 7. Violence  | Measuring maze complexity                 |
| 8. Fraud     | Heuristic-based solving                   |
| 9. Treachery | Final stage with heuristic pathfinding    |

### How to Run

1. Clone the repository
2. Navigate to the project root
3. Build using `make`
4. Use the generator and solver as described above

### License

Educational project — free to use for academic purposes
