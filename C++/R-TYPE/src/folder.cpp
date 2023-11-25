#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

std::vector<std::string> listFilesInFolder(const std::string& folderPath) {
    namespace fs = std::filesystem;
    std::vector<std::string> fileNames;

    try {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (fs::is_regular_file(entry)) {
                fileNames.push_back(entry.path().filename().string());
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return fileNames;
}