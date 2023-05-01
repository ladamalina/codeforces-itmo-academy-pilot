#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std::literals;

class SegmentTree {
 public:
  struct Node { int max = -1; };

  explicit SegmentTree(const std::vector<int>& a) {
    while (size_ < a.size()) size_ *= 2;
    tree_ = std::vector<Node>(size_ * 2 - 1, BASE);
    Init(a, 0, 0, static_cast<int>(size_));
  }

  [[nodiscard]] int GetLowerBound(int i, int v) {
    return GetLowerBound(i, v, 0, 0, static_cast<int>(size_));
  }

  void Set(int i, int v) {
    Set(i, v, 0, 0, static_cast<int>(size_));
  }

 private:
  std::vector<Node> tree_;
  size_t size_ = 1;
  const Node BASE;

  static Node Combine(const Node& a, const Node& b) {
    return {std::max(a.max, b.max)};
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

  [[nodiscard]] int GetLowerBound(int i, int v, int x, int lx, int rx) {
    if (i >= rx) return -1;
    // i < rx
    if (lx + 1 == rx) {
      return tree_[x].max >= v ? lx : -1;
    }
    const auto m = (lx + rx) / 2;
    if (tree_[2*x+1].max >= v) {
      auto l_lb = GetLowerBound(i, v, 2*x+1, lx, m);
      if (l_lb != -1) return l_lb;
    }
    if (tree_[2*x+2].max >= v) {
      return GetLowerBound(i, v, 2*x+2, m, rx);
    }
    return -1;
  }

  void Set(int i, int v, int x, int lx, int rx) {
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
  int n, m;
  cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  SegmentTree tree(a);
  int op, i, v;
  for (int j = 0; j < m; ++j) {
    cin >> op;
    if (op == 1) {
      cin >> i >> v;
      tree.Set(i, v);
    } else if (op == 2) {
      cin >> v >> i;
      cout << tree.GetLowerBound(i, v) << '\n';
    } else {
      throw std::runtime_error("Invalid operation: "s + std::to_string(op));
    }
  }
}

[[maybe_unused]] void TestSolution() {
  {
    std::istringstream cin("5 7\n"
                           "1 3 2 4 3\n"
                           "2 3 0\n"
                           "2 3 2\n"
                           "1 2 5\n"
                           "2 4 1\n"
                           "2 5 4\n"
                           "1 3 7\n"
                           "2 6 1\n"s);
    std::ostringstream cout;
    std::string expected_cout("1\n"
                              "3\n"
                              "2\n"
                              "-1\n"
                              "3\n"s);
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
