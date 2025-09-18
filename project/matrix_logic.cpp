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
  for (auto& row : matrix) {
    for (auto val : row) std::cout << val << " ";
    std::cout << "\n";
  }
  std::cout << std::endl;
}