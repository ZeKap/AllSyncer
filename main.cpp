#include <iostream>
#include <fstream>
#include <sstream>
#include "include/Entry.h"
#include "nlohmann-json/json.hpp"
using json = nlohmann::json;

std::string folderFromPath = "/Users/kap/trucs-tests/AllSyncer/from/";
std::string folderToPath = "/Users/kap/trucs-tests/AllSyncer/to";


std::string configFilePath = "/Users/kap/trucs-tests/AllSyncer/config.json";

json getParsedJsonFromLink(const std::string& path) {
    // open json file
    std::ifstream configFile(path);

    // store its content in a string
    std::stringstream configFileStream;
    configFileStream << configFile.rdbuf();
    configFile.close();
    std::string configFileString(configFileStream.str());

    // return the parsed json
    return json::parse(configFileString);
}

int main() {
    AllSyncer::Entry input(folderFromPath);
    input.copyAll(folderToPath);

    json jsonConfig = getParsedJsonFromLink(configFilePath);

    for(auto & key : jsonConfig.items()) {
        std::cout << key.key() << std::endl;
        for(auto & value : key.value()) {
            std::cout << "    " << value << std::endl;
        }
    }


    return 0;
}
