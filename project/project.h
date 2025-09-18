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

int handler(void* user, const char* section, const char* name, const char* value);
std::string dir_reader(const std::string& path);