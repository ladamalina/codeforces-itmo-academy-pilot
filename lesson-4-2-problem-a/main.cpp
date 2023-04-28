#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std::literals;

template<typename T>
class SegmentTree {
 public:
  struct Node {
    T seg = 0;
    T pref = 0;
    T suf = 0;
    T sum = 0;
  };

  explicit SegmentTree(const std::vector<T>& a) {
    while (size_ < a.size()) size_ *= 2;
    tree_ = std::vector<Node>(size_ * 2 - 1, ZERO);
    Init(a, 0, 0, size_);
  }

  [[nodiscard]] T MaxSum() {
    return MaxSum(0, size_);
  }

  [[nodiscard]] T MaxSum(size_t l, size_t r) {
    return MaxSum(l, r, 0, 0, size_).seg;
  }

  void Set(size_t i, T v) {
    Set(i, v, 0, 0, size_);
  }

 private:
  std::vector<Node> tree_;
  size_t size_ = 1;
  const Node ZERO{0, 0, 0, 0};

  Node Combine(const Node& a, const Node& b) {
    return {
      std::max(a.seg, std::max(b.seg, a.suf + b.pref)),
      std::max(a.pref, a.sum + b.pref),
      std::max(a.suf + b.sum, b.suf),
      a.sum + b.sum
    };
  }

  Node InitOne(T v) {
    return {std::max(v, 0ll), std::max(v, 0ll), std::max(v, 0ll), v};
  }

  void Init(const std::vector<T>& a, size_t x, size_t lx, size_t rx) {
    if (lx + 1 == rx) {
      if (lx < a.size()) tree_[x] = InitOne(a[lx]);
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      tree_[x] = Combine(tree_[2*x+1], tree_[2*x+2]);
    }
  }

  [[nodiscard]] Node MaxSum(size_t l, size_t r, size_t x, size_t lx, size_t rx) {
    if (rx <= l || lx >= r) return ZERO;
    if (rx <= r && lx >= l) return tree_[x];
    const auto m = (lx + rx) / 2;
    return Combine(MaxSum(l, r, 2*x+1, lx, m), MaxSum(l, r, 2*x+2, m, rx));
  }

  void Set(size_t i, T v, size_t x, size_t lx, size_t rx) {
    if (lx + 1 == rx) {
      tree_[x] = InitOne(v);
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) {
      Set(i, v, 2*x+1, lx, m);
    } else {
      Set(i, v, 2*x+2, m, rx);
    }
    tree_[x] = Combine(tree_[2*x+1], tree_[2*x+2]);
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int64_t n, m;
  cin >> n >> m;
  std::vector<int64_t> a(n);
  for (int64_t i = 0; i < n; ++i) cin >> a[i];
  SegmentTree<int64_t> tree(a);
  cout << tree.MaxSum() << '\n';
  size_t i;
  int64_t v;
  for (int64_t j = 0; j < m; ++j) {
    cin >> i >> v;
    tree.Set(i, v);
    cout << tree.MaxSum() << '\n';
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
//#ifndef NDEBUG
//  TestSolution();
//#endif
  Solution(std::cin, std::cout);
  return 0;
}
