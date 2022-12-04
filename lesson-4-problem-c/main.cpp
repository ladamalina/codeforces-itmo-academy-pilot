#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using namespace std::literals;

template<typename T>
class SegmentTreeMinCount {
 public:
  using Node = std::pair<T, size_t>;

  explicit SegmentTreeMinCount(const std::vector<T>& a)
    : INF(std::numeric_limits<T>::max()) {
    while (size_ < a.size()) size_ *= 2;
    tree.resize(size_ * 2 - 1, {INF, 0});
    Init(a, 0, 0, size_);
  }

  [[nodiscard]] Node MinCount(size_t l, size_t r) {
    return MinCount(l, r, 0, 0, size_);
  }

  void Set(size_t i, T v) {
    Set(i, v, 0, 0, size_);
  }

 private:
  std::vector<Node> tree;
  size_t size_ = 1;
  const T INF;

  Node Combine(const Node& a, const Node& b) {
    if (a.first < b.first) return a;
    if (a.first > b.first) return b;
    return {a.first, a.second + b.second};
  }

  void Init(const std::vector<T>& a, size_t x, size_t lx, size_t rx) {
    if (lx + 1 == rx) {
      if (lx < a.size()) tree[x] = {a[lx], 1};
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      tree[x] = Combine(tree[2*x+1], tree[2*x+2]);
    }
  }

  [[nodiscard]] Node MinCount(size_t l, size_t r, size_t x, size_t lx, size_t rx) {
    if (rx <= l || lx >= r) return {INF, 0};
    if (rx <= r && lx >= l) return tree[x];
    const auto m = (lx + rx) / 2;
    return Combine(MinCount(l, r, 2*x+1, lx, m), MinCount(l, r, 2*x+2, m, rx));
  }

  void Set(size_t i, T v, size_t x, size_t lx, size_t rx) {
    if (lx + 1 == rx) {
      tree[x] = {v, 1};
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Set(i, v, 2*x+1, lx, m);
    else Set(i, v, 2*x+2, m, rx);
    tree[x] = Combine(tree[2*x+1], tree[2*x+2]);
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  uint64_t n, m;
  cin >> n >> m;
  std::vector<uint64_t> a(n);
  for (uint64_t i = 0; i < n; ++i) cin >> a[i];
  SegmentTreeMinCount<uint64_t> tree(a);
  int op;
  size_t i, l, r;
  uint64_t v;
  for (uint64_t j = 0; j < m; ++j) {
    cin >> op;
    if (op == 1) {
      cin >> i >> v;
      tree.Set(i, v);
    } else {
      cin >> l >> r;
      const auto mc_a = tree.MinCount(l, r);
      cout << mc_a.first << ' ' << mc_a.second << '\n';
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
#ifndef NDEBUG
  TestSolution();
#endif
  Solution(std::cin, std::cout);
  return 0;
}
