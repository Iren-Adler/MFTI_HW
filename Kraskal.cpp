#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> dsu;
std::vector<int> sz;

int Find(int u) {
  if (dsu[u] == -1) {
    return u;
  }
  return dsu[u] = Find(dsu[u]);
}

bool Unite(int u, int v) {
  u = Find(u);
  v = Find(v);
  if (u == v) {
    return false;
  }
  if (sz[u] > sz[v]) {
    std::swap(u, v);
  }
  dsu[u] = v;
  sz[v] += sz[u];
  return true;
}

class Graph {
 private:
  std::vector<std::pair<int, std::pair<int, int>>> edges_;
  size_t v_;
  size_t e_;

 public:
  explicit Graph(int n, int m) {
    edges_.resize(m);
    v_ = n;
    e_ = m;
  }

  void GetEdges() {
    for (size_t i = 0; i < e_; ++i) {
      int u, v, w;
      std::cin >> u >> v >> w;
      --u;
      --v;
      edges_[i].second.first = u;
      edges_[i].second.second = v;
      edges_[i].first = w;
    }
  }

  int GetAns() {
    int ans = 0;
    for (auto edge : edges_) {
      if (Unite(edge.second.first, edge.second.second)) {
        ans += edge.first;
      }
    }
    return ans;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  Graph g(n, m);
  g.GetEdges();
  dsu.resize(n, -1);
  sz.resize(n, 1);

  std::cout << g.GetAns() << std::endl;

  return 0;
}