#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <filesystem>
extern "C" {
    #include "ini.h"
}

struct conf {
    bool use_dir;
    std::string dir_start;
    std::string filenames;
    std::string dir_end;
    bool processors_reducing;
    std::vector <int> processors_num;
};

struct vivod_final{
    std::string name_file;
    int proc_num;
    int par_degree;
    int time_cons;
    int time_par;
    double c_percent;
    int s[3][10];
    int srt[10];
    int por[10];
};

int handler(void* user, const char* section, const char* name, const char* value);
std::string dir_reader(const std::string& path);
void str_to_processors(bool processors_reducing, std::string string, std::vector <int>& proc);
void logic_start(std::string file_start, const std::vector <int>& proc, std::filesystem::path path);
vivod_final Wanna_work_with_matrix(std::vector<std::vector<int>>& matrix, int kolvoproc);
void aswer_me_pls(std::filesystem::path path, const vivod_final& result);
int max(int i1, int i2);
int max(int i1, int i2, int i3);
int max(int i1, int i2, int i3, int i4);
int max(int i1, int i2, int i3, int i4, int i5);
int min(int q[10]);
int min(int q[10], int porog);
void vivod(int s[3][10], int srt[10], int por[10]);
void matini(int q[], int l);