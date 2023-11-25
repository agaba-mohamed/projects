# Raytracer

![Illustration](https://developer.nvidia.com/blog/wp-content/uploads/2018/10/revid2screen8.png)

### Mandatory Features

#### Primitives
- Sphere
- Plane

#### Transformations
- Translation

#### Light
- Directional light
- Ambient light

#### Material
- Flat color

#### Scene Configuration
- Add primitives to the scene
- Set up lighting
- Set up camera

#### Interface
- No GUI, output to a PPM file

### Usage
```bash
./raytracer <SCENE_FILE>
```
- **SCENE_FILE:** Scene configuration

### Bonus Features

#### Primitives
- Cylinder (Should)
- Cone (Should)
- Limited cylinder (Could)
- Limited cone (Could)
- Torus (Could)
- Tanglecube (Could)
- Triangles (Could)
- .OBJ file (Could)
- Fractals (Could)
- Möbius strip (Could)

#### Transformations
- Rotation (Should)
- Scale (Could)
- Shear (Could)
- Transformation matrix (Could)
- Scene graph (Could)

#### Light
- Drop shadows (Should)
- Multiple directional lights (Could)
- Multiple point lights (Could)
- Colored light (Could)
- Phong reflection model (Could)
- Ambient occlusion (Could)

#### Material
- Transparency (Could)
- Refraction (Could)
- Reflection (Could)
- Texturing from file (Could)
- Texturing from procedural generation of chessboard (Could)
- Texturing from procedural generation of Perlin noise (Could)
- Normal mapping (Could)

#### Scene Configuration
- Import a scene in a scene (Could)
- Set up antialiasing through supersampling (Could)
- Set up antialiasing through adaptive supersampling (Could)

#### Optimizations
- Space partitioning (Could)
- Multithreading (Could)
- Clustering (Could)

#### Interface
- Display the image during and after generation (Could)
- Exit during or after generation (Could)
- Scene preview using a basic and fast renderer (Could)
- Automatic reload of the scene at file change (Could)

### Scene File Format
The rendered scene is set up in an external file. It's suggested to use the libconfig++ library, but you can implement your own parser and syntax. Here is an example scene file using libconfig++ file format:

```plaintext
# Configuration of the camera
camera:
{
    resolution = { width = 1920; height = 1080; };
    position = { x = 0; y = -100; z = 20; };
    rotation = { x = 0; y = 0; z = 0; };
    fieldOfView = 72.0; # In degree
};

# Primitives in the scene
primitives:
{
    # List of spheres
    spheres = (
        { x = 60; y = 5; z = 40; r = 25; color = { r = 255; g = 64; b = 64; }; } ,
        { x = -40; y = 20; z = -10; r = 35; color = { r = 64; g = 255; b = 64; }; }
    );

    # List of planes
    planes = (
        { axis = "Z"; position = -20; color = { r = 64; g = 64; b = 255; }; }
    );
};

# Light configuration
lights:
{
    ambient = 0.4; # Multiplier of ambient light
    diffuse = 0.6; # Multiplier of diffuse light

    # List of point lights
    point = (
        { x = 400; y = 100; z = 500; };
    );

    # List of directional lights
    directional = ();
};
```

### Architecture

#### Interfaces
To allow extensibility, use interfaces for at least your primitives and lights.

#### Plugins
The rendering engine should be extensible, allowing the addition of new features without completely rewriting the code. You can implement this using dynamic libraries (.so) as plugins loaded at runtime (not mandatory).

#### Design Patterns
Use at least 2 design patterns from the following list:
- Factory
- Builder
- Composite
- Decorator
- Observer
- State
- Mediator

Your choices of design patterns will be discussed during the defense.

### Authorized Libraries
The only authorized libraries are:
- libconfig++ for parsing the scene configuration file
- SFML 2.5.1 for displaying

Additional libraries for bonuses need approval from the pedagogical team.

### Build

#### Makefile
Your Makefile must have the usual mandatory rules. Running a simple `make` command in your turn-in directory should generate the raytracer program at the root of the repository and optional plugins in the ./plugins/ directory.

#### CMake
Your CMakeLists.txt must build a program at the root of the repository and plugins in the ./plugins/ directory at the root of the repository.

```bash
mkdir ./build/ && cd ./build/
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..
ls ./raytracer ./plugins/
```
