#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std::literals;

template<typename T>
class SegTree {
 public:
  explicit SegTree(const std::vector<T>& a) {
    while (size_ < static_cast<int>(a.size())) size_ *= 2;
    tree.resize(size_ * 2 - 1);
    Init(a, 0, 0, size_);
  }

  [[nodiscard]] T Sum(int l, int r) {
    return Sum(l, r, 0, 0, size_);
  }

  void Inc(int i) {
    Inc(i, 0, 0, size_);
  }

 private:
  std::vector<T> tree;
  int size_ = 1;

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < static_cast<int>(a.size())) tree[x] = a[lx];
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      tree[x] = tree[2*x+1] + tree[2*x+2];
    }
  }

  [[nodiscard]] T Sum(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return 0;
    if (rx <= r && lx >= l) return tree[x];
    const auto m = (lx + rx) / 2;
    return Sum(l, r, 2*x+1, lx, m) + Sum(l, r, 2*x+2, m, rx);
  }

  void Inc(int i, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      ++tree[x];
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) {
      Inc(i, 2*x+1, lx, m);
    } else {
      Inc(i, 2*x+2, m, rx);
    }
    tree[x] = tree[2*x+1] + tree[2*x+2];
  }
};

void Solution(std::istream& cin, std::ostream& cout) {
  int n;
  cin >> n;
  std::vector<int> a(n);
  SegTree<int> tree(a);
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    auto inv_sum = tree.Sum(num, static_cast<int>(a.size()));
    cout << inv_sum << ' ';
    tree.Inc(num - 1);
  }
}

[[maybe_unused]] void TestSolution() {
  std::istringstream cin("5\n"
                         "4 1 3 5 2"s);
  std::ostringstream cout;
  std::string expected_cout("0 1 1 0 3 ");
  Solution(cin, cout);
  const auto actual_cout = cout.str();
  assert(actual_cout == expected_cout);
  std::cerr << "TestSolution OK" << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
//#ifndef NDEBUG
//  TestSolution();
//#endif
  Solution(std::cin, std::cout);
  std::cout << std::endl;
  return 0;
}
