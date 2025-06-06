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
class SegTree { // Присваивание, прибавление и сумма
public:
  struct Node {
    int cnt = 0;
    T sum = 0;
    T set = NO_OP;
    T add = 0;
  };
  
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  void ModifySet(int l, int r, T v) {
    ModifySet(l, r, v, 0, 0, size_);
  }

  void ModifyAdd(int l, int r, T v) {
    ModifyAdd(l, r, v, 0, 0, size_);
  }

  T Get(int l, int r) {
    return Get(l, r, 0, 0, size_).sum;
  }

private:
  std::vector<Node> t_;
  int size_ = 1;
  static const T NO_OP = std::numeric_limits<int>::min();

  static Node Combine(const Node& x, const Node& l, const Node& r) {
    Node m{l.cnt + r.cnt, l.sum + r.sum, x.set, x.add};
    if (m.set != NO_OP) m.sum = m.cnt * m.set;
    m.sum += m.cnt * m.add;
    return m;
  }

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) {
        t_[x] = {1, a[lx], NO_OP, 0};
      }
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = Combine(t_[x], t_[2*x+1], t_[2*x+2]);
    }
  }

  void Propagate(int x, int lx, int rx) {
    if ((t_[x].set==NO_OP && t_[x].add==0) || lx+1 == rx) return;
    
    if (t_[x].set != NO_OP) {
      t_[2*x+1] = {t_[2*x+1].cnt, t_[2*x+1].cnt*t_[x].set, t_[x].set, 0};
      t_[2*x+2] = {t_[2*x+2].cnt, t_[2*x+2].cnt*t_[x].set, t_[x].set, 0};
    }
    if (t_[x].add != 0) {
      t_[2*x+1] = {t_[2*x+1].cnt, t_[2*x+1].sum + t_[2*x+1].cnt*t_[x].add, t_[2*x+1].set, t_[2*x+1].add+t_[x].add};
      t_[2*x+2] = {t_[2*x+2].cnt, t_[2*x+2].sum + t_[2*x+2].cnt*t_[x].add, t_[2*x+2].set, t_[2*x+2].add+t_[x].add};
    }
    
    t_[x] = {t_[2*x+1].cnt+t_[2*x+2].cnt, t_[2*x+1].sum+t_[2*x+2].sum, NO_OP, 0};
  }

  void ModifySet(int l, int r, T v, int x, int lx, int rx) {
    Propagate(x, lx, rx);
    if (rx <= l || lx >= r) return;
    if (rx <= r && lx >= l) {
      t_[x] = {t_[x].cnt, t_[x].cnt*v, v, 0};
      return;
    }
    const auto m = (lx + rx) / 2;
    ModifySet(l, r, v, 2*x+1, lx, m);
    ModifySet(l, r, v, 2*x+2, m, rx);
    t_[x] = Combine(t_[x], t_[2*x+1], t_[2*x+2]);
  }

  void ModifyAdd(int l, int r, T v, int x, int lx, int rx) {
    Propagate(x, lx, rx);
    if (rx <= l || lx >= r) return;
    if (rx <= r && lx >= l) {
      t_[x] = {t_[x].cnt, t_[x].sum + t_[x].cnt*v, t_[x].set, t_[x].add+v};
      return;
    }
    const auto m = (lx + rx) / 2;
    ModifyAdd(l, r, v, 2*x+1, lx, m);
    ModifyAdd(l, r, v, 2*x+2, m, rx);
    t_[x] = Combine(t_[x], t_[2*x+1], t_[2*x+2]);
  }

  Node Get(int l, int r, int x, int lx, int rx) {
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
  SegTree tree(vl(n, 0));
  FOR(j, 0, m-1) {
    int op; cin >> op;
    if (op == 1) {
      int l, r, v; cin >> l >> r >> v;
      tree.ModifySet(l, r, v);
    } else if (op == 2) {
      int l, r, v; cin >> l >> r >> v;
      tree.ModifyAdd(l, r, v);
    } else {
      int l, r; cin >> l >> r;
      cout << tree.Get(l, r) << '\n';
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
