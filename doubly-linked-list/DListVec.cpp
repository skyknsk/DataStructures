#include "DListVec.hpp"

using namespace skyknsk;

int main() {

  {
    DListVec<Seq> list;
    list.resize(1);
    list[0].push_back({1, nullptr, nullptr});
    list[0].print_struct();
  }

  {
    DListVec<Seq> list(10);
    list[0].push_back({1, nullptr, nullptr});
    list[0].print_struct();
    
    list[1].push_front({2, nullptr, nullptr});
    list[1].print_struct();
  }

  {
    DListVec<Seq> list(2);
    list.pool_alloc(10);
    list[0].push_front({1, nullptr, nullptr});
  }
  return 0;
}