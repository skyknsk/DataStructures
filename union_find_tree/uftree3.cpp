#include <iostream>
#include <vector>
#include <cstdint>
#include <set>

#define uint uint32_t

template <typename TYPE>
class UFTree {
  private:
    std::vector<TYPE> par;
    std::vector<TYPE> rank;

  public:
    explicit UFTree(TYPE n)
      : par{n}, rank{n}
    {
      for(TYPE i=0; i<n; ++i) {
        par[i] = i;
        rank[i] = 0;
      }
    }
    ~UFTree() {
      par.clear();
      rank.clear();
      par.shrink_to_fit();
      par.shrink_to_fit();
    }

    void Solve(const TYPE n, const TYPE m, const std::vector<TYPE> &a, const std::vector<TYPE> &b);

  private:
    TYPE GetRoot( TYPE x);
    bool IsSame( TYPE x,  TYPE y) ;
    void Merge(TYPE x, TYPE y);
};

template <typename TYPE>
inline TYPE UFTree<TYPE>::GetRoot( TYPE x) {
  return par[x] == x ? x : par[x] = GetRoot(par[x]);
}

template <typename TYPE>
inline bool UFTree<TYPE>::IsSame( TYPE x,  TYPE y)  {
  return GetRoot(x) == GetRoot(y);
}

template <typename TYPE>
void UFTree<TYPE>::Merge(TYPE x, TYPE y) {
  x = GetRoot(x);
  y = GetRoot(y);
  if(x == y)
    return;

  if(rank[x] < rank[y]) {
    par[x] = y;
  }
  else {
    par[y] = x;
    if(rank[x] == rank[y])
      ++rank[x];
  }
}

template <typename TYPE>
void UFTree<TYPE>::Solve(const TYPE n, const TYPE m, const std::vector<TYPE> &a, const std::vector<TYPE> &b) {
  for(TYPE i=0; i<m; ++i) {
    Merge(a[i], b[i]);
  }

  std::set<TYPE> st;
  for(TYPE i=0; i<n; ++i) {
    TYPE root = GetRoot(i);
    if(st.count(root) == 0) {
      st.insert(root);
    }
  }

  std::cout << st.size() - 1 << std::endl;
}

int main() {
  uint N, M;
  std::cin >> N >> M;

  std::vector<uint> A(M);
  std::vector<uint> B(M);

  for(uint i=0; i<M; ++i) {
    std::cin >> A[i] >> B[i];
  }

  UFTree<uint> tree(N);
  tree.Solve(N, M, A, B);

  return 0;
}
