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
class SegTree {
 public:
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  T Sum(int l, int r) {
    return Sum(l, r, 0, 0, size_);
  }

  void Inc(int i) {
    Inc(i, 0, 0, size_);
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
      t_[x] = t_[2*x+1] + t_[2*x+2];
    }
  }

  T Sum(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return 0;
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) / 2;
    return Sum(l, r, 2*x+1, lx, m) + Sum(l, r, 2*x+2, m, rx);
  }

  void Inc(int i, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      ++t_[x];
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Inc(i, 2*x+1, lx, m);
    else Inc(i, 2*x+2, m, rx);
    t_[x] = t_[2*x+1] + t_[2*x+2];
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n;
  cin >> n;
  std::vector<int> a(n);
  SegTree tree(a);
  FOR(i, 0, n-1) {
    int num; cin >> num;
    const auto inv_sum = tree.Sum(num, a.size());
    cout << inv_sum << ' ';
    tree.Inc(num - 1);
  }
}

[[maybe_unused]] void TestSolution() {
  std::istringstream cin("5\n"
                         "4 1 3 5 2"s);
  std::ostringstream cout;
  const auto e_out = "0 1 1 0 3 "s;
  Solution(cin, cout);
  const auto a_out = cout.str();
  assert(a_out == e_out);
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
// #ifndef NDEBUG
//   TestSolution();
// #endif
  Solution(std::cin, std::cout);
  std::cout << std::endl;
  return 0;
}
