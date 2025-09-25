#include "project.h"
void logic_start(std::string file_start, 
    const std::vector <int>& proc, std::filesystem::path path) {    
  size_t rows = 10, cols = 3;
  std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, -1));
  std::ifstream file(file_start);
  if (!file) {
    std::cerr << "Не удалось открыть файл\n";
    return;
  }
  std::string line;
  size_t r = 0;
  while (r < rows && std::getline(file, line)) {
    if (line == "jump") {
      r++;
      continue;
    }
    int r1, r2, r3;
    if (std::sscanf(line.c_str(), "R%d,R%d -> R%d", &r1, &r2, &r3) == 3) {
      matrix[r][0] = r1, matrix[r][1] = r2, matrix[r++][2] = r3;
    }
    else {
    std::cerr << "Ошибка данных в строке " << line << " файла " << file_start <<  ", не хехе\n";
    return;
  }
  }
  if (r < 10) {
    std::cerr << "Ошибка количества данных в файле " << file_start <<  ", не хехе\n";
    return;
  }
    if (!std::filesystem::exists(path)) 
     std::filesystem::create_directories(path);
//   std::cout << path << '\n';
  vivod_final info_result;
  for (auto processor : proc) {
    info_result = Wanna_work_with_matrix(matrix, processor);
    info_result.name_file = file_start;
    info_result.proc_num = processor;
    std::string img_name = "distr_" + std::to_string(processor) + ".txt";
    std::string file_name = "vivod_" + std::to_string(processor) + ".txt";
    std::filesystem::path full_path_ans =
        std::filesystem::path(path) / file_name;
    std::filesystem::path full_path_img =
        std::filesystem::path(path) / img_name;
    aswer_me_pls(full_path_ans, info_result);
    draw_me_pls(full_path_img, info_result.s, info_result.srt, info_result.por, info_result.proc_num);
  }
}

vivod_final Wanna_work_with_matrix(std::vector<std::vector<int>>& matrix, int kolvoproc){
    vivod_final result;
    int s[3][10];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 10; j++)
            s[i][j] = matrix[j][i];

    //vivod(s);
    int porog = 0;
    int r[30]; // коэффициенты сложности получения
    int por[10];// коэффициент операции
    int sch[30]; // коэффициенты для используемых значений
    int srt[10]; // упоряточенный массив

    int tic[120];
    // kolvoproc; // Количество процессоров
    matini(r, 30);
    matini(por, 10);
    matini(sch, 30);
    matini(srt, 10);
    matini(tic, 120);
    //matini(r, 30);

    for (int y = 0; y < 10; y++)
    {
        if (s[1][y] == -1)
        {
            porog += 10;
            por[y] = porog;
            tic[por[y]]++;
        }
        else
        {
            por[y] = max(porog, r[s[1][y]], r[s[0][y]]) + 1;
            if (tic[por[y]] < kolvoproc)
            {
                tic[por[y]]++;
            }
            else
            {
                for (por[y]; tic[por[y]] >= kolvoproc; por[y]++);  // Поиск свободного места
                tic[por[y]]++;
            }
            if (sch[s[0][y]] < por[y])
            {
                sch[s[0][y]] = por[y];
            }
            if (sch[s[1][y]] < por[y])  // максимальный уровень использования операции
            {
                sch[s[1][y]] = por[y];
            }

            if (por[y] <= sch[s[2][y]])  // проверка на то не уйдет ли изменение переменной выше использования её прошлого значения
            {
                por[y] = sch[s[2][y]] + 1;
            }
            r[s[2][y]] = por[y];


        }
    }

    /*for (int i = 0; i < 10; i++)
    {
        std::cout << por[i] <<"----"<<i<< '\n';
    }*/
    int beg = 0;
    int lvl = por[0];
    int buf = 0;
    for (int i = 1; i < 10; i++)
    {
        lvl = por[lvl] > por[i] ? por[i] : lvl;
    }
    bool serch = true;

    for (int i = 0; i < 10; i++)
    {
        while (serch)
        {
            if (beg < 10)
            {
                if (por[beg] == lvl)
                {
                    srt[i] = beg;
                    serch = false;
                }
                beg++;

            }
            else
            {
                beg = 0;
                buf = lvl + 1;
                for (int i = 1; i < 10; i++)
                {
                    lvl = ((lvl > por[i]) && (por[i] >= buf) || (lvl < buf)) ? por[i] : lvl;
                }
                //lvl = por[min(por, lvl+1)];

            }

        }
        serch = true;
    }
    std::memcpy(result.s, s, sizeof(s));
    std::memcpy(result.srt, srt, sizeof(srt));
    std::memcpy(result.por, por, sizeof(por));
    int cur = 0;
    for (int i = 0; i < 120; i++)
    {
        cur = cur < tic[i] ? tic[i] : cur;
    }
    result.par_degree = cur;
    result.time_cons = 10;
    // std::cout << "1.1) " << cur << '\n';
    cur = 0;
    for (int i = 0; i < 120; i++)
    {
        if (tic[i] != 0)
        {
            cur++;
        }
    }
    // std::cout << "1.3) " << cur << '\n';
    result.time_par = cur;
    double w = cur;
    double err = (double)10 / w;
    // std::cout << "1.4) " << err << '\n';
    result.c_percent = err;
    // std::cout << '\n' << '\n';
    return result;
}