//
// Created by kap on 30/12/22.
//

#include <iostream>
#include "../include/Entry.h"

namespace AllSyncer {
    Entry::Entry(const std::string& path, const json & configInput) {
        // check if the file exists
        if(!std::filesystem::exists(path)) {
            exit(1);
        }

        // store path to the file, its edit time and its permissions
        this->path = path;
        this->editTime = std::filesystem::last_write_time(path);
        this->perms = std::filesystem::status(path).permissions();

        // store config in object
        this->config = configInput;
    }


    void Entry::copyFile(const AllSyncer::Entry& src, const std::string &dest,
                            std::filesystem::copy_options options) {
        // copy content of the entry
        std::filesystem::copy(src.path, dest, options);

        // copy its edit time and permissions
        std::filesystem::last_write_time(dest, src.editTime);
        std::filesystem::permissions(dest, src.perms);
    }


    int Entry::copyFolder(const AllSyncer::Entry& src, const std::string &dest) {

        // if the destination doesn't exist, create it
        if(!std::filesystem::exists(dest)) {
            std::filesystem::create_directories(dest);
        }

        // copy its edit time and permissions
        std::filesystem::last_write_time(dest, src.editTime);
        std::filesystem::permissions(dest, src.perms);

        // if the folder is empty, we stop here
        if(std::filesystem::is_empty(src.path)) {
            return 0;
        }

        // else we copy its contents
        for(const std::filesystem::directory_entry& newEntry : std::filesystem::directory_iterator(src.path)) {
            // copy the newEntry, if there was an error, return it
            int error = copyAll(Entry(newEntry.path(), src.config), dest / newEntry.path().filename());
            if(error != 0) {
                return error;
            }
        }

        return 0;
    }


    #pragma clang diagnostic push
    #pragma ide diagnostic ignored "misc-no-recursion"
    int Entry::copyAll(const AllSyncer::Entry& src, const std::string &dest) {

        switch (std::filesystem::status(src.path).type()) {

        // if the src is a file
        case std::filesystem::file_type::regular:
            // copy only the file
            copyFile(src, dest);
            break;


        // if it's a folder, copy edit time and permissions for all files
        case std::filesystem::file_type::directory:
            copyFolder(src, dest);
            break;


        default:
            break;
        }

        return 0;
    }
    #pragma clang diagnostic pop



    int Entry::copyAll(const std::string& destination) const {

        // if the source doesn't exist, display an error
        if (!std::filesystem::exists(this->path)) {
            std::cerr << "Error: source path does not exist: " << this->path << std::endl;
            return 1;
        }

        // if the destination doesn't exist, create it
        if(std::filesystem::exists(destination)) {
            std::filesystem::create_directories(destination);
        }

        return copyAll(*this, destination);
    }

} // AllSyncer
