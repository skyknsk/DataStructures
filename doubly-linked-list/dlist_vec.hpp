#ifndef INCLUDE_GUARD_dlist_vec_
#define INCLUDE_GUARD_dlist_vec_

#include "doubly_linked_list.hpp"
#include <vector>

namespace skyknsk {

struct Seq {
  uint32_t symbol;
  DoublyLinkedList<Seq>::Node* next;
  DoublyLinkedList<Seq>::Node* prev;
};

using DList = DoublyLinkedList<Seq>;
using DNode = DoublyLinkedList<Seq>::Node;

template <class Value_Type>
class DListVec {
  public:
    static constexpr uint32_t kPoolSize = 100;

  private:
    std::vector<DList> dlist_vec_;
    std::stack<DNode*> pool_;
    size_t size_;

  public:
    DListVec() : size_(0) {
      dlist_vec_.resize(0);
      pool_alloc(kPoolSize);
    };
    DListVec(const size_t size);
    ~DListVec();

    //accessor
    DList & operator [] (const size_t idx) {
      assert(idx < size_);
      return dlist_vec_[idx];
    }

    // memory operator
    bool empty() const;
    size_t size() const;
    void resize(const size_t new_size);
    void pool_alloc(const size_t size);
};

template <class Value_Type>
DListVec<Value_Type>::DListVec(const size_t size) {
  dlist_vec_.resize(size);
  pool_alloc(kPoolSize);
  size_ = size;
  for(size_t i = 0; i < size; ++i) {
    dlist_vec_[i].set_pool(&pool_);
  }
}

template <class Value_Type>
DListVec<Value_Type>::~DListVec() {
  for(size_t i = 0; i < size_; ++i) {
    dlist_vec_[i].clear();
  }
  while(!pool_.empty()) {
    DNode* node = pool_.top();
    pool_.pop();
  }
  dlist_vec_.clear();
}

template <class Value_Type>
bool DListVec<Value_Type>::empty() const {
  return dlist_vec_.empty();
}

template <class Value_Type>
size_t DListVec<Value_Type>::size() const {
  return size_;
}

template <class Value_Type>
void DListVec<Value_Type>::resize(const size_t new_size) {
  dlist_vec_.resize(new_size);
  size_ = new_size;
  for(size_t i = 0; i < new_size; ++i) {
    dlist_vec_[i].set_pool(&pool_);
  }
}

template <class Value_Type>
void DListVec<Value_Type>::pool_alloc(const size_t size) {
  DNode* nodes = new DNode [size];
  for(size_t i = 0; i < size; ++i) {
    pool_.push(&nodes[i]);
  }
}

};

#endif