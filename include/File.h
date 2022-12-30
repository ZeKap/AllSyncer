//
// Created by kap on 30/12/22.
//

#ifndef ALLSYNCER_FILE_H
#define ALLSYNCER_FILE_H

#include <filesystem>

namespace AllSyncer {

    /**
     * Class to use filesystem lib but easier
     * @author <a href="https://github.com/ZeKap">ZeKap</a>
     */
    class File {
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
    public:
        /**
         * Constructor of the files, from the given path it get editTime and perms
         * @param path: string path
         */
        explicit File(const std::string& path);
        /**
         * Copy the file contents edit time and perms to the given destination
         */
        void copyAll(const std::string& destination);
    };

} // AllSyncer

#endif //ALLSYNCER_FILE_H
