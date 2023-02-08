#include <iostream>
#include <fstream>
#include <sstream>
#include "include/Entry.h"
#include "nlohmann-json/json.hpp"
using json = nlohmann::json;


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


std::string folderFromPath = "/Users/kap/trucs-tests/AllSyncer/from/";
std::string folderToPath = "/Users/kap/trucs-tests/AllSyncer/to";

std::string configFilePath = "/Users/kap/trucs-tests/AllSyncer/config.json";
const json config = getParsedJsonFromLink(configFilePath);

int main() {

    /*// example to use json parsed
    for(auto & key : config.items()) {
        std::cout << key.key() << std::endl;
        for(auto & value : key.value()) {
            std::cout << "    " << value << std::endl;
        }
    }*/

    // we add a src and copy it
    AllSyncer::Entry input(folderFromPath, folderToPath, config);
    input.copy();

    return 0;
}
