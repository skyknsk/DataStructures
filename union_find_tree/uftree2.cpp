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
      rank.shrink_to_fit();
    }

    void Solve(const TYPE N, const TYPE M, const std::vector<TYPE> &p, const std::vector<TYPE> &x, const std::vector<TYPE> &y);

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
void UFTree<TYPE>::Solve(const TYPE N, const TYPE M, const std::vector<TYPE> &p, const std::vector<TYPE> &x, const std::vector<TYPE> &y) {
  for(TYPE i=0; i<N; ++i) {
    Merge(x[i]-1, y[i]-1);
  }

  TYPE count = 0;
  for(TYPE i=0; i<M; ++i) {
    if(IsSame(i, p[i]-1)) {
      ++count;
    }
  }
  std::cout << count << std::endl;
}

int main() {
  uint N, M;
  std::cin >> N >> M;

  std::vector<uint> P(N);
  for(uint i=0; i<N; ++i) {
    std::cin >> P[i];
  }

  std::vector<uint> X(N), Y(N);
  for(uint i=0; i<N; ++i) {
    std::cin >> X[i] >> Y[i];
  }

  UFTree<uint> tree(N);
  tree.Solve(N, M, P, X, Y);

  return 0;
}
