#include"../src/EntityType.cpp"
#include"../src/folder.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
class Game {
    public:
    Game();
    Game(bool display);
    void add(std::string);
    void inside();
    void render();
    char KeyWasReleased;
    bool is_display = true;
    std::vector<EntityType> entities_type;
    std::vector<EntityType> entities;
    sf::RenderWindow win;
};

#ifdef __linux__
    #include <dlfcn.h>
    #define PLATEFORMPATH "linux"
    #define LIBTYPE void*
    #define OPENLIB(libname) dlopen((libname), RTLD_LAZY)
    #define LIBFUNC(lib, fn) dlsym((lib), (fn))
    #define CLOSELIB(libname) dlclose((lib))
#elif _WIN32
    #include <windows.h>
    #define PLATEFORMPATH L"windows"
    #define LIBTYPE HINSTANCE
    #define OPENLIB(libname) LoadLibraryW(libname)
    #define LIBFUNC(lib, fn) GetProcAddress((lib), (fn))
    #define CLOSELIB(libname) FreeLibrary((lib))
#endif
