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

template<typename T>
class SegTree { // Запросы о взвешенной сумме
public:
  struct Node {
    int len = 0;
    T sum = 0;
    T add = 0;
    T res = 0;
  };
  
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  void Modify(int l, int r, T v) {
    Modify(l, r, v, 0, 0, size_);
  }

  T Get(int l, int r) {
    return Get(l, r, 0, 0, size_).res;
  }

private:
  std::vector<Node> t_;
  int size_ = 1;

  static Node Combine(const Node& x, const Node& l, const Node& r) {
    Node node{
      l.len + r.len,
      l.sum + r.sum,
      x.add,
      l.res + r.res + r.sum*l.len
    };
    if (x.add) {
      node.sum += x.add * node.len;
      node.res += x.add * CL(1+node.len)*node.len/2;
    }
    return node;
  }

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) {
        t_[x] = {1, a[lx], 0, a[lx]};
      }
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = Combine(t_[x], t_[2*x+1], t_[2*x+2]);
    }
  }

  void Propagate(int x, int lx, int rx) {
    if (t_[x].add==0 || lx+1 == rx) return;

    auto& tx = t_[x];

    auto& l = t_[2*x+1];
    l.add += tx.add;
    l.sum += tx.add * l.len;
    l.res += tx.add * CL(1+l.len)*l.len/2;

    auto& r = t_[2*x+2];
    r.add += tx.add;
    r.sum += tx.add * r.len;
    r.res += tx.add * CL(1+r.len)*r.len/2;

    tx.add = 0;
  }

  void Modify(int l, int r, T v, int x, int lx, int rx) {
    Propagate(x, lx, rx);
    if (rx <= l || lx >= r) return;
    if (rx <= r && lx >= l) {
      auto& tx = t_[x];
      tx.add += v;
      tx.sum += v * tx.len;
      tx.res += v * CL(1+tx.len)*tx.len/2;
      return;
    }
    const auto m = (lx + rx) / 2;
    Modify(l, r, v, 2*x+1, lx, m);
    Modify(l, r, v, 2*x+2, m, rx);
    t_[x] = Combine(t_[x], t_[2*x+1], t_[2*x+2]);
  }

  Node Get(int l, int r, int x, int lx, int rx) {
    Propagate(x, lx, rx);
    if (rx <= l || lx >= r) return {};
    if (rx <= r && lx >= l) {
      return t_[x];
    }
    const auto m = (lx + rx) / 2;
    const auto m1 = Get(l, r, 2*x+1, lx, m);
    const auto m2 = Get(l, r, 2*x+2, m, rx);
    return Combine(t_[x], m1, m2);
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, m; cin >> n >> m;
  vl a(n);
  FOR(i, 0, n-1) cin >> a[i];
  SegTree tree(a);

  FOR(i, 0, m-1) {
    int op; cin >> op;
    if (op == 1) {
      int l, r, d; cin >> l >> r >> d;
      --l; --r;
      tree.Modify(l, r+1, d);
    } else {
      int l, r; cin >> l >> r;
      --l; --r;
      cout << tree.Get(l, r+1) << '\n';
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
