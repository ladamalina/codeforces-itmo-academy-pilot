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
class SegTree { // Прибавления арифметической последовательности на отрезках
public:
  struct Node {
    int cnt = 0;
    T a = 0;
    T d = 0;
  };
  
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < SZ(a)) size_ <<= 1;
    t_.resize(size_ << 1);
    Init(a, 1, 0, size_);
  }

  void Modify(int l, int r, T a, T d) {
    Modify(l, r, a, d, 1, 0, size_);
  }

  T Get(int i) {
    return Get(i, 1, 0, size_).a;
  }

private:
  std::vector<Node> t_;
  int size_ = 1;

  static Node Combine(const Node& x, const Node& l, const Node& r) {
    return {l.cnt + r.cnt, x.a, x.d};
  }

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < SZ(a)) {
        t_[x] = {1, a[lx], 0};
      }
    } else {
      const auto m = (lx + rx) >> 1;
      Init(a, (x<<1), lx, m);
      Init(a, (x<<1)|1, m, rx);
      t_[x] = Combine(t_[x], t_[(x<<1)], t_[(x<<1)|1]);
    }
  }

  void Propagate(int x, int lx, int rx) {
    if ((t_[x].a==0 && t_[x].d==0) || lx+1 == rx) return;

    t_[(x<<1)] = {t_[(x<<1)].cnt, t_[(x<<1)].a + t_[x].a, t_[(x<<1)].d + t_[x].d};
    const auto a2 = t_[x].a + t_[x].d*t_[(x<<1)].cnt;
    t_[(x<<1)|1] = {t_[(x<<1)|1].cnt, t_[(x<<1)|1].a + a2, t_[(x<<1)|1].d + t_[x].d};
    t_[x] = {t_[(x<<1)].cnt + t_[(x<<1)|1].cnt, 0, 0};
  }

  void Modify(int l, int r, T a, T d, int x, int lx, int rx) {
    Propagate(x, lx, rx);
    if (rx <= l || lx >= r) return;
    if (rx <= r && lx >= l) {
      t_[x] = {t_[x].cnt, t_[x].a + a + (lx-l)*d, t_[x].d + d};
      return;
    }
    const auto m = (lx + rx) >> 1;
    Modify(l, r, a, d, (x<<1), lx, m);
    Modify(l, r, a, d, (x<<1)|1, m, rx);
    t_[x] = Combine(t_[x], t_[(x<<1)], t_[(x<<1)|1]);
  }

  Node Get(int i, int x, int lx, int rx) {
    Propagate(x, lx, rx);
    if (lx + 1 == rx)
      return t_[x];
    const auto m = (lx + rx) >> 1;
    if (i < m)
      return Get(i, (x<<1), lx, m);
    return Get(i, (x<<1)|1, m, rx);
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, m; cin >> n >> m;
  SegTree tree(vl(n, 0));
  FOR(j, 0, m-1) {
    int op; cin >> op;
    if (op == 1) {
      int l, r, a, d; cin >> l >> r >> a >> d; --l; --r;
      tree.Modify(l, r+1, a, d);
    } else {
      int i; cin >> i; --i;
      cout << tree.Get(i) << '\n';
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
