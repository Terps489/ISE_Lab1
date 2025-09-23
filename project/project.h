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
    std::string processors_num;
};

struct vivod{
    std::string name_file;
    int par_degree;
    int time_cons;
    int time_par;
    double c_percent;
};

int handler(void* user, const char* section, const char* name, const char* value);
std::string dir_reader(const std::string& path);
void logic_start(std::string file_start, int *proc);
void Wanna_work_with_matrix(std::vector<std::vector<int>>& matrix, int kolvoproc);
int max(int i1, int i2);
int max(int i1, int i2, int i3);
int max(int i1, int i2, int i3, int i4);
int max(int i1, int i2, int i3, int i4, int i5);
int min(int q[10]);
int min(int q[10], int porog);
void vivod(int s[3][10], int srt[10]);
void matini(int q[], int l);