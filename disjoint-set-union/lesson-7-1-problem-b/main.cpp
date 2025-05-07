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
  explicit DSU(size_t size)
      : p_(vi(size + 1))
      , r_(vi(size + 1, 1))
      , min_(vi(size + 1))
      , max_(vi(size + 1))
      , count_(vi(size + 1, 1)) {
    std::iota(p_.begin(), p_.end(), 0);
    std::iota(min_.begin(), min_.end(), 0);
    std::iota(max_.begin(), max_.end(), 0);
  }
  int Get(int a) const {
    return p_[a] = (a == p_[a] ? a : Get(p_[a]));
  }
  void Union(int a, int b) {
    a = Get(a);
    b = Get(b);
    if (a == b) {
      return;
    }
    if (r_[a] == r_[b]) {
      ++r_[a];
    }
    if (r_[a] > r_[b]) {
      min_[a] = std::min(min_[a], min_[b]);
      max_[a] = std::max(max_[a], max_[b]);
      count_[a] += count_[b];
      p_[b] = a;
    } else {
      min_[b] = std::min(min_[a], min_[b]);
      max_[b] = std::max(max_[a], max_[b]);
      count_[b] += count_[a];
      p_[a] = b;
    }
  }
  int Min(int a) const {
    return min_[Get(a)];
  }
  int Max(int a) const {
    return max_[Get(a)];
  }
  int Count(int a) const {
    return count_[Get(a)];
  }
 private:
  mutable vi p_, r_, min_, max_, count_;
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, m;
  cin >> n >> m;
  DSU dsu(n);
  for (int i = 0; i < m; ++i) {
    std::string cmd;
    cin >> cmd;
    if (cmd[0] == 'u') {
      int u, v;
      cin >> u >> v;
      dsu.Union(u, v);
    } else if (cmd[0] == 'g') {
      int u;
      cin >> u;
      cout << dsu.Min(u) << ' ' << dsu.Max(u) << ' ' << dsu.Count(u) << '\n';
    }
  }
}

[[maybe_unused]] void TestSolution() {
  std::istringstream cin("5 11\n"
                         "union 1 2\n"
                         "get 3\n"
                         "get 2\n"
                         "union 2 3\n"
                         "get 2\n"
                         "union 1 3\n"
                         "get 5\n"
                         "union 4 5\n"
                         "get 5\n"
                         "union 4 1\n"
                         "get 5\n"s);
  std::ostringstream cout;
  std::string expected_cout("3 3 1\n"
                            "1 2 2\n"
                            "1 3 3\n"
                            "5 5 1\n"
                            "4 5 2\n"
                            "1 5 5\n");
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
