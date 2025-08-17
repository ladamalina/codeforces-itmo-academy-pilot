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
class SegTree { // Отрезок с максимальной суммой
 public:
  struct Node {
    T seg = 0, pref = 0, suff = 0, sum = 0;
    Node() = default;
    explicit Node(T v) : seg(std::max(v, T(0))), pref(std::max(v, T(0))), suff(std::max(v, T(0))), sum(v) {}
    Node(T seg_, T pref_, T suff_, T sum_) : seg(seg_), pref(pref_), suff(suff_), sum(sum_) {}
  };

  explicit SegTree(const std::vector<T>& a) {
    while (size_ < SZ(a)) size_ <<= 1;
    t_ = std::vector<Node>(size_ << 1);
    Init(a, 1, 0, size_);
  }

  T GetMaxSum() {
    return GetMaxSum(0, size_);
  }

  T GetMaxSum(int l, int r) {
    return GetMaxSum(l, r, 1, 0, size_).seg;
  }

  void Set(int i, T v) {
    Set(i, v, 1, 0, size_);
  }

 private:
  std::vector<Node> t_;
  int size_ = 1;

  Node Combine(const Node& a, const Node& b) {
    return {
      std::max(a.seg, std::max(b.seg, a.suff + b.pref)),
      std::max(a.pref, a.sum + b.pref),
      std::max(a.suff + b.sum, b.suff),
      a.sum + b.sum
    };
  }

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < SZ(a)) t_[x] = Node{a[lx]};
    } else {
      const auto m = (lx + rx) >> 1;
      Init(a, (x<<1), lx, m);
      Init(a, (x<<1)|1, m, rx);
      t_[x] = Combine(t_[(x<<1)], t_[(x<<1)|1]);
    }
  }

  [[nodiscard]] Node GetMaxSum(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return {};
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) >> 1;
    return Combine(GetMaxSum(l, r, (x<<1), lx, m), GetMaxSum(l, r, (x<<1)|1, m, rx));
  }

  void Set(int i, T v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = Node(v);
      return;
    }
    const auto m = (lx + rx) >> 1;
    if (i < m) Set(i, v, (x<<1), lx, m);
    else Set(i, v, (x<<1)|1, m, rx);
    t_[x] = Combine(t_[(x<<1)], t_[(x<<1)|1]);
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, m; cin >> n >> m;
  vl a(n);
  FOR(i, 0, n-1) {
    cin >> a[i];
  }
  SegTree tree(a);
  cout << tree.GetMaxSum() << '\n';
  FOR(j, 0, m-1) {
    int i; ll v; cin >> i >> v;
    tree.Set(i, v);
    cout << tree.GetMaxSum() << '\n';
  }
}

[[maybe_unused]] void TestSolution() {
  {
    std::istringstream cin("5 2\n"
                           "5 -4 4 3 -5\n"
                           "4 3\n"
                           "3 -1\n"s);
    std::ostringstream cout;
    std::string expected_cout("8\n"
                              "11\n"
                              "7\n"s);
    Solution(cin, cout);
    const auto actual_cout = cout.str();
    assert(actual_cout == expected_cout);
  }
  {
    std::istringstream cin("4 2\n"
                           "-2 -1 -5 -4\n"
                           "1 3\n"
                           "3 2\n"s);
    std::ostringstream cout;
    std::string expected_cout("0\n"
                              "3\n"
                              "3\n"s);
    Solution(cin, cout);
    const auto actual_cout = cout.str();
    assert(actual_cout == expected_cout);
  }
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
