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
    int cur;
    for (int y = 0; y < 10; y++)
    {
        if (s[1][y] != -1)
        {
            porog += 10;
            por[y] = porog;
        }
        else
        {
            por[y] = max3(porog, r[s[1][y]], r[s[0][y]]);
            r[s[2][y]] = por[y];
        }
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
int max3(int i1, int i2, int i3)
{
    if (max(i1, i2) > i3)
    {
        return i3;
    }
    return max(i1, i2);
}