#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

using namespace std::literals;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vii = std::vector<ii>;

class DSU {
 public:
  explicit DSU(size_t size)
      : p_(vi(size + 1))
      , r_(vi(size + 1, 1)) {
    std::iota(p_.begin(), p_.end(), 0);
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
      p_[b] = a;
    } else {
      p_[a] = b;
    }
  }

 private:
  mutable vi p_, r_;
};

struct Request {
  char r;
  int u;
  int v;
};

void Solution(std::istream& cin, std::ostream& cout) {
  int vertices_n, edges_n, requests_n;
  cin >> vertices_n >> edges_n >> requests_n;
  for (int i = 0; i < edges_n; ++i) {
    int u, v;
    cin >> u >> v;
  }
  std::vector<Request> requests(requests_n);
  for (int i = 0; i < requests_n; ++i) {
    std::string cmd;
    cin >> cmd;
    requests[i].r = cmd[0];
    cin >> requests[i].u >> requests[i].v;
  }
  DSU dsu(vertices_n);
  std::vector<bool> ans;
  for (int i = requests_n - 1; i >= 0; --i) {
    if (requests[i].r == 'c') {
      dsu.Union(requests[i].u, requests[i].v);
    } else if (requests[i].r == 'a') {
      ans.push_back(dsu.Get(requests[i].u) == dsu.Get(requests[i].v));
    }
  }
  for (auto a : std::ranges::reverse_view(ans)) {
    cout << (a ? "YES" : "NO") << '\n';
  }
}

[[maybe_unused]] void TestSolution() {
  std::istringstream cin("3 3 7\n"
                         "1 2\n"
                         "2 3\n"
                         "3 1\n"
                         "ask 3 3\n"
                         "cut 1 2\n"
                         "ask 1 2\n"
                         "cut 1 3\n"
                         "ask 2 1\n"
                         "cut 2 3\n"
                         "ask 3 1\n"s);
  std::ostringstream cout;
  std::string expected_cout("YES\n"
                            "YES\n"
                            "NO\n"
                            "NO\n");
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
