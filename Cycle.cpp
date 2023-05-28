#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> adjacent_;
  std::vector<int> color_;
  std::vector<int> in_time_;
  std::vector<int> ans_;
  int found_cycle_;
  size_t v_;
  size_t e_;

 public:
  explicit Graph(int n, int m) {
    adjacent_.resize(n);
    color_.resize(n);
    in_time_.resize(n);
    found_cycle_ = 0;
    v_ = n;
    e_ = m;
  }

  void GetEdges() {
    for (size_t i = 0; i < e_; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u;
      --v;
      adjacent_[u].push_back(v);
    }
  }

  int GetColor(int u) {
    return color_[u];
  }

  void Dfs(int u, int& t) {
    color_[u] = 1;
    in_time_[u] = t++;
    for (int v : adjacent_[u]) {
      if (found_cycle_) {
        break;
      }
      if (color_[v] == 0) {
        Dfs(v, t);
      } else if (color_[v] == 1) {
        found_cycle_ = in_time_[v];
        break;
      }
    }
    if (found_cycle_ && in_time_[u] >= found_cycle_) {
      ans_.push_back(u + 1);
    }
    color_[u] = 2;
  }

  int Found() {
    return found_cycle_;
  }

  void GetCycle() {
    if (!found_cycle_) {
      std::cout << "NO" << std::endl;
    } else {
      std::cout << "YES" << std::endl;
      for (size_t i = ans_.size(); i > 0; --i) {
        std::cout << ans_[i - 1] << " ";
      }
      std::cout << std::endl;
    }
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n, m);
  g.GetEdges();
  int t = 1;
  for (int u = 0; u < n; ++u) {
    if (g.GetColor(u) == 0) {
      g.Dfs(u, t);
      if (g.Found()) {
        break;
      }
    }
  }
  g.GetCycle();

  return 0;
}