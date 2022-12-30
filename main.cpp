#include <iostream>
#include <fstream>
#include <filesystem>


std::string fileFromPath = "/home/kap/test/copy-2/from/file.txt";
std::string fileToPath = "/home/kap/test/copy-2/to/file.txt";

int main() {
    std::filesystem::path input(fileFromPath);
    std::filesystem::path output(fileToPath);

    // if there is a problem opening one of the files
    if(!std::filesystem::exists(input)) {
        std::cout << "Error" << std::endl;
    }

    // copy file
    std::filesystem::copy_file(input, output, std::filesystem::copy_options::overwrite_existing);

    // get last write time
    std::filesystem::file_time_type lastWriteTime = std::filesystem::last_write_time(input);
    // copy it to the file
    std::filesystem::last_write_time(output, lastWriteTime);

    // get permissions
    std::filesystem::perms perms = std::filesystem::status(input).permissions();
    // copy it to the file
    std::filesystem::permissions(output, perms);

    return 0;
}
