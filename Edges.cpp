#include <vector>
#include <map>

class Graph {
 private:
  std::vector<std::vector<int>> adjacent_;
  std::vector<std::pair<int, int>> edges_;
  std::vector<int> color_;
  std::vector<int> in_time_;
  std::vector<int> up_time_;
  std::vector<int> bridges_;
  std::map<std::pair<int, int>, int> cnt_;
  size_t v_;
  size_t e_;

 public:
  explicit Graph(int n, int m) {
    adjacent_.resize(n);
    edges_.resize(m);
    color_.resize(n);
    in_time_.resize(n);
    up_time_.resize(n);
    v_ = n;
    e_ = m;
  }

  void GetEdges() {
    for (size_t i = 0; i < e_; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u;
      --v;
      edges_[i].first = u;
      edges_[i].second = v;
      adjacent_[u].push_back(v);
      adjacent_[v].push_back(u);
      cnt_[std::make_pair(std::min(u, v), std::max(u, v))]++;
    }
  }

  int GetColor(int u) {
    return color_[u];
  }

  void Dfs(int u, int p, int& t) {
    ++t;
    color_[u] = 1;
    in_time_[u] = t;
    up_time_[u] = t;
    for (int v : adjacent_[u]) {
      if (color_[v] == 0) {
        Dfs(v, u, t);
        up_time_[u] = std::min(up_time_[u], up_time_[v]);
      } else if (color_[v] == 1 && v != p) {
        up_time_[u] = std::min(up_time_[u], in_time_[v]);
      }
    }
    color_[u] = 2;
  }

  void GetBridges() {
    for (size_t i = 0; i < e_; ++i) {
      int u = edges_[i].first, v = edges_[i].second;
      if (in_time_[v] < in_time_[u]) {
        std::swap(u, v);
      }
      if (in_time_[u] < up_time_[v] && u != v && cnt_[std::make_pair(std::min(u, v), std::max(u, v))] == 1) {
        bridges_.push_back(i + 1);
      }
    }
  }

  void OutputBridges() {
    std::cout << bridges_.size() << std::endl;
    for (int bridge : bridges_) {
      std::cout << bridge << " ";
    }
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n, m);
  g.GetEdges();
  int t = 0;
  for (int u = 0; u < n; ++u) {
    if (g.GetColor(u) == 0) {
      g.Dfs(u, -1, t);
    }
  }
  g.GetBridges();
  g.OutputBridges();

  return 0;
}