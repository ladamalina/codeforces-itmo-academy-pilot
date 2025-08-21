// #pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

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

template<typename T>
class SegTree { // Дерево отрезков на сумму
public:
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < SZ(a)) size_ <<= 1;
    t_.resize(size_ << 1);
    Init(a, 1, 0, size_);
  }

  T Sum(int l, int r) {
    return Sum(l, r, 1, 0, size_);
  }

  void Set(int i, T v) {
    Set(i, v, 1, 0, size_);
  }

private:
  std::vector<T> t_;
  int size_ = 1;

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < SZ(a)) t_[x] = a[lx];
    } else {
      const auto m = (lx + rx) >> 1;
      Init(a, (x<<1), lx, m);
      Init(a, (x<<1)|1, m, rx);
      t_[x] = t_[(x<<1)] + t_[(x<<1)|1];
    }
  }

  T Sum(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return 0;
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) >> 1;
    return Sum(l, r, (x<<1), lx, m) + Sum(l, r, (x<<1)|1, m, rx);
  }

  void Set(int i, T v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = v;
      return;
    }
    const auto m = (lx + rx) >> 1;
    if (i < m) Set(i, v, (x<<1), lx, m);
    else Set(i, v, (x<<1)|1, m, rx);
    t_[x] = t_[(x<<1)] + t_[(x<<1)|1];
  }
};

void Solution([[maybe_unused]] std::istream& cin, [[maybe_unused]] std::ostream& cout) {
  int n, m; cin >> n >> m;
  vl b(n);
  SegTree tree(b);
  FOR(j, 0, m-1) {
    int op; cin >> op;
    if (op == 1) {
      int l, r, v; cin >> l >> r >> v;
      b[l] += v;
      tree.Set(l, b[l]);
      if (r-1 < n-1) {
        b[r] -= v;
        tree.Set(r, b[r]);
      }
    } else {
      int i; cin >> i;
      cout << tree.Sum(0, i+1) << '\n';
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
#ifndef NDEBUG
  TestSolution();
#endif
  Solution(std::cin, std::cout);
  return 0;
}
