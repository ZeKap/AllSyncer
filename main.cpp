#include <iostream>
#include "include/Entry.h"
#include "include/json.hpp"

std::string folderFromPath = "/Users/kap/trucs-tests/AllSyncer/from/";
std::string folderToPath = "/Users/kap/trucs-tests/AllSyncer/to";

std::string configFile = "/Users/kap/trucs-tests/AllSyncer/config.json";

int main() {
    AllSyncer::Entry input(folderFromPath);
    input.copyAll(folderToPath);

    return 0;
}
