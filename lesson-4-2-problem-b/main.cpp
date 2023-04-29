#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std::literals;

class SegmentTree {
 public:
  struct Node { int sum = 0; };

  explicit SegmentTree(const std::vector<int>& a) {
    while (size_ < a.size()) size_ *= 2;
    tree_ = std::vector<Node>(size_ * 2 - 1, ZERO);
    Init(a, 0, 0, static_cast<int>(size_));
  }

  [[nodiscard]] int GetNthIdx(int i) {
    return GetNthIdx(i + 1, 0, 0, static_cast<int>(size_));
  }

  void Invert(int i) {
    Invert(i, 0, 0, size_);
  }

 private:
  std::vector<Node> tree_;
  size_t size_ = 1;
  const Node ZERO;

  static Node Combine(const Node& a, const Node& b) {
    return {a.sum + b.sum};
  }

  static Node InitOne(int v) {
    return {v};
  }

  void Init(const std::vector<int>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < static_cast<int>(a.size())) tree_[x] = InitOne(a[lx]);
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      tree_[x] = Combine(tree_[2*x+1], tree_[2*x+2]);
    }
  }

  [[nodiscard]] int GetNthIdx(int i, int x, int lx, int rx) {
    if (lx + 1 == rx) return lx;
    const auto m = (lx + rx) / 2;
    if (tree_[2*x+1].sum >= i) return GetNthIdx(i, 2*x+1, lx, m);
    else return GetNthIdx(i - tree_[2*x+1].sum, 2*x+2, m, rx);
  }

  void Invert(size_t i, size_t x, size_t lx, size_t rx) {
    if (lx + 1 == rx) {
      tree_[x] = InitOne(1 - tree_[x].sum);
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) {
      Invert(i, 2*x+1, lx, m);
    } else {
      Invert(i, 2*x+2, m, rx);
    }
    tree_[x] = Combine(tree_[2*x+1], tree_[2*x+2]);
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n, m;
  cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  SegmentTree tree(a);
  int op, i;
  for (int j = 0; j < m; ++j) {
    cin >> op >> i;
    if (op == 1) {
      tree.Invert(i);
    } else if (op == 2) {
      cout << tree.GetNthIdx(i) << '\n';
    } else {
      throw std::runtime_error("Invalid operation: "s + std::to_string(op));
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
#ifndef NDEBUG
  TestSolution();
#endif
  Solution(std::cin, std::cout);
  return 0;
}
