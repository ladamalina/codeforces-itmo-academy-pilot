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

class SegTree { // K-я единица с конца
public:
  struct Node { int sum = 0; };

  explicit SegTree(const std::vector<int>& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_ = std::vector<Node>(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  int GetNthIdx(int i) {
    return GetNthIdx(i+1, 0, 0, size_);
  }

  void Invert(int i) {
    Invert(i, 0, 0, size_);
  }

private:
  std::vector<Node> t_;
  int size_ = 1;

  static Node Combine(const Node& a, const Node& b) {
    return {a.sum + b.sum};
  }

  void Init(const std::vector<int>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) t_[x] = {a[lx]};
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
    }
  }

  int GetNthIdx(int i, int x, int lx, int rx) {
    if (lx + 1 == rx) return lx;
    const auto m = (lx + rx) / 2;
    if (t_[2*x+2].sum >= i)
      return GetNthIdx(i, 2*x+2, m, rx);
    return GetNthIdx(i - t_[2*x+2].sum, 2*x+1, lx, m);
  }

  void Invert(int i, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = {1 - t_[x].sum};
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Invert(i, 2*x+1, lx, m);
    else Invert(i, 2*x+2, m, rx);
    t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
  }
};

void Solution([[maybe_unused]] std::istream& cin, [[maybe_unused]] std::ostream& cout) {
  int n; cin >> n;
  vi a(n);
  FOR(i, 0, n-1) cin >> a[i];
  SegTree tree(vi(a.size(), 1));
  vi b(n);
  FORD(i, n-1, 0) {
    const auto ti = tree.GetNthIdx(a[i]);
    b[i] = ti+1;
    tree.Invert(ti);
  }
  for (const auto x : b) cout << x << ' ';
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
