#include <iostream>
#include <vector>

int main() {
  int vertex;
  std::cin >> vertex;
  std::vector<std::vector<int>> dist;
  dist.resize(vertex, std::vector<int>(vertex));
  for (int i = 0; i < vertex; ++i) {
    for (int j = 0; j < vertex; ++j) {
      std::cin >> dist[i][j];
    }
  }
  for (int k = 0; k < vertex; ++k) {
    for (int x = 0; x < vertex; ++x) {
      for (int y = 0; y < vertex; ++y) {
        dist[x][y] = std::min(dist[x][y], dist[x][k] + dist[k][y]);
      }
    }
  }
  for (int x = 0; x < vertex; ++x) {
    for (int y = 0; y < vertex; ++y) {
      std::cout << dist[x][y] << " ";
    }
    std::cout << '\n';
  }
  return 0;
}