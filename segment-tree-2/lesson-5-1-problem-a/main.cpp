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
class SegTree { // Прибавление к отрезку
 public:
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  void Modify(int l, int r, T v) {
    Modify(l, r, v, 0, 0, size_);
  }

  T Get(int i) {
    return Get(i, 0, 0, size_);
  }

 private:
  std::vector<T> t_;
  int size_ = 1;

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) t_[x] = a[lx];
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = 0;
    }
  }

  void Modify(int l, int r, T v, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return;
    if (rx <= r && lx >= l) {
      t_[x] += v;
      return;
    }
    const auto m = (lx + rx) / 2;
    Modify(l, r, v, 2*x+1, lx, m);
    Modify(l, r, v, 2*x+2, m, rx);
  }

  T Get(int i, int x, int lx, int rx) {
    if (lx + 1 == rx)
      return t_[x];
    const auto m = (lx + rx) / 2;
    if (i < m)
      return Get(i, 2*x+1, lx, m) + t_[x];
    return Get(i, 2*x+2, m, rx) + t_[x];
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, m; cin >> n >> m;
  vl a(n);
  SegTree tree(a);
  FOR(j, 0, m-1) {
    int op; cin >> op;
    if (op == 1) {
      int l, r, v; cin >> l >> r >> v;
      tree.Modify(l, r, v);
    } else {
      int i; cin >> i;
      cout << tree.Get(i) << '\n';
    }
  }
}

[[maybe_unused]] void TestSolution() {
  std::istringstream cin("5 5\n"
                         "1 0 3 3\n"
                         "2 1\n"
                         "1 2 4 4\n"
                         "2 3\n"
                         "2 4\n"s);
  std::ostringstream cout;
  std::string expected_cout("3\n"
                            "4\n"
                            "0\n");
  Solution(cin, cout);
  const auto actual_cout = cout.str();
  assert(actual_cout == expected_cout);
  std::cerr << "TestSolution OK" << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
//#ifndef NDEBUG
//  TestSolution();
//#endif
  Solution(std::cin, std::cout);
  return 0;
}
