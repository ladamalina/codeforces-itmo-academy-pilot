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

class SegTree { // K-я единица
 public:
  struct Node { int sum = 0; };

  explicit SegTree(const std::vector<int>& a) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_ = std::vector<Node>(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  int GetNthIdx(int i) {
    return GetNthIdx(i + 1, 0, 0, size_);
  }

  void Invert(int i) {
    Invert(i, 0, 0, size_);
  }

 private:
  std::vector<Node> t_;
  int size_ = 1;

  static Node Combine(const Node& a, const Node& b) {
    return {a.sum + b.sum};
  }

  void Init(const std::vector<int>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) t_[x] = {a[lx]};
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
    }
  }

  int GetNthIdx(int i, int x, int lx, int rx) {
    if (lx + 1 == rx) return lx;
    const auto m = (lx + rx) / 2;
    if (t_[2*x+1].sum >= i)
      return GetNthIdx(i, 2*x+1, lx, m);
    return GetNthIdx(i - t_[2*x+1].sum, 2*x+2, m, rx);
  }

  void Invert(int i, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = {1 - t_[x].sum};
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Invert(i, 2*x+1, lx, m);
    else Invert(i, 2*x+2, m, rx);
    t_[x] = Combine(t_[2*x+1], t_[2*x+2]);
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, m;
  cin >> n >> m;
  vi a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  SegTree tree(a);
  for (int j = 0; j < m; ++j) {
    int op, i;
    cin >> op >> i;
    if (op == 1) {
      tree.Invert(i);
    } else {
      cout << tree.GetNthIdx(i) << '\n';
    }
  }
}

[[maybe_unused]] void TestSolution() {
  {
    std::istringstream cin("5 7\n"
                           "1 1 0 1 0\n"
                           "2 0\n"
                           "2 1\n"
                           "2 2\n"
                           "1 2\n"
                           "2 3\n"
                           "1 0\n"
                           "2 0\n"s);
    std::ostringstream cout;
    std::string expected_cout("0\n"
                              "1\n"
                              "3\n"
                              "3\n"
                              "1\n"s);
    Solution(cin, cout);
    const auto actual_cout = cout.str();
    assert(actual_cout == expected_cout);
  }
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
