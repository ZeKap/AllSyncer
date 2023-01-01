//
// Created by kap on 30/12/22.
//

#ifndef ALLSYNCER_ENTRY_H
#define ALLSYNCER_ENTRY_H

#include <filesystem>

namespace AllSyncer {

    /**
     * Class to use filesystem lib but easier
     * @author <a href="https://github.com/ZeKap">ZeKap</a>
     */
    class Entry {
    private:
        /**
         * Path to the file
         */
        std::filesystem::path path;
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
         * @param src Entry, to get its path, perms and edit time
         * @param dest string to the path where to copy the entry
         * @return error code if there is one
         */
        static int copyAll(const AllSyncer::Entry& src, const std::string &dest);
    public:
        /**
         * Constructor of the files, from the given path it get editTime and perms
         * @param path: string path
         */
        explicit Entry(const std::string& path);
#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
        /**
         * Copy the file contents edit time and perms to the given destination
         * @return a code error
         */
        int copyAll(const std::string& destination) const;
#pragma clang diagnostic pop
    };

} // AllSyncer

#endif //ALLSYNCER_ENTRY_H
