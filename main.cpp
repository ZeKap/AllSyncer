#include <iostream>
#include <fstream>


std::string fileFromPath = "/home/kap/test/copy-2/from/file.txt";
std::string fileToPath = "/home/kap/test/copy-2/to/file.txt";

int main() {
    std::ifstream input(fileFromPath);
    std::ofstream output(fileToPath);

    // if there is a problem opening one of the files
    if(!input.is_open() || !output.is_open()) {
        std::cout << "Error" << std::endl;
        return 1;
    }

    output << input.rdbuf();

    input.close();
    output.close();

    return 0;
}
