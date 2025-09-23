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
    std::cerr << "Ошибка данных, не хехе\n";
    return;
  }
  }
  std::cout << path << '\n';
  vivod_final info_result;
  for (auto processor : proc) {
    std::cout << processor << '\n';
    info_result = Wanna_work_with_matrix(matrix, processor);
    info_result.name_file = file_start;
    std::string file_name = "vivod_" + std::to_string(processor) + ".txt";
    std::filesystem::path full_path =
        std::filesystem::path(path) / file_name;
    aswer_me_pls(full_path,info_result);
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
    //vivod(s, srt,por);
    int cur;
    for (int i = 0; i < 10; i++)
    {
        cur = srt[i];
        std::cout << "R" << s[0][cur] << " + R" << s[1][cur] << " --> R" << s[2][cur] << "   Diff:" << por[cur] << "   Num:" << srt[i] << '\n';
    }
    cur = 0;
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
    std::cout << '\n' << '\n';
    return result;
}


void matini(int q[], int l)
{
    for (int i = 0; i < l; i++)
    {
        q[i] = 0;
    }
}

int max(int i1, int i2)
{
    if (i1 > i2)
    {
        return i1;
    }
    return i2;
}
int max(int i1, int i2, int i3)
{
    if (max(i1, i2) < i3)
    {
        return i3;
    }
    return max(i1, i2);
}
int max(int i1, int i2, int i3, int i4)
{
    if (max(i1, i2) < max(i3, i4))
    {
        return max(i3, i4);
    }
    return max(i1, i2);
}
int max(int i1, int i2, int i3, int i4, int i5)
{
    if (max(i1, i2, i5) < max(i3, i4))
    {
        return max(i3, i4);
    }
    return max(i1, i2, i5);
}
int min(int q[10])
{
    int rez = 0;
    for (int i = 1; i < 10; i++)
    {
        rez = q[rez] > q[i] ? q[i] : rez;
    }
    return rez;

}
int min(int q[], int porog)
{
    int rez = 0;
    for (int i = 1; i < 10; i++)
    {
        rez = ((q[rez] > q[i]) && (q[i] > porog) || (q[rez] <= porog)) ? q[i] : rez;
    }
    return rez;
}

void aswer_me_pls(std::filesystem::path path,vivod_final result){
    std::ofstream out(path);
    if (!out) {
        std::cerr << "Не удалось создать файл: " << path << '\n';
        return;
    }
    out.close();
}