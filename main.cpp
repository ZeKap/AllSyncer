#include <iostream>
#include "include/File.h"


std::string fileFromPath = "/home/kap/test/copy-2/from/file.txt";
std::string fileToPath = "/home/kap/test/copy-2/to/file.txt";

int main() {
    AllSyncer::File input(fileFromPath);
    input.copyAll(fileToPath);

    return 0;
}
