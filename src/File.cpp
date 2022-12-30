//
// Created by kap on 30/12/22.
//

#include "../include/File.h"

namespace AllSyncer {
    File::File(const std::string& path) {
        // check if the file exists
        if(!std::filesystem::exists(path)) {
            exit(1);
        }

        // store path to the file, its edit time and its permissions
        this->path = path;
        this->editTime = std::filesystem::last_write_time(path);
        this->perms = std::filesystem::status(path).permissions();
    }

    void File::copyAll(const std::string& destination) {
        // copy content of the file
        std::filesystem::copy_file(this->path, destination,
                                   std::filesystem::copy_options::overwrite_existing);
        // copy its edit time and permissions
        std::filesystem::last_write_time(destination, this->editTime);
        std::filesystem::permissions(destination, this->perms);
    }
} // AllSyncer