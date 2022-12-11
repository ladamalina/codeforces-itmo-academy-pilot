#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using namespace std::literals;

template<typename T>
class SegmentTreeMin {
 public:
  explicit SegmentTreeMin(const std::vector<T>& a)
    : INF(std::numeric_limits<T>::max()) {
    while (size_ < a.size()) size_ *= 2;
    tree.resize(size_ * 2 - 1, INF);
    Init(a, 0, 0, size_);
  }

  [[nodiscard]] T Min(size_t l, size_t r) {
    return Min(l, r, 0, 0, size_);
  }

  void Set(size_t i, T v) {
    Set(i, v, 0, 0, size_);
  }

 private:
  std::vector<T> tree;
  size_t size_ = 1;
  const T INF;

  void Init(const std::vector<T>& a, size_t x, size_t lx, size_t rx) {
    if (lx + 1 == rx) {
      if (lx < a.size()) tree[x] = a[lx];
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      tree[x] = std::min(tree[2*x+1], tree[2*x+2]);
    }
  }

  [[nodiscard]] T Min(size_t l, size_t r, size_t x, size_t lx, size_t rx) {
    if (rx <= l || lx >= r) return INF;
    if (rx <= r && lx >= l) return tree[x];
    const auto m = (lx + rx) / 2;
    return std::min(Min(l, r, 2*x+1, lx, m), Min(l, r, 2*x+2, m, rx));
  }

  void Set(size_t i, T v, size_t x, size_t lx, size_t rx) {
    if (lx + 1 == rx) {
      tree[x] = v;
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) {
      Set(i, v, 2*x+1, lx, m);
    } else {
      Set(i, v, 2*x+2, m, rx);
    }
    tree[x] = std::min(tree[2*x+1], tree[2*x+2]);
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  uint64_t n, m;
  cin >> n >> m;
  std::vector<uint64_t> a(n);
  for (uint64_t i = 0; i < n; ++i) cin >> a[i];
  SegmentTreeMin<uint64_t> tree(a);
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
      const auto min_a = tree.Min(l, r);
      cout << min_a << '\n';
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
