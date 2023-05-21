#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using vi = std::vector<int>;
using namespace std::literals;

class DSU {
 public:
  explicit DSU(size_t size) : p_(vi(size + 1)), r_(vi(size + 1, 1)) {
    std::iota(p_.begin(), p_.end(), 0);
  }
  int Get(int a) {
    return p_[a] = (a == p_[a] ? a : Get(p_[a]));
  }
  void Union(int a, int b) {
    a = Get(a);
    b = Get(b);
    if (r_[a] == r_[b])
      ++r_[a];
    if (r_[a] > r_[b])
      p_[b] = a;
    else
      p_[a] = b;
  }
 private:
  vi p_, r_;
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, m;
  cin >> n >> m;
  DSU dsu(n);
  for (int i = 0; i < m; ++i) {
    std::string cmd;
    int u, v;
    cin >> cmd >> u >> v;
    if (cmd[0] == 'u') {
      dsu.Union(u, v);
    } else if (cmd[0] == 'g') {
      const auto pu = dsu.Get(u);
      const auto vu = dsu.Get(v);
      cout << (pu == vu ? "YES" : "NO") << '\n';
    }
  }
}

[[maybe_unused]] void TestSolution() {
  std::istringstream cin("4 4\n"
                         "union 1 2\n"
                         "union 1 3\n"
                         "get 1 4\n"
                         "get 2 3\n"s);
  std::ostringstream cout;
  std::string expected_cout("NO\n"
                            "YES\n");
  Solution(cin, cout);
  const auto actual_cout = cout.str();
  assert(actual_cout == expected_cout);
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
#ifndef NDEBUG
  TestSolution();
#endif
  Solution(std::cin, std::cout);
  return 0;
}
