//
// Created by kap on 30/12/22.
//

#include <iostream>
#include "../include/Entry.h"

namespace AllSyncer {
    Entry::Entry(const std::string& path, const std::string& dest, const json & configInput) {
        // check if the file exists
        if(!std::filesystem::exists(path)) {
            exit(1);
        }

        // store src to the file, its edit time and its permissions
        this->src = path;
        this->dest = dest;
        this->editTime = std::filesystem::last_write_time(path);
        this->perms = std::filesystem::status(path).permissions();

        // store config in object
        this->config = configInput;
    }


#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
    void Entry::copyAll() {

        switch (std::filesystem::status(src).type()) {

            // if the src is a file
            case std::filesystem::file_type::regular:
                // copy only the file
                copyFile();
                break;


            // if it's a folder, check if it needs to be forced sync
            case std::filesystem::file_type::directory: {

                // check the folder name to check if it needs to be synced
                auto find = std::find(config["folderAlways"].begin(),
                                      config["folderAlways"].end(),
                                      src.filename().string());
                // we force sync when we find the filename in the config in folderAlways
                if (find != config["folderAlways"].end()) {
                    forceCopyFolder();
                } else {
                    copyFolder();
                }

                break;
            }


            default:
                break;
        }
    }
#pragma clang diagnostic pop


    void Entry::copyFile() {

        // we need to check if the file need to be copied before copying it, or we create it
        std::filesystem::file_time_type srcEditTime = editTime;

        if((std::filesystem::exists(dest) &&
                srcEditTime > std::filesystem::last_write_time(dest))
            || !std::filesystem::exists(dest)) {
            try {

                // copy content of the entry
                std::filesystem::copy(src, dest/*, options*/);

                // copy its edit time and permissions
                std::filesystem::last_write_time(dest, editTime);
                std::filesystem::permissions(dest, perms);

                std::cout << "File   " << src << "\n   --> "
                          << dest << std::endl;

            } catch (std::filesystem::filesystem_error &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }


#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
    void Entry::copyFolder() {

        // we need to check if the folder need to be copied before copying it, or we create it
        std::filesystem::file_time_type srcEditTime = editTime;

        if((std::filesystem::exists(dest) &&
            srcEditTime > std::filesystem::last_write_time(dest))
           || !std::filesystem::exists(dest)) {
            try {

                if(!std::filesystem::exists(dest)) {
                    std::filesystem::create_directories(dest);
                }

                // copy its edit time and permissions
                std::filesystem::last_write_time(dest, editTime);
                std::filesystem::permissions(dest, perms);

                std::cout << "Folder \"" << src.string() << "\"\n   --> "
                          << dest << std::endl;

                // if the folder is empty, we stop here
                if(std::filesystem::is_empty(src)) {
                    return;
                }

            } catch (std::filesystem::filesystem_error &e) {
                std::cerr << e.what() << std::endl;
            }
        }

        // anyway let's copy its contents
        for(const std::filesystem::directory_entry& newEntry : std::filesystem::directory_iterator(src)) {
            Entry entry(newEntry.path(), dest/newEntry.path().filename(), config);
            entry.copyAll();
            //copyAll(Entry(newEntry.path(), src.config), dest / newEntry.path().filename());
        }
    }

    void Entry::forceCopyFolder() {
        std::filesystem::remove_all(dest);
        std::cout << "Removed " << dest << " because it's in the list of force sync" << std::endl;
        copyFolder();
        std::cout << "Copied " << dest << " and now we're synced" << std::endl;
    }
#pragma clang diagnostic pop


    void Entry::copy() {

        // if the source doesn't exist, display an error
        if (!std::filesystem::exists(src)) {
            std::cerr << "Error: source path does not exist: " << src << std::endl;
            return;
        }

        // if the destination doesn't exist, create it
        if(std::filesystem::exists(dest)) {
            std::filesystem::create_directories(dest);
        }

        copyAll();
    }

} // AllSyncer
