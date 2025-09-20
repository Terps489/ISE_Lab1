#include "project.h"
void logic_start(std::string file_start) {
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
  Wanna_work_with_matrix(matrix);
}

void Wanna_work_with_matrix(std::vector<std::vector<int>>& matrix){
//   for (auto& row : matrix) {
//     for (auto val : row) std::cout << val << " ";
//     std::cout << "\n";
//   }
//   std::cout << std::endl;
    int s[3][10];
    s = matrix;
    int porog = 0;
    int r[30]; // коэффициенты сложности получения
    int por[10];// коэффициент операции
    int sch[30]; // коэффициенты для используемых значений
    int srt[10]; // упоряточенный массив
    int cur;

    int tic[120];
    int kolvoproc=10;


    for (int y = 0; y < 10; y++)
    {
        if (s[1][y] == -1)
        {
            porog += 10;
            por[y] = porog+1;
        }
        else
        {
            por[y] = max(porog, r[s[1][y]], r[s[0][y]])+1;
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
    int beg=0;
    int lvl= por[min(por)];
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
                lvl = por[min(por, lvl)];

            }

        }
        serch = true;
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
    if (max(i1, i2) > i3)
    {
        return i3;
    }
    return max(i1, i2);
}
int max(int i1, int i2, int i3, int i4)
{
    if (max(i1, i2) > max(i3,i4))
    {
        return max(i3, i4);
    }
    return max(i1, i2);
}
int max(int i1, int i2, int i3, int i, int i5)
{
    if (max(i1, i2,i5) > max(i3, i4))
    {
        return max(i3, i4);
    }
    return max(i1, i2, i5);
}
int min(int q[10])
{
    int rez=0;
    for (int i = 1; i < 10; i++)
    {
        rez = q[rez] > q[i] ? q[i] : rez;
    }
    return rez;

}
int min(int q[10], int porog)
{
    int rez=0;
    for (int i = 1; i < 10; i++)
    {
        rez = ((q[rez] > q[i]) &&(q[i]>porog) || (q[rez]<=porog)) ? q[i] : rez;
    }
    return rez;
}


void vivod(int s[3][10], int srt[10])
{
    int cur;
    for (int i = 0; i < 10; i++)
    {
        cur = srt[i];
        std::cerr << "R" << s[0][cur] << " + R" << s[1][cur] << " --> " << s[2][cur];
    }
}