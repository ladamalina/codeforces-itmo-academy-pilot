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

constexpr ll NO_OP = LLONG_MAX;

struct Node {
  int l = 0, r = 0;
  Node* le = nullptr;
  Node* ri = nullptr;
  ll sum = 0, max = 0, set = NO_OP;
};

void SetNodeD(Node* x, ll d) {
  x->sum = d * (x->r - x->l + 1);
  x->max = d <= 0 ? 0 : x->sum;
  x->set = d;
}

void Combine(Node* x) {
  x->sum = x->le->sum + x->ri->sum;
  x->max = std::max(x->le->max, x->le->sum + x->ri->max);
}

void Propagate(Node* x) {
  if (x->set == NO_OP || x->l == x->r) return;
  const auto m = (x->l + x->r) / 2;
  if (!x->le) x->le = new Node(x->l, m);
  if (!x->ri) x->ri = new Node(m+1, x->r);
  SetNodeD(x->le, x->set);
  SetNodeD(x->ri, x->set);
  x->set = NO_OP;
}

void Modify(Node* x, int l, int r, ll d) {
  if (x->r < l || r < x->l) return;
  if (l <= x->l && x->r <= r) {
    SetNodeD(x, d);
    return;
  }
  Propagate(x);
  const auto m = (x->l + x->r) / 2;
  if (!x->le) x->le = new Node(x->l, m);
  if (!x->ri) x->ri = new Node(m+1, x->r);
  if (l <= m) Modify(x->le, l, r, d);
  if (r > m) Modify(x->ri, l, r, d);
  Combine(x);
}

int Query(Node* x, ll h) {
  Propagate(x);

  if (x->max <= h) return x->r;
  // x->max > h

  if (x->l == x->r) return x->l - 1;
  // x->l < x->r

  if (!x->le && !x->ri) return x->l - 1;
  // x->le && x->ri

  if (x->le->max > h) return Query(x->le, h);
  return Query(x->ri, h - x->le->sum);
}

void Solution(std::istream& cin, std::ostream& cout) {
  int n; cin >> n;

  auto root = new Node(1, n);
  while (true) {
    char op; cin >> op;
    if (op == 'E') break;
    if (op == 'I') {
      int a, b, d; cin >> a >> b >> d;
      Modify(root, a, b, d);
    } else if (op == 'Q') {
      int h; cin >> h;
      const auto res = Query(root, h);
      cout << res << '\n';
    }
  }
}

#ifndef NDEBUG
[[maybe_unused]] std::stringstream ReadFile(const std::string& path) {
  std::ifstream file(path);
  assert(file);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  return ss;
}

[[maybe_unused]] void RunTest(const std::string& in_path, const std::string& out_path) {
  std::stringstream cin = ReadFile(in_path);
  std::stringstream cout;
  const auto e_out = ReadFile(out_path).str();
  const auto start_t = std::chrono::high_resolution_clock::now();
  Solution(cin, cout);
  const auto end_t = std::chrono::high_resolution_clock::now();
  const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
  std::cerr << in_path << ", "sv << total_t << " ms"sv << std::endl;
  const auto a_out = cout.str();
  assert(a_out == e_out);
}

[[maybe_unused]] void TestSolution() {
  const std::string dir("../"s);
  RunTest(dir + "input1.txt"s, dir + "output1.txt"s);
  std::cerr << "TestSolution OK"sv << std::endl;
}
#endif

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
