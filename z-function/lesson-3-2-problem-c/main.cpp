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
using vc [[maybe_unused]] = std::vector<char>;

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

void Solution([[maybe_unused]] std::istream& cin, [[maybe_unused]] std::ostream& cout) {
  std::string chars;
  for (auto c = 'a'; c <= 'z'; ++c) chars.push_back(c);
  for (auto c = 'A'; c <= 'Z'; ++c) chars.push_back(c);

  int tn; cin >> tn;
  FOR(ti, 1, tn) {
    int n; cin >> n;
    vi z(n);
    FOR(i, 0, n-1) cin >> z[i];
    if (z[0] != 0) {
      cout << "!\n";
      continue;
    }
    vvi eq(n, vi(n, -1));
    bool possible = true;
    FOR(i, 1, n-1) {
      int j = 0;
      for (; j < z[i]; ++j) {
        if (i+j >= n) {
          possible = false;
          break;
        }
        if (eq[i+j][j] == -1) eq[i+j][j] = 1;
        else if (eq[i+j][j] == 0) possible = false;
      }
      if (i+j < n) {
        if (eq[i+j][j] == -1) eq[i+j][j] = 0;
        else if (eq[i+j][j] == 1) possible = false;
      }
    }
    if (!possible) {
      cout << "!\n";
      continue;
    }

    std::string s(n, '\0');
    FOR(i, 0, n-1) {
      FOR(j, 0, n-1) { // EQ
        if (eq[i][j] == 1) {
          if (s[i] == '\0') s[i] = s[j];
          else if (s[i] != s[j]) possible = false;
        }
      }
      if (s[i] != '\0') {
        FOR(j, 0, n-1) { // NOT EQ
          if (eq[i][j] == 0) {
            if (s[i] == s[j]) possible = false;
          }
        }
      } else {
        for (const auto c : chars) {
          bool avail = true;
          FOR(j, 0, n-1) {
            if (eq[i][j] == 0 && s[j] == c) avail = false;
          }
          if (avail) {
            s[i] = c;
            break;
          }
        }
        if (s[i] == '\0') possible = false;
      }
    }

    if (!possible) {
      cout << "!\n";
      continue;
    }
    cout << s << '\n';
  }
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
