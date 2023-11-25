/*
** EPITECH PROJECT, 2023
** aaa
** File description:
** aaaa
*/

#include"TCPServer.cpp"

int main(int ac, char** av) {
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <port>" << std::endl;
        return 1;
    }

    try {
        TCPServer server(std::stoi(av[1])); // Replace 8080 with your desired port number

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}