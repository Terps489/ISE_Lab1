#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
extern "C" {
    #include "ini.h"
}

struct conf {
    bool use_dir;
    std::string dir_start;
    std::string filenames;
    std::string dir_end;
};

std::string dir_reader(const std::string& path) {
    std::string result;
    for (auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            if (!result.empty()) result += ' ';
            result += (path + "/" + entry.path().filename().string());
        }
    }
    return result;
}

int handler(void* user, const char* section, const char* name, const char* value) {
    conf* pconfig = (conf*)user;
    std::string key = name;
    std::string val = value;

    if (key == "use_dir") pconfig -> use_dir = (val == "true");
    else if (pconfig -> use_dir && key == "dir_start") pconfig->dir_start = val;
    else if (key == "filename_start") pconfig->filenames = (pconfig -> use_dir) ? dir_reader(pconfig->dir_start) : val;
    else if (key == "dir_end") pconfig->dir_end = val;
    else return 0;
    return 1;
}

int main() {
    conf cfg;
    if (ini_parse("config.ini", handler, &cfg) < 0) {
        std::cerr << "Не удалось прочитать config.ini\n";
        return 1;
    }

    std::cout << "dir_start: " << cfg.dir_start << '\n';
    std::cout << "filename:  " << cfg.filenames << '\n';
    std::cout << "dir_end:   " << cfg.dir_end << '\n';
    std::cout << "use_dir: " << cfg.use_dir << '\n';
    if (cfg.filenames.empty()) {
        std::cerr << "В конфиге нет файлов.\n";
        return 1;
    }
    std::istringstream stream(cfg.filenames);
    std::vector<std::string> filenames;
    std::string filename;

    while (stream >> filename) {
        filenames.push_back(filename);
    }
    std::cout << filenames[0] << "\n";

    return 0;
}