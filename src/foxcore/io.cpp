#include <fstream>

std::string readFile(const std::string &path) {
    std::ifstream stream(path);
    std::string line;
    std::string file = "";

    while (getline(stream, line)) {
        file = file + line;
        file = file + "\n";
    }

    return file;
}
