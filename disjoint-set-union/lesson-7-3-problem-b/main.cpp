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

class DSU { // без эвристики сжатия путей, с ранговой эвристикой
public:
  explicit DSU(int n) : p_(vi(n)), r_(vi(n, 1)), cnt_(n) {
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Get(const int a) {
    if (a == p_[a]) return p_[a];
    // pp_.emplace(a, p_[a]);
    // return p_[a] = Get(p_[a]);
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
    pp_.push(SP);
    pr_.push(SP);
    pcnt_.push(ISP);
  }

  void Rollback() {
    while (!pp_.empty() && pp_.top() != SP) {
      const auto [i, v] = pp_.top();
      p_[i] = v;
      pp_.pop();
    }
    assert(!pp_.empty() && pp_.top() == SP);
    pp_.pop();

    while (!pr_.empty() && pr_.top() != SP) {
      const auto [i, v] = pr_.top();
      r_[i] = v;
      pr_.pop();
    }
    assert(!pr_.empty() && pr_.top() == SP);
    pr_.pop();

    while (!pcnt_.empty() && pcnt_.top() != ISP) {
      cnt_ = pcnt_.top();
      pcnt_.pop();
    }
    assert(!pcnt_.empty() && pcnt_.top() == ISP);
    pcnt_.pop();
  }

  [[nodiscard]] int Count() const { return cnt_; }

private:
  vi p_, r_;
  int cnt_;
  std::stack<ii> pp_{}, pr_{}; // <id, prev_val>
  std::stack<int> pcnt_{}; // <prev_val>
  const ii SP = {-1, -1};
  const int ISP = -1;
};

void Solution([[maybe_unused]] std::istream& cin, [[maybe_unused]] std::ostream& cout) {
  int n, en; cin >> n >> en;

  vii es(en);
  FOR(i, 0, en-1) {
    cin >> es[i].F >> es[i].S; --es[i].F; --es[i].S;
  }

  int qn; cin >> qn;
  std::vector<std::pair<ii, int>> qs(qn);
  FOR(i, 0, qn-1) {
    auto& [l, r] = qs[i].F;
    cin >> l >> r; --l; --r;
    qs[i].S = i;
  }

  const auto k = std::max(CI(std::sqrt(en)), 1);
  std::sort(RNG(qs), [&](const std::pair<ii, int>& a, const std::pair<ii, int>& b) {
    return std::make_tuple(a.F.F / k, a.F.S, a.S) < std::make_tuple(b.F.F / k, b.F.S, b.S);
  });

  vi res(qn);
  DSU dsu(n);
  dsu.Persist();
  bool next_k = true;

  FOR(i, 0, qn-1) {
    const auto [l, r] = qs[i].F;
    const auto qi = qs[i].S;

    const auto lk = l / k, rk = r / k;
    if (lk == rk) {
      DSU dsu_sm(n);
      FOR(ei, l, r) dsu_sm.Union(es[ei].F, es[ei].S);
      res[qi] = dsu_sm.Count();
      continue;
    }

    if (next_k) {
      dsu.Rollback();
      dsu.Persist();
      next_k = false;

      FOR(ei, (lk+1)*k, r) dsu.Union(es[ei].F, es[ei].S);
      dsu.Persist();
    } else {
      FOR(ei, qs[i-1].F.S+1, r) dsu.Union(es[ei].F, es[ei].S);
      dsu.Persist();
    }

    FOR(ei, l, (lk+1)*k-1) dsu.Union(es[ei].F, es[ei].S);
    res[qi] = dsu.Count();
    dsu.Rollback();

    if (i+1 < qn && lk != qs[i+1].F.F / k) next_k = true;
  }

  FOR(i, 0, qn-1) cout << res[i] << '\n';
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

[[maybe_unused]] void RunTest(const std::string& in_path, const std::string& out_path) {
  std::stringstream cin = ReadFile(in_path);
  std::stringstream cout;
  const auto e_out = ReadFile(out_path).str();
  const auto start_t = std::chrono::high_resolution_clock::now();
  Solution(cin, cout);
  const auto end_t = std::chrono::high_resolution_clock::now();
  const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
  std::cerr << in_path << ", "sv << total_t << " ms"sv << std::endl;
  const auto a_out = cout.str();
  assert(a_out == e_out);
}

[[maybe_unused]] void TestSolution() {
  const std::string dir("../"s);
  RunTest(dir + "input1.txt"s, dir + "output1.txt"s);
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