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
  vi p_, r_;

  explicit DSU(const int n) : p_(vi(n)), r_(vi(n, 1)) {
    std::iota(RNG(p_), 0);
  }

  int Get(const int a) {
    return p_[a] = (a == p_[a] ? a : Get(p_[a]));
  }

  void Union(int a, int b) {
    a = Get(a), b = Get(b);
    if (a == b) return;
    if (r_[a] == r_[b]) ++r_[a];
    if (r_[a] > r_[b]) p_[b] = a;
    else p_[a] = b;
  }
};

struct Edge {
  int v = 0, u = 0, w = 0, i = 0;
  bool operator<(const Edge& o) const { return std::tie(w, i) < std::tie(o.w, o.i); }
  bool operator>(const Edge& o) const { return std::tie(w, i) > std::tie(o.w, o.i); }
};

void Solution([[maybe_unused]] std::istream& cin, [[maybe_unused]] std::ostream& cout) {
  int n, m; cin >> n >> m;
  ll s; cin >> s;
  std::vector<Edge> edges(m);
  FOR(i, 0, m-1) {
    cin >> edges[i].v >> edges[i].u >> edges[i].w;
    edges[i].i = i + 1;
  }
  std::sort(edges.rbegin(), edges.rend());
  DSU dsu(n + 1);
  std::priority_queue<Edge, std::vector<Edge>, std::greater<>> pq;
  FOR(i, 0, m-1) {
    if (dsu.Get(edges[i].v) == dsu.Get(edges[i].u)) {
      pq.push(edges[i]);
    } else {
      dsu.Union(edges[i].v, edges[i].u);
    }
  }
  ll res_sum = 0;
  vi res_vs;
  while (!pq.empty() && res_sum + pq.top().w <= s) {
    res_sum += pq.top().w;
    res_vs.push_back(pq.top().i);
    pq.pop();
  }
  cout << SZ(res_vs) << '\n';
  FOR(i, 0, SZ(res_vs)-1) cout << res_vs[i] << ' ';
  cout << '\n';
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