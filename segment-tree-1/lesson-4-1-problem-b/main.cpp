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
class SegTree { // Дерево отрезков на минимум
 public:
  explicit SegTree(const std::vector<T>& a)
      : INF(std::numeric_limits<T>::max()) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1, INF);
    Init(a, 0, 0, size_);
  }

  T GetMin(int l, int r) {
    return GetMin(l, r, 0, 0, size_);
  }

  void Set(int i, T v) {
    Set(i, v, 0, 0, size_);
  }

 private:
  std::vector<T> t_;
  int size_ = 1;
  const T INF;

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) t_[x] = a[lx];
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = std::min(t_[2*x+1], t_[2*x+2]);
    }
  }

  T GetMin(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return INF;
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) / 2;
    return std::min(GetMin(l, r, 2*x+1, lx, m), GetMin(l, r, 2*x+2, m, rx));
  }

  void Set(int i, T v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = v;
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Set(i, v, 2*x+1, lx, m);
    else Set(i, v, 2*x+2, m, rx);
    t_[x] = std::min(t_[2*x+1], t_[2*x+2]);
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
      cout << tree.GetMin(l, r) << '\n';
    }
  }
}

[[maybe_unused]] void TestSolution() {
  std::istringstream cin("5 5\n"
                         "5 4 2 3 5\n"
                         "2 0 3\n"
                         "1 2 6\n"
                         "2 0 3\n"
                         "1 3 1\n"
                         "2 0 5"s);
  std::ostringstream cout;
  std::string expected_cout("2\n"
                            "4\n"
                            "1\n"s);
  Solution(cin, cout);
  const auto actual_cout = cout.str();
  assert(actual_cout == expected_cout);
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
#ifndef NDEBUG
  TestSolution();
#endif
  Solution(std::cin, std::cout);
  return 0;
}
