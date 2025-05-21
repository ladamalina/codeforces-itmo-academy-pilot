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

using Freq = std::array<ll, 41>;

class SegTree { // Число инверсий на отрезке
public:
  struct Node {
    ll inv=0;
    Freq f{};
  };
  
  explicit SegTree(const vi& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  ll GetInvs(int l, int r) {
    return GetInvs(l, r, 0, 0, size_).inv;
  }

  void Set(int i, int v) {
    Set(i, v, 0, 0, size_);
  }

private:
  std::vector<Node> t_;
  int size_ = 1;

  static void InitOne(Node& node, int v) {
    node = {};
    node.f[v] = 1;
  }

  static Node Combine(const Node& a, const Node& b) {
    Node res{a.inv + b.inv};
    FOR(i, 1, 40) res.f[i] = a.f[i] + b.f[i];
    FOR(ai, 2, 40) {
      FOR(bi, 1, ai-1) {
        res.inv += a.f[ai]*b.f[bi];
      }
    }
    return res;
  }

  void Init(const vi& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) InitOne(t_[x], a[lx]);
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
    }
  }

  Node GetInvs(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return {};
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) / 2;
    return Combine(GetInvs(l, r, 2*x+1, lx, m), GetInvs(l, r, 2*x+2, m, rx));
  }

  void Set(int i, int v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      InitOne(t_[x], v);
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Set(i, v, 2*x+1, lx, m);
    else Set(i, v, 2*x+2, m, rx);
    t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
  }
};

void Solution([[maybe_unused]] std::istream& cin, [[maybe_unused]] std::ostream& cout) {
  int n, q; cin >> n >> q;
  vi a(n);
  FOR(i, 0, n-1) {
    cin >> a[i];
  }
  SegTree tree(a);
  FOR(j, 0, q-1) {
    int op; cin >> op;
    if (op == 1) {
      int l, r; cin >> l >> r; --l; --r;
      cout << tree.GetInvs(l, r+1) << '\n';
    } else {
      int i, v; cin >> i >> v; --i;
      tree.Set(i, v);
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
