#include "project.h"

int main() {
  conf cfg;
  if (ini_parse("config.ini", handler, &cfg) < 0) {
    std::cerr << "Не удалось прочитать config.ini\n";
    return 1;
  }
  // for (auto a : cfg.processors_num) std::cout << a << "\n";
  // std::cout << "dir_start: " << cfg.dir_start << '\n';
  // std::cout << "filename:  " << cfg.filenames << '\n';
  // std::cout << "dir_end:   " << cfg.dir_end << '\n';
  // std::cout << "use_dir: " << cfg.use_dir << '\n';
  // std::cout << "processors_reducing: " << cfg.processors_reducing << '\n';
  // std::cout << "processors_num: " << cfg.processors_num << '\n';
  if (cfg.filenames.empty()) {
    std::cerr << "В конфиге нет файлов.\n";
    return 1;
  }
  std::istringstream stream(cfg.filenames);
  std::string filename;
  while (stream >> filename){
     std::filesystem::path file_path = filename; 
     std::string base_name = file_path.stem().string();
     std::filesystem::path target_dir = 
     std::filesystem::path(cfg.dir_end) / base_name;
     logic_start(filename, cfg.processors_num, target_dir);
  }
  return 0;
}

int handler(void* user, const char* section, const char* name, const char* value){
  conf* pconfig = (conf*)user;
  std::string key = name, val = value;
  if (key == "use_dir") pconfig->use_dir = (val == "true");
  else if (pconfig->use_dir && key == "dir_start") pconfig->dir_start = val;
  else if (key == "filename_start")pconfig->filenames = (pconfig->use_dir) ? dir_reader(pconfig->dir_start) : val;
  else if (key == "dir_end") pconfig->dir_end = val;
  else if (key == "processors_reducing") pconfig->processors_reducing = (val == "true");
  else if (key == "processors_num") str_to_processors(pconfig->processors_reducing, val, pconfig->processors_num);
  else return 0;
  return 1;
}

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

void str_to_processors(bool processors_reducing, std::string string, std::vector <int>& proc){
  std::istringstream stream(string);
  int num;
  if (!processors_reducing){
  while (stream >> num) proc.push_back(num);
  }
  else {
    stream >> num;
    while (num>1) proc.push_back(num--);
  }
  return;
}

void aswer_me_pls(std::filesystem::path path, const vivod_final& result) {
    std::ofstream out(path);
    if (!out) {
        std::cerr << "Не удалось создать файл: " << path << '\n';
        return;
    }
    out << "=== Результаты Работы проекта  === \n" ;
    out << "Имя файла: " << result.name_file << '\n';
    out << "Количество доступных процессоров: " << result.proc_num << '\n';
    out << "Степень параллельности потока команд: " << result.par_degree << '\n';
    out << "Время выполнения последовательной программы в условных единицах: " << result.time_cons << '\n';
    out << "Время выполнения параллельной программы в условных единицах: " << result.time_par << '\n';
    out << "Коэффициент роста производительности: " << result.c_percent << '\n';
}

void draw_me_pls(std::filesystem::path path, int s[3][10], int srt[10], int por[10], int proc){
    std::ofstream out(path);
    if (!out) {
        std::cerr << "Не удалось создать файл: " << path << '\n';
        return;
    }
    out << "=== Отрисовка проекта  === \n" ;
    for (int i = 1; i <= proc; i++) out << "proc " << i << "\t\t";
    out << "\n";
  for (int i = 0; i < 9; i++)
    {
        (s[0][srt[i]] == -1) ? out << "jump" :
            out << "R" << s[0][srt[i]] << ",R" << s[1][srt[i]] << " -> R" << s[2][srt[i]];
        (por[srt[i]] == por[srt[i+1]]) ? out << "\t" :  out <<"\n";
    }
    (s[0][srt[9]] == -1) ? out << "jump" :
        out << "R" << s[0][srt[9]] << ",R" << s[1][srt[9]] << " -> R" << s[2][srt[9]] << std::endl;
}