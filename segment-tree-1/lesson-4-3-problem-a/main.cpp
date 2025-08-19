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
class SegTree {
 public:
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < SZ(a)) size_ <<= 1;
    t_.resize(size_ << 1);
    Init(a, 1, 0, size_);
  }

  T Sum(int l, int r) {
    return Sum(l, r, 1, 0, size_);
  }

  void Inc(int i) {
    Inc(i, 1, 0, size_);
  }

 private:
  std::vector<T> t_;
  int size_ = 1;

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < SZ(a)) t_[x] = a[lx];
    } else {
      const auto m = (lx + rx) >> 1;
      Init(a, (x<<1), lx, m);
      Init(a, (x<<1)|1, m, rx);
      t_[x] = t_[(x<<1)] + t_[(x<<1)|1];
    }
  }

  T Sum(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return 0;
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) >> 1;
    return Sum(l, r, (x<<1), lx, m) + Sum(l, r, (x<<1)|1, m, rx);
  }

  void Inc(int i, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      ++t_[x];
      return;
    }
    const auto m = (lx + rx) >> 1;
    if (i < m) Inc(i, (x<<1), lx, m);
    else Inc(i, (x<<1)|1, m, rx);
    t_[x] = t_[(x<<1)] + t_[(x<<1)|1];
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
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifndef NDEBUG
  TestSolution();
#endif
  Solution(std::cin, std::cout);
  return 0;
}
