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

class DSU {
public:
  explicit DSU(const int n) : p_(vi(n)), r_(vi(n, 1)), d_(vi(n)) {
    std::iota(RNG(p_), 0);
  }

  ii Get(const int a) {
    if (p_[a] == a)
      return {p_[a], d_[a]};
    const auto p_res = Get(p_[a]);
    p_[a] = p_res.F;
    d_[a] = (d_[a] + p_res.S) & 1;
    return {p_[a], d_[a]};
  }

  void Union(int a, int b) {
    const auto a_res = Get(a), b_res = Get(b);
    a = a_res.F, b = b_res.F;
    if (a == b) return;
    if (r_[a] == r_[b]) ++r_[a];
    if (r_[a] > r_[b]) {
      p_[b] = a;
      d_[b] = (a_res.S + b_res.S + 1) & 1;
    } else {
      p_[a] = b;
      d_[a] = (a_res.S + b_res.S + 1) & 1;
    }
  }

private:
  vi p_, r_, d_;
};

void Solution([[maybe_unused]] std::istream& cin, [[maybe_unused]] std::ostream& cout) {
  int n, m; cin >> n >> m;
  DSU dsu(n+1);

  FOR(i, 1, m) {
    int a, b; cin >> a >> b;
    const auto a_res = dsu.Get(a), b_res = dsu.Get(b);
    if (a_res.F == b_res.F) {
      if (a_res.S == b_res.S) {
        cout << i << '\n';
        return;
      }
    } else {
      dsu.Union(a, b);
    }
  }
  cout << -1 << '\n';
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