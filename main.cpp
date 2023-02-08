#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
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

    // we create a vector containing all folders from config and the config
    std::vector<AllSyncer::Entry> folders;
    for (auto& [key, value] : config["foldersToSync"].items()) {
        //std::cout << "Folder: " << key << ", Path: " << value.get<std::string>() << std::endl;
        folders.emplace_back(key, value.get<std::string>(), config);
    }

    // for each entry in vector, we copy it with config
    for (AllSyncer::Entry item: folders) {
        item.copy();
    }

    return 0;
}
