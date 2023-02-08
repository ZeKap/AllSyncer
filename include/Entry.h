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
         * Copy all files from one Entry to a destination set in String
         * @param src Entry, to get its src, perms and edit time
         * @param dest string to the src where to copy the entry
         * @return error code if there is one
         */
        void copyAll();
        /**
         * @brief Copy one file to destination, with the options from filesystem lib
         *
         * @param src the Entry type of the file to copy
         * @param dest the destination in a String
         * @param options one or more of the enum in the filesystem lib
         */
        void copyFile();
        /**
         * @brief Copy a folder to the destination in parameter and its contents
         *
         * @param src the Entry type to copy from
         * @param dest the destination to copy to
         * @return the code error if any
         */
        void copyFolder();
    public:
        /**
         * Constructor of the files, from the given src it get editTime and perms
         * @param path: string src
         */
        explicit Entry(const std::string& path, const std::string& dest, const json & configInput);
        #pragma clang diagnostic push
        #pragma ide diagnostic ignored "modernize-use-nodiscard"
        /**
         * Copy the file contents edit time and perms to the given destination
         * @return a code error
         */
        void copy() const;
        #pragma clang diagnostic pop
    };

} // AllSyncer

#endif //ALLSYNCER_ENTRY_H
