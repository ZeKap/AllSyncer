//
// Created by kap on 30/12/22.
//

#ifndef ALLSYNCER_ENTRY_H
#define ALLSYNCER_ENTRY_H

#include <filesystem>
#include "../nlohmann-json/json.hpp"
using json = nlohmann::json;

namespace AllSyncer {

    /**
     * Class to use filesystem lib but easier
     * @author <a href="https://github.com/ZeKap">ZeKap</a>
     */
    class Entry {
    private:
        /**
         * JSON config parsed, given for each time an entry is created
         */
        json config;
        /**
         * Path to the file
         */
        std::filesystem::path src;
        /**
         * Path to destination
         */
        std::filesystem::path dest;
        /**
         * Last edit time
         */
        std::filesystem::file_time_type editTime;
        /**
         * Permissions
         */
        std::filesystem::perms perms;
        /**
         * @brief Copy all files and folders from the Entry src to the Entry dest, will call copyFile and copyFolder
         */
        void copyAll();
        /**
         * @brief Copy Entry as a file
         */
        void copyFile();
        /**
         * @brief Copy Entry as a folder (is recursive)
         */
        void copyFolder();
        /**
         * Called when config says to force a sync, will delete folder and recreate it
         */
        void forceCopyFolder();
    public:
        /**
         * Constructor of the files, from the given src it get editTime and perms
         * @param path: string src
         */
        explicit Entry(const std::string& path, const std::string& dest, const json & configInput);
        #pragma clang diagnostic push
        #pragma ide diagnostic ignored "modernize-use-nodiscard"
        /**
         * Only public copy function, will create folder to source if not existing and call other copy functions
         */
        void copy();
        #pragma clang diagnostic pop
    };

} // AllSyncer

#endif //ALLSYNCER_ENTRY_H
