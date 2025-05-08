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
      , sum_(vi(size + 1)) {
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Get(int a) const {
    return a == p_[a] ? a : Get(p_[a]);
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
      sum_[b] -= sum_[a];
      p_[b] = a;
    } else {
      sum_[a] -= sum_[b];
      p_[a] = b;
    }
  }

  void Add(int a, int x) {
    sum_[Get(a)] += x;
  }

  int Sum(int a) const {
    int s = 0;
    while (a != p_[a]) {
      s += sum_[a];
      a = p_[a];
    }
    s += sum_[a];
    return s;
  }

 private:
  mutable vi p_, r_, sum_;
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, m;
  cin >> n >> m;
  DSU dsu(n);
  for (int i = 0; i < m; ++i) {
    std::string cmd;
    cin >> cmd;
    if (cmd[0] == 'j') {
      int x, y;
      cin >> x >> y;
      dsu.Union(x, y);
    } else if (cmd[0] == 'g') {
      int x;
      cin >> x;
      cout << dsu.Sum(x) << '\n';
    } else if (cmd[0] == 'a') {
      int x, v;
      cin >> x >> v;
      dsu.Add(x, v);
    }
  }
}

[[maybe_unused]] void TestSolution() {
  std::istringstream cin("3 6\n"
                         "add 1 100\n"
                         "join 1 3\n"
                         "add 1 50\n"
                         "get 1\n"
                         "get 2\n"
                         "get 3\n"s);
  std::ostringstream cout;
  std::string expected_cout("150\n"
                            "0\n"
                            "50\n");
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
