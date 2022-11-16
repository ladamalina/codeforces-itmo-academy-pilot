#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std::literals;

template<typename T>
class SegmentTreeSum {
 public:
  explicit SegmentTreeSum(const std::vector<T>& a) {
    while (size_ < a.size()) size_ *= 2;
    tree.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  [[nodiscard]] T Sum(size_t l, size_t r) {
    return Sum(l, r, 0, 0, size_);
  }

  void Set(size_t i, T v) {
    Set(i, v, 0, 0, size_);
  }

 private:
  std::vector<T> tree;
  size_t size_ = 1;

  void Init(const std::vector<T>& a, size_t x, size_t lx, size_t rx) {
    if (lx + 1 == rx) {
      if (lx < a.size()) tree[x] = a[lx];
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      tree[x] = tree[2*x+1] + tree[2*x+2];
    }
  }

  [[nodiscard]] T Sum(size_t l, size_t r, size_t x, size_t lx, size_t rx) {
    if (rx <= l || lx >= r) return 0;
    if (rx <= r && lx >= l) return tree[x];
    const auto m = (lx + rx) / 2;
    return Sum(l, r, 2*x+1, lx, m) + Sum(l, r, 2*x+2, m, rx);
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
    tree[x] = tree[2*x+1] + tree[2*x+2];
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  uint64_t n, m;
  cin >> n >> m;
  std::vector<uint64_t> a(n);
  for (uint64_t i = 0; i < n; ++i) cin >> a[i];
  SegmentTreeSum<uint64_t> tree(a);
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
      const auto s = tree.Sum(l, r);
      cout << s << '\n';
    }
  }
}

[[maybe_unused]] void TestSolution() {
  std::istringstream cin("5 5\n"
                         "5 4 2 3 5\n"
                         "2 0 3\n"
                         "1 1 1\n"
                         "2 0 3\n"
                         "1 3 1\n"
                         "2 0 5"s);
  std::ostringstream cout;
  std::string expected_cout("11\n"
                            "8\n"
                            "14\n");
  Solution(cin, cout);
  const auto actual_cout = cout.str();
  assert(actual_cout == expected_cout);
  std::cerr << "TestSolution OK" << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
#ifndef NDEBUG
  TestSolution();
#endif
  Solution(std::cin, std::cout);
  return 0;
}
