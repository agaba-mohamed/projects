g++ -fPIC -shared -o libs/enemy.dll scripts/enemy.cpp
g++ -fPIC -shared -o libs/chase_enemy.dll scripts/chase_enemy.cpp
g++ -fPIC -shared -o libs/bullet.dll scripts/bullet.cpp
g++ -fPIC -shared -o libs/rotate_bullet.dll scripts/rotate_bullet.cpp
g++ src/Client/mainCli.cpp -o build/client -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio -g3
g++ src/Server/mainServer.cpp -o build/server -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio -g3
g++ src/editor.cpp -o build/editor -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio -g3
