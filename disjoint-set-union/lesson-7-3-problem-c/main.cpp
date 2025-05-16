// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numbers>
#include <numeric>
#include <optional>
#include <random>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

class PersistentDSU {
public:
  explicit PersistentDSU(const int n) : p_(vi(n)), r_(vi(n, 1)), cnt_(n) {
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Get(const int a) {
    if (a == p_[a]) return p_[a];
    /*const auto upd_p = Get(p_[a]);
    pp_.emplace(a, p_[a]);
    return p_[a] = upd_p;*/
    return Get(p_[a]);
  }

  void Union(int a, int b) {
    a = Get(a), b = Get(b);
    if (a == b) return;
    if (r_[a] == r_[b]) {
      pr_.emplace(a, r_[a]);
      ++r_[a];
    }
    if (r_[a] > r_[b]) {
      pp_.emplace(b, p_[b]);
      p_[b] = a;
    } else {
      pp_.emplace(a, p_[a]);
      p_[a] = b;
    }
    pcnt_.emplace(cnt_);
    --cnt_;
  }

  void Persist() {
    pp_.emplace(SP, SP);
    pr_.emplace(SP, SP);
    pcnt_.push(SP);
  }

  void Rollback() {
    while (!pp_.empty()) {
      const auto [i, v] = pp_.top();
      pp_.pop();
      if (i == SP) break;
      p_[i] = v;
    }
    while (!pr_.empty()) {
      const auto [i, v] = pr_.top();
      pr_.pop();
      if (i == SP) break;
      r_[i] = v;
    }
    while (!pcnt_.empty()) {
      const auto v = pcnt_.top();
      pcnt_.pop();
      if (v == SP) break;
      cnt_ = v;
    }
  }

  [[nodiscard]] int Count() const { return cnt_; }

private:
  vi p_, r_;
  int cnt_ = 0;
  std::stack<ii> pp_{}, pr_{}; // <id, prev_val>
  std::stack<int> pcnt_{}; // <prev_val>
  const int SP = -1;
};

struct Query {
  int l = 0, r = 0, u = 0, v = 0;
};

void Solution([[maybe_unused]] std::istream& cin, [[maybe_unused]] std::ostream& cout) {
  int n, m; cin >> n >> m;

  vi get_queries;
  std::vector<Query> edge_queries;
  std::map<ii, int> edge_add_qi;
  FOR(qi, 0, m-1) {
    char op; cin >> op;
    if (op == '+') {
      int u, v; cin >> u >> v; --u; --v;
      if (u > v) std::swap(u, v);
      edge_add_qi[{u, v}] = qi;
    } else if (op == '-') {
      int u, v; cin >> u >> v; --u; --v;
      if (u > v) std::swap(u, v);
      const auto it = edge_add_qi.find({u, v});
      edge_queries.emplace_back(it->S, qi, u, v);
      edge_add_qi.erase(it);
    } else if (op == '?') {
      get_queries.push_back(qi);
    }
  }
  for (const auto& [edge, add_qi] : edge_add_qi) {
    const auto [u, v] = edge;
    edge_queries.emplace_back(add_qi, m, u, v);
  }

  PersistentDSU dsu(n);
  vi res(m);

  const std::function<void(int,int,const std::vector<Query>&)> rec = [&](int l, int r, const std::vector<Query>& queries) {
    if (l >= r) return;
    if (l + 1 == r) {
      dsu.Persist();
      for (const auto& q : queries) {
        if (q.l <= l && r <= q.r)
          dsu.Union(q.u, q.v);
      }
      res[l] = dsu.Count();
      dsu.Rollback();
      return;
    }
    dsu.Persist();
    std::vector<Query> queries2;
    for (const auto& q : queries) {
      if (q.l <= l && r <= q.r) {
        dsu.Union(q.u, q.v);
      } else if ((l <= q.l && q.l < r) || (l < q.r && q.r <= r)) {
        queries2.push_back(q);
      }
    }
    const auto mid = (l + r + 1) / 2;
    rec(l, mid, queries2);
    rec(mid, r, queries2);
    dsu.Rollback();
  };

  if (m > 0)
    rec(0, m, edge_queries);
  for (const auto x : get_queries)
    cout << res[x] << '\n';
}

#ifndef NDEBUG
[[maybe_unused]] std::stringstream ReadFile(const std::string& path) {
  std::ifstream file(path);
  assert(file);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  return ss;
}

[[maybe_unused]] void RunTest(const std::string& in_path, const std::string& out_path, const bool compare = true) {
  std::stringstream cin = ReadFile(in_path);
  std::stringstream cout;
  const auto start_t = std::chrono::high_resolution_clock::now();
  Solution(cin, cout);
  const auto end_t = std::chrono::high_resolution_clock::now();
  const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
  std::cerr << in_path << ", "sv << total_t << " ms"sv << std::endl;
  const auto a_out = cout.str();
  if (compare) {
    const auto e_out = ReadFile(out_path).str();
    assert(a_out == e_out);
  }
}

[[maybe_unused]] void TestSolution() {
  const std::string dir("../"s);
  RunTest(dir + "input1.txt"s, dir + "output1.txt"s);
  RunTest(dir + "input_300K.txt"s, ""s, false);
  std::cerr << "TestSolution OK"sv << std::endl;
}
#endif

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  // #ifndef NDEBUG
  //   TestSolution();
  // #endif
  Solution(std::cin, std::cout);
  return 0;
}