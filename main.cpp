#include <iostream>
#include "include/Entry.h"


std::string folderFromPath = "/home/kap/test/copy-2/from/";
std::string folderToPath = "/home/kap/test/copy-2/to/";

int main() {
    AllSyncer::Entry input(folderFromPath);
    input.copyAll(folderToPath);

    return 0;
}
