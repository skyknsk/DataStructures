#include <iostream>
#include <vector>
#include <cstdint>

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

    void Solve(const TYPE q, const std::vector<TYPE> &p, const std::vector<TYPE> &x, const std::vector<TYPE> &y);

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
void UFTree<TYPE>::Solve(const TYPE q, const std::vector<TYPE> &p, const std::vector<TYPE> &x, const std::vector<TYPE> &y) {
  for(TYPE i=0; i<q; ++i) {
    if(p[i] == 0) {
      Merge(x[i], y[i]);
    }
    else {
      if(IsSame(x[i], y[i])) {
        std::cout << "Yes\n";
      }
      else {
        std::cout << "No\n";
      }
    }
  }
}

int main() {
  uint N, Q;
  std::cin >> N >> Q;

  std::vector<uint> P(Q);
  std::vector<uint> A(Q);
  std::vector<uint> B(Q);

  for(uint i=0; i<Q; ++i) {
    std::cin >> P[i] >> A[i] >> B[i];
  }

  UFTree<uint> tree(N);
  tree.Solve(Q, P, A, B);

  return 0;
}
