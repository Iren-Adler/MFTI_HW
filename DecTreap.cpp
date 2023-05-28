#include <iostream>
#include <vector>

struct Node {
 public:
  int key;
  int priority;

  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

Node* Treap(std::vector<std::pair<int, int>>& values, Node** vertexs) {
  Node* root = nullptr;
  Node* leaf = nullptr;

  for (size_t i = 0; i < values.size(); ++i) {
    std::pair<int, int> value = values[i];
    Node* new_node = new Node{value.first, value.second};
    Node* vertex = leaf;

    while (vertex != nullptr && value.second < vertex->priority) {
      vertex = vertex->parent;
    }

    if (vertex == nullptr) {
      new_node->left = root;

      if (root != nullptr) {
        root->parent = new_node;
      }

      root = new_node;
    } else {
      new_node->left = vertex->right;
      if (vertex->right != nullptr) {
        vertex->right->parent = new_node;
      }
      vertex->right = new_node;
      new_node->parent = vertex;
    }

    leaf = new_node;

    vertexs[i] = new_node;
  }
  return root;
}


void InorderWalk(Node* x) {
  if (x != nullptr) {
    InorderWalk(x->left);
    std::cout << (x->parent != nullptr ? x->parent->key : 0) << ' ';
    std::cout << (x->left != nullptr ? x->left->key : 0) << ' ';
    std::cout << (x->right != nullptr ? x->right->key : 0) << '\n';
  }
    InorderWalk(x->right);
}

void Clear(Node** vertexs, int& n) {
  for (int i = 0; i < n; ++i) {
    delete vertexs[i];
  }
  delete[] vertexs;  
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> values(n);
  Node** vertexs = new Node*[n];
  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;
    values[i] = std::make_pair(i + 1, b);
  }

  Node* treap = Treap(values, vertexs);
  std::vector<std::pair<int, int>>().swap(values);
  std::cout << "YES\n";
  InorderWalk(treap);
  Clear(vertexs, n);
  return 0;
}