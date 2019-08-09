#ifndef INCLUDE_GUARD_DOUBLY_LINKED_LIST
#define INCLUDE_GUARD_DOUBLY_LINKED_LIST

#include <initializer_list>
#include <stack>
#include <iterator>
#include <iostream>
#include <utility>
#include <assert.h>

namespace skyknsk {

template<class Value_Type>
class DoublyLikedList {
  public:
    class Node {
      public:
        Value_Type data;
        Node* next;
        Node* prev;
    };

  private:
    Node* head_;  // Pointer to head node(dummy)
    size_t capacity_; 
    size_t size_; // Current size without dummy node
    std::stack<Node*>* pool_ptr_; // Pointer to pool of unused nodes

  public:
    // default constructor
    DoublyLikedList(std::stack<Node*>* stack_ptr = nullptr) {
      std::cout << "constructor\n";
      initialize(stack_ptr);
    };

    // initializer_list constructor 
    DoublyLikedList(
      std::initializer_list<Value_Type> init, 
      std::stack<Node*>* stack_ptr = nullptr
    );

    // destructor
    ~DoublyLikedList();

    // copy constructor
    DoublyLikedList(
      const DoublyLikedList& other, 
      std::stack<Node*>* stack_ptr = nullptr
    ) {
      std::cout << __func__  << "_copy" << std::endl;
      initialize(stack_ptr);
      Node* ptr = head_;
      Node* other_ptr = other.head_->next;

      while(other_ptr != other.head_) {
        if(ptr->next == head_) {
          insert_after_ptr(ptr, other_ptr->data);
        }
        else {
          ptr->next->data = other_ptr->data;
        }
        ptr = ptr->next;
        other_ptr = other_ptr->next;
      }
      size_ = other.size_;
    }

    // copy assignment
    DoublyLikedList & operator = (const DoublyLikedList& other) {
      std::cout << __func__  << "_copy\n";
      if(this != &other) {
        Node* ptr = head_;
        Node* other_ptr = other.head_->next;

        while(other_ptr != other.head_) {
          if(ptr->next == head_) {
            insert_after_ptr(ptr, other_ptr->data);
          }
          else {
            ptr->next->data = other_ptr->data;
          }
          ptr = ptr->next;
          other_ptr = other_ptr->next;
        }
        size_ = other.size_;
      }
      return *this;
    }

    void initialize(std::stack<Node*>* stack_ptr);
    void set_pool(std::stack<Node*>* stack_ptr);
    void print();
    void print_struct();

    // accessor
    Node & operator [] (const size_t idx) {
      assert(idx < size_);
      Node* ptr = head_->next;
      for(size_t i = 0; i < idx; ++i) {
        ptr = ptr->next;
      }
      return *ptr;
    };
    Node* front();
    Node* back();
    Node* next(
      Node* ptr, 
      const size_t n = 1
    );
    Node* prev(
      Node* ptr, 
      const size_t n = 1
    );

    // memory operatotr
    bool empty();
    size_t size();
    void resize(const size_t new_size);
    Node* make_node();

