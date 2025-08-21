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

using Mt = std::array<ll, 4>;

class SegTree { // Умножение матриц
public:
  struct Node {
    Mt mt{1,0,0,1};
  };
  
  explicit SegTree(const std::vector<Mt>& a, ll mod) : mod_(mod) {
    while (size_ < SZ(a)) size_ <<= 1;
    t_.resize(size_ << 1);
    Init(a, 1, 0, size_);
  }

  Mt Mult(int l, int r) {
    return Mult(l, r, 1, 0, size_).mt;
  }

  void Set(int i, const Mt& v) {
    Set(i, v, 1, 0, size_);
  }

private:
  std::vector<Node> t_;
  int size_ = 1;
  ll mod_ = 1;

  Node Combine(const Node& a, const Node& b) {
    return {{
      (a.mt[0]*b.mt[0] + a.mt[1]*b.mt[2]) % mod_,
      (a.mt[0]*b.mt[1] + a.mt[1]*b.mt[3]) % mod_,
      (a.mt[2]*b.mt[0] + a.mt[3]*b.mt[2]) % mod_,
      (a.mt[2]*b.mt[1] + a.mt[3]*b.mt[3]) % mod_,
    }};
  }

  void Init(const std::vector<Mt>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < SZ(a)) t_[x] = {a[lx]};
    } else {
      const auto m = (lx + rx) >> 1;
      Init(a, (x<<1), lx, m);
      Init(a, (x<<1)|1, m, rx);
      t_[x] = Combine(t_[(x<<1)], t_[(x<<1)|1]);
    }
  }

  Node Mult(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return {};
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) >> 1;
    return Combine(Mult(l, r, (x<<1), lx, m), Mult(l, r, (x<<1)|1, m, rx));
  }

  void Set(int i, const Mt& v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = {v};
      return;
    }
    const auto m = (lx + rx) >> 1;
    if (i < m) Set(i, v, (x<<1), lx, m);
    else Set(i, v, (x<<1)|1, m, rx);
    t_[x] = Combine(t_[(x<<1)], t_[(x<<1)|1]);
  }
};

void Solution([[maybe_unused]] std::istream& cin, [[maybe_unused]] std::ostream& cout) {
  int r, n, m; cin >> r >> n >> m;
  std::vector<Mt> a(n);
  FOR(i, 0, n-1) {
    cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
  }
  SegTree tree(a, r);
  FOR(j, 0, m-1) {
    int l, r; cin >> l >> r; --l; --r;
    const auto res = tree.Mult(l, r+1);
    cout << res[0] << ' ' << res[1] << '\n';
    cout << res[2] << ' ' << res[3] << '\n';
    cout << '\n';
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
