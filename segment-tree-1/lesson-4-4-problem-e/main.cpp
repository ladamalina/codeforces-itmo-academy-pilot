// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second
#define PB push_back

class SegTree { // Землетрясения
public:
  explicit SegTree(int n) {
    while (size_ < n) size_ *= 2;
    t_ = vi(size_ * 2 - 1, INT_MAX);
  }

  int Process(int l, int r, int p) {
    return Process(l, r, 0, 0, size_, p);
  }

  void Set(int i, int v) {
    Set(i, v, 0, 0, size_);
  }

private:
  vi t_;
  int size_ = 1;

  int Process(int l, int r, int x, int lx, int rx, int p) {
    if (rx <= l || lx >= r) return 0;
    if (t_[x] > p) return 0;
    if (lx + 1 == rx) {
      t_[x] = INT_MAX;
      return 1;
    }
    const auto m = (lx + rx) / 2;
    const auto res = Process(l, r, 2*x+1, lx, m, p) + Process(l, r, 2*x+2, m, rx, p);
    t_[x] = std::min(t_[2*x+1], t_[2*x+2]);
    return res;
  }

  void Set(int i, int v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = v;
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Set(i, v, 2*x+1, lx, m);
    else Set(i, v, 2*x+2, m, rx);
    t_[x] = std::min(t_[2*x+1], t_[2*x+2]);
  }
};

void Solution([[maybe_unused]] std::istream& cin, [[maybe_unused]] std::ostream& cout) {
  int n, m; cin >> n >> m;
  SegTree tree(n);
  FOR(i, 0, m-1) {
    int op; cin >> op;
    if (op == 1) {
      int i, h; cin >> i >> h;
      tree.Set(i, h);
    } else {
      int l, r, p; cin >> l >> r >> p;
      cout << tree.Process(l, r, p) << '\n';
    }
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
