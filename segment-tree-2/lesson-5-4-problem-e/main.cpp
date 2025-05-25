#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

constexpr int MAX_H = 1e5;

template<typename T>
class SegTree { // Стена
public:
  struct Node {
    T mn = 0;
    T mx = MAX_H;
  };
  
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  void Inc(int l, int r, T v) {
    Modify(l, r, v, MAX_H, 0, 0, size_);
  }

  void Dec(int l, int r, T v) {
    Modify(l, r, 0, v, 0, 0, size_);
  }

  void Modify(int l, int r, T mn, T mx) {
    Modify(l, r, mn, mx, 0, 0, size_);
  }

  T Get(int i) {
    return Get(i, 0, 0, size_).mn;
  }

private:
  std::vector<Node> t_;
  int size_ = 1;

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) {
        t_[x] = {a[lx], a[lx]};
      }
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      // t_[x] = Combine(t_[x], t_[2*x+1], t_[2*x+2]);
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

    t_[2*x+1] = Apply(t_[2*x+1], t_[x].mn, t_[x].mx);
    t_[2*x+2] = Apply(t_[2*x+2], t_[x].mn, t_[x].mx);

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
    const auto m = (lx + rx) / 2;
    Modify(l, r, mn, mx, 2*x+1, lx, m);
    Modify(l, r, mn, mx, 2*x+2, m, rx);
    // t_[x] = Combine(t_[x], t_[2*x+1], t_[2*x+2]);
  }

  Node Get(int i, int x, int lx, int rx) {
    Propagate(x, lx, rx);
    if (lx + 1 == rx)
      return t_[x];
    const auto m = (lx + rx) / 2;
    if (i < m) {
      const auto l_res = Get(i, 2*x+1, lx, m);
      return Apply(l_res, t_[x].mn, t_[x].mx);
    }
    const auto r_res = Get(i, 2*x+2, m, rx);
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
// #ifndef NDEBUG
//   TestSolution();
// #endif
  Solution(std::cin, std::cout);
  return 0;
}
