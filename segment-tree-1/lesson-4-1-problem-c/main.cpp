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
class SegTree { // Число минимумов на отрезке
 public:
  using Node = std::pair<T, int>;

  explicit SegTree(const std::vector<T>& a)
      : INF(std::numeric_limits<T>::max()) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1, {INF, 0});
    Init(a, 0, 0, size_);
  }

  Node MinCount(int l, int r) {
    return MinCount(l, r, 0, 0, size_);
  }

  void Set(int i, T v) {
    Set(i, v, 0, 0, size_);
  }

 private:
  std::vector<Node> t_;
  int size_ = 1;
  const T INF;

  static Node Combine(const Node& a, const Node& b) {
    if (a.F < b.F) return a;
    if (a.F > b.F) return b;
    return {a.F, a.S + b.S};
  }

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) t_[x] = {a[lx], 1};
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
    }
  }

  [[nodiscard]] Node MinCount(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return {INF, 0};
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) / 2;
    return Combine(MinCount(l, r, 2*x+1, lx, m), MinCount(l, r, 2*x+2, m, rx));
  }

  void Set(int i, T v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = {v, 1};
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Set(i, v, 2*x+1, lx, m);
    else Set(i, v, 2*x+2, m, rx);
    t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, m; cin >> n >> m;
  vl a(n);
  FOR(i, 0, n-1) {
    cin >> a[i];
  }
  SegTree tree(a);
  FOR(j, 0, m-1) {
    int op; cin >> op;
    if (op == 1) {
      int i; ll v; cin >> i >> v;
      tree.Set(i, v);
    } else {
      int l, r; cin >> l >> r;
      const auto res = tree.MinCount(l, r);
      cout << res.F << ' ' << res.S << '\n';
    }
  }
}

[[maybe_unused]] void TestSolution() {
  std::istringstream cin("5 5\n"
                         "3 4 3 5 2\n"
                         "2 0 3\n"
                         "1 1 2\n"
                         "2 0 3\n"
                         "1 0 2\n"
                         "2 0 5"s);
  std::ostringstream cout;
  std::string expected_cout("3 2\n"
                            "2 1\n"
                            "2 3\n"s);
  Solution(cin, cout);
  const auto actual_cout = cout.str();
  assert(actual_cout == expected_cout);
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
// #ifndef NDEBUG
//   TestSolution();
// #endif
  Solution(std::cin, std::cout);
  return 0;
}
