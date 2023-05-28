#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int Min(int a, int b) {
  return a < b ? a : b;
}

void ZFunction(string& s) {
  int n = s.length();
  vector<int> z(n);
  int l = 0;
  int r = 0;
  z[0] = n;
  for (int i = 1; i < n; i++) {
    if (i <= r) {
      z[i] = Min(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  for (auto elem : z) {
    cout << elem << " ";
  }
}

int main() {
  string s;
  cin >> s;
  ZFunction(s);
  return 0;
}
