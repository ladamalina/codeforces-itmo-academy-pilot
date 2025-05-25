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
class SegTree { // Художник
public:
  struct Node {
    int len = 0;
    T sum = 0;
    int cnt_b = 0;
    bool lb = false;
    bool rb = false;
    T set = NO_OP;
  };
  
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  void Modify(int l, int r, T v) {
    Modify(l, r, v, 0, 0, size_);
  }

  Node Get(int l, int r) {
    return Get(l, r, 0, 0, size_);
  }

private:
  std::vector<Node> t_;
  int size_ = 1;
  static const T NO_OP = std::numeric_limits<T>::min();

  static Node Combine(const Node& x, const Node& l, const Node& r) {
    if (x.set == 0) return {l.len+r.len, 0, 0, false, false, x.set};
    if (x.set == 1) return {l.len+r.len, l.len+r.len, 1, true, true, x.set};
    return { // NO_OP
      l.len + r.len,
      l.sum + r.sum,
      l.rb&&r.lb ? (l.cnt_b+r.cnt_b-1) : (l.cnt_b+r.cnt_b),
      l.lb,
      r.rb,
      x.set
    };
  }

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) {
        t_[x].len = 1;
      }
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = Combine(t_[x], t_[2*x+1], t_[2*x+2]);
    }
  }

  void Propagate(int x, int lx, int rx) {
    if (t_[x].set==NO_OP || lx+1 == rx) return;

    if (t_[x].set == 0) {
      t_[2*x+1] = {t_[2*x+1].len, 0, 0, false, false, t_[x].set};
      t_[2*x+2] = {t_[2*x+2].len, 0, 0, false, false, t_[x].set};
      t_[x] = {t_[x].len, 0, 0, false, false, NO_OP};
    }
    if (t_[x].set == 1) {
      t_[2*x+1] = {t_[2*x+1].len, t_[2*x+1].len, 1, true, true, t_[x].set};
      t_[2*x+2] = {t_[2*x+2].len, t_[2*x+2].len, 1, true, true, t_[x].set};
      t_[x] = {t_[x].len, t_[x].len, 1, true, true, NO_OP};
    }
  }

  void Modify(int l, int r, T v, int x, int lx, int rx) {
    Propagate(x, lx, rx);
    if (rx <= l || lx >= r) return;
    if (rx <= r && lx >= l) {
      if (v == 0) t_[x] = {t_[x].len, 0, 0, false, false, v};
      else t_[x] = {t_[x].len, t_[x].len, 1, true, true, v};
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

struct Query {
  char c=' ';
  int l=0, r=0;
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n; cin >> n;
  std::vector<Query> qs(n);
  int min_x=INT_MAX, max_r=INT_MIN;
  FOR(i, 0, n-1) {
    char c; int x, l;
    cin >> c >> x >> l;
    qs[i] = {c, x, x+l-1};
    min_x = std::min(min_x, x);
    max_r = std::max(max_r, x+l-1);
  }
  for (auto& q : qs) {
    q.l -= min_x;
    q.r -= min_x;
  }
  max_r -= min_x;
  
  SegTree tree(vi(max_r+1, 0));
  
  for (const auto& q : qs) {
    tree.Modify(q.l, q.r+1, q.c=='B');
    const auto res = tree.Get(0, max_r+1);
    cout << res.cnt_b << ' ' << res.sum << '\n';
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
