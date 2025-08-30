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

constexpr int MAX_H = 1e5;

template<typename T>
class SegTree { // Стена
public:
  struct Node {
    T mn = 0;
    T mx = MAX_H;
  };
  
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < SZ(a)) size_ <<= 1;
    t_.resize(size_ << 1);
    Init(a, 0, 0, size_);
  }

  void Inc(int l, int r, T v) {
    Modify(l, r, v, MAX_H, 1, 0, size_);
  }

  void Dec(int l, int r, T v) {
    Modify(l, r, 0, v, 1, 0, size_);
  }

  void Modify(int l, int r, T mn, T mx) {
    Modify(l, r, mn, mx, 1, 0, size_);
  }

  T Get(int i) {
    return Get(i, 1, 0, size_).mn;
  }

private:
  std::vector<Node> t_;
  int size_ = 1;

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < SZ(a)) {
        t_[x] = {a[lx], a[lx]};
      }
    } else {
      const auto m = (lx + rx) >> 1;
      Init(a, (x<<1), lx, m);
      Init(a, (x<<1)|1, m, rx);
      // t_[x] = Combine(t_[x], t_[(x<<1)], t_[(x<<1)|1]);
    }
  }

  Node Apply(const Node& x, T mn, T mx) {
    auto node = x;
    if (node.mx <= mn) {
      node.mn = mn;
      node.mx = mn;
    } else if (node.mn >= mx) {
      node.mn = mx;
      node.mx = mx;
    } else {
      node.mn = std::max(node.mn, mn);
      node.mx = std::min(node.mx, mx);
    }
    return node;
  }
  
  void Propagate(int x, int lx, int rx) {
    if ((t_[x].mn==0 && t_[x].mx==MAX_H) || lx+1 == rx) return;

    t_[(x<<1)] = Apply(t_[(x<<1)], t_[x].mn, t_[x].mx);
    t_[(x<<1)|1] = Apply(t_[(x<<1)|1], t_[x].mn, t_[x].mx);

    t_[x].mn = 0;
    t_[x].mx = MAX_H;
  }

  void Modify(int l, int r, T mn, T mx, int x, int lx, int rx) {
    Propagate(x, lx, rx);
    if (rx <= l || lx >= r) return;
    if (rx <= r && lx >= l) {
      t_[x] = Apply(t_[x], mn, mx);
      return;
    }
    const auto m = (lx + rx) >> 1;
    Modify(l, r, mn, mx, (x<<1), lx, m);
    Modify(l, r, mn, mx, (x<<1)|1, m, rx);
    // t_[x] = Combine(t_[x], t_[(x<<1)], t_[(x<<1)|1]);
  }

  Node Get(int i, int x, int lx, int rx) {
    Propagate(x, lx, rx);
    if (lx + 1 == rx)
      return t_[x];
    const auto m = (lx + rx) >> 1;
    if (i < m) {
      const auto l_res = Get(i, (x<<1), lx, m);
      return Apply(l_res, t_[x].mn, t_[x].mx);
    }
    const auto r_res = Get(i, (x<<1)|1, m, rx);
    return Apply(r_res, t_[x].mn, t_[x].mx);
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, k; cin >> n >> k;
  vi a(n);
  SegTree tree(a);

  FOR(i, 0, k-1) {
    int op; cin >> op;
    if (op == 1) {
      int l, r, h; cin >> l >> r >> h;
      tree.Inc(l, r+1, h);
    } else {
      int l, r, h; cin >> l >> r >> h;
      tree.Dec(l, r+1, h);
    }
  }

  FOR(i, 0, n-1) {
    cout << tree.Get(i) << '\n';
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