    // list operatator
    void insert(
      const size_t idx, 
      const Value_Type val
    );
    void insert_ptr(
      Node* ptr,
      const Value_Type val
    );
    void insert_ptr(
      Node* ptr,
      const std::initializer_list<Value_Type> vals
    );
    void insert_after_ptr(
      Node* ptr,
      const Value_Type val
    );
    void insert_after_ptr(
      Node* ptr,
      const std::initializer_list<Value_Type> vals
    );
    void erase(const size_t idx);
    void erase(
      const size_t first,
      const size_t last
    );
    void erase_ptr(Node* ptr);
    void push_front(const Value_Type val);
    void push_back(const Value_Type val);
    void pop_front();
    void pop_back();
    void clear();
};

template<class Value_Type>
DoublyLikedList<Value_Type>::DoublyLikedList(
  std::initializer_list<Value_Type> init,
  std::stack<Node*>* stack_ptr
) {
  std::cout << __func__ << std::endl;
  initialize(stack_ptr);
  size_ = init.size();

  Node* prev = head_;
  for(auto& val : init) {
    Node* new_node = make_node();
    new_node->data = val;
    new_node->prev = prev;
    prev->next = new_node;
    prev = new_node;
  }
  prev->next = head_;
  head_->prev = prev;
}

template<class Value_Type>
DoublyLikedList<Value_Type>::~DoublyLikedList() {
  clear();
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::initialize(std::stack<Node*>* stack_ptr) {
  size_ = 0;
  capacity_ = 0;
  pool_ptr_ = stack_ptr;
  Node* dummy = make_node();
  head_ = dummy;
  dummy->next = dummy->prev = dummy;
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::set_pool(std::stack<Node*>* stack_ptr) {
  pool_ptr_ = stack_ptr;
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::print() {
  if(empty()) {
    std::cout << "empty" << std::endl;
  }
  else {
    Node* ptr = head_->next;
    while(ptr != head_) {
      std::cout << ptr->data << " ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::print_struct() {
  if(empty()) {
    std::cout << "empty" << std::endl;
  }
  else {
    Node* ptr = head_->next;
    while(ptr != head_) {
      std::cout << ptr->data.symbol << " ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}

template<class Value_Type>
typename DoublyLikedList<Value_Type>::Node* DoublyLikedList<Value_Type>::next(
    Node* ptr, 
    const size_t n
) {
  for(size_t i = 0; i < n; ++i) {
    if(ptr->next == head_) {
      break;
    }
    ptr = ptr->next;
  }
  return ptr;
}

template<class Value_Type>
typename DoublyLikedList<Value_Type>::Node* DoublyLikedList<Value_Type>::prev(
    Node* ptr, 
    const size_t n
) {
  for(size_t i = 0; i < n; ++i) {
    if(ptr->prev == head_) {
      break;
    }
    ptr = ptr->prev;
  }
  return ptr;
}

template<class Value_Type>
bool DoublyLikedList<Value_Type>::empty() {
  return size_ == 0;
}

template<class Value_Type>
size_t DoublyLikedList<Value_Type>::size() {
  return size_;
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::resize(const size_t new_size) {
  /*
    if size_ < new_size, push_back node
   */
  if(size_ < new_size) {
  }
  else {

  }

  size_ = new_size;
}

template<class Value_Type>
typename DoublyLikedList<Value_Type>::Node* DoublyLikedList<Value_Type>::make_node() {
  Node* new_node;
  if(pool_ptr_ == nullptr || (*pool_ptr_).empty()) {
    new_node = new Node;
  }
  else {
    std::cout << "make\n";
    new_node = (*pool_ptr_).top();
    (*pool_ptr_).pop();
  }
  return new_node;
}

template<class Value_Type>
typename DoublyLikedList<Value_Type>::Node* DoublyLikedList<Value_Type>::front() {
  return head_->next;
}

template<class Value_Type>
typename DoublyLikedList<Value_Type>::Node* DoublyLikedList<Value_Type>::back() {
  return head_->prev;
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::insert(
  const size_t idx,
  const Value_Type val
) {
  Node* pos = head_;
  if(idx <= size_/2) {
    pos = pos->next;
    for(size_t i = 0; i < idx; ++i) {
      pos = pos->next;
    }
  }
  else {
    pos = pos->prev;
    for(size_t i = 1; i < size_ - idx; ++i) {
      pos = pos->prev;
    }
  }

  Node* new_node = make_node();
  new_node->data = val;
  new_node->next = pos;
  new_node->prev = pos->prev;
  pos->prev->next = new_node;
  pos->prev = new_node;
  ++size_;
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::insert_ptr(
  Node* ptr,
  const Value_Type val
) {
  Node* new_node = make_node();
  new_node->data = val;
  new_node->next = ptr;
  new_node->prev = ptr->prev;
  ptr->prev->next = new_node;
  ptr->prev = new_node;
  ++size_;
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::insert_ptr(
  Node* ptr,
  const std::initializer_list<Value_Type> vals
) {
  for(auto& val : vals) {
    Node* new_node = make_node();
    new_node->data = val;
    new_node->next = ptr;
    new_node->prev = ptr->prev;
    ptr->prev->next = new_node;
    ptr->prev = new_node; 
  }
  size_ += vals.size();
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::insert_after_ptr(
  Node* ptr,
  const Value_Type val
) {
  Node* new_node = make_node();
  ptr->next->prev = new_node;
  new_node->data = val;
  new_node->next = ptr->next;
  new_node->prev = ptr;
  ptr->next = new_node;
  ++size_;
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::insert_after_ptr(
  Node* ptr,
  const std::initializer_list<Value_Type> vals
) {
  for(auto val_itr = std::rbegin(vals); val_itr != std::rend(vals); ++val_itr) {
    Node* new_node = make_node();
    ptr->next->prev = new_node;
    new_node->data = *val_itr;
    new_node->next = ptr->next;
    new_node->prev = ptr;
    ptr->next = new_node;
  }
  size_ += vals.size();
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::erase(const size_t idx) {
  Node* pos = head_;
  if(idx <= size_/2) {
    pos = pos->next;
    for(size_t i = 0; i < idx; ++i) {
      pos = pos->next;
    }
  }
  else {
    pos = pos->prev;
    for(size_t i = 1; i < size_ - idx; ++i) {
      pos = pos->prev;
    }
  }

  pos->prev->next = pos->next;
  pos->next->prev = pos->prev;

  --size_;
  if(pool_ptr_ != nullptr) {
    (*pool_ptr_).push(pos);
  }
  else {
    delete pos;
  }
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::erase(
  const size_t first,
  const size_t last
) {

}

template<class Value_Type>
void DoublyLikedList<Value_Type>::erase_ptr(Node* ptr) {
  ptr->prev->next = ptr->next;
  ptr->next->prev = ptr->prev;
  --size_;
  if(pool_ptr_ != nullptr) {
    (*pool_ptr_).push(ptr);
  }
  else {
    delete ptr;
  }
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::push_front(const Value_Type val) {
  insert(0, val);
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::push_back(const Value_Type val) {
  insert(size_, val);
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::pop_front() {
  if(!empty()) {
    erase(0);
  }
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::pop_back() {
  if(!empty()) {
    erase(size_ - 1);
  }
}

template<class Value_Type>
void DoublyLikedList<Value_Type>::clear() {
  while(!empty()) {
    pop_front();
  }
}

};

#endif