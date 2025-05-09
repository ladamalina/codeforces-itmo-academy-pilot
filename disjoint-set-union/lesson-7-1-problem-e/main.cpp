#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std::literals;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vii = std::vector<ii>;

class HashPair {
 public:
  size_t operator()(const ii& x) const {
    return x.first * 37 + x.second * 37 * 37;
  }
};

class DSU {
 public:
  explicit DSU(size_t size)
      : p_(vi(size + 1))
      , t1_(vi(size + 1, -1)) {
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Get(int a) const {
    return a == p_[a] ? a : Get(p_[a]);
  }

  void Union(int a, int b, int t) {
    const auto pa = Get(a);
    const auto pb = Get(b);
    if (pa == pb) {
      return;
    }
    if (pb > pa) {
      p_[pb] = pa;
    } else {
      p_[pa] = pb;
    }
    if (pa == 1) t1_[pb] = t;
    if (pb == 1) t1_[pa] = t;
  }

  int GetT1(int a) {
    if (a == 1) return -1;
    while (a != p_[a]) {
      if (t1_[a] != -1) {
        return t1_[a];
      }
      a = p_[a];
    }
    if (t1_[a] != -1) {
      return t1_[a];
    }
    return -1;
  }

 private:
  mutable vi p_, t1_;
};

void Solution(std::istream& cin, std::ostream& cout) {
  int monkeys_n, events_n;
  cin >> monkeys_n >> events_n;

  vii hands(monkeys_n + 1);
  std::unordered_multiset<ii, HashPair> edges;
  for (int i = 1; i <= monkeys_n; ++i) {
    int l, r;
    cin >> l >> r;
    hands[i] = {l, r};
    if (l != -1) edges.emplace(i, l);
    if (r != -1) edges.emplace(i, r);
  }
  vii events(events_n);
  for (int i = 0; i < events_n; ++i) {
    cin >> events[i].first;
    int hand;
    cin >> hand;
    events[i].second = (hand == 1) ? hands[events[i].first].first : hands[events[i].first].second;

    auto it = edges.find(events[i]);
    if (it != edges.end()) edges.erase(it);
  }
  DSU dsu(monkeys_n);
  for (const auto& [a, b] : edges) {
    dsu.Union(a, b, -1);
  }
  for (int i = events_n - 1; i >= 0; --i){
    dsu.Union(events[i].first, events[i].second, i);
  }
  for (int i = 1; i <= monkeys_n; ++i) {
    cout << dsu.GetT1(i) << '\n';
  }
}

[[maybe_unused]] void TestSolution() {
  {
    std::istringstream cin("3 2\n"
                           "-1 3\n"
                           "3 -1\n"
                           "1 2\n"
                           "1 2\n"
                           "3 1\n"s);
    std::ostringstream cout;
    std::string expected_cout("-1\n"
                              "1\n"
                              "1\n");
    Solution(cin, cout);
    const auto actual_cout = cout.str();
    assert(actual_cout == expected_cout);
  }
  {
    std::istringstream cin("4 5\n"
                           "2 2\n"
                           "3 -1\n"
                           "4 -1\n"
                           "-1 2\n"
                           "1 1\n"
                           "2 1\n"
                           "3 1\n"
                           "1 2\n"
                           "4 2\n"s);
    std::ostringstream cout;
    std::string expected_cout("-1\n"
                              "3\n"
                              "2\n"
                              "3\n");
    Solution(cin, cout);
    const auto actual_cout = cout.str();
    assert(actual_cout == expected_cout);
  }

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
