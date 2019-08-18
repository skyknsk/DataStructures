#include "doubly_linked_list.hpp"
#include <vector>

using namespace skyknsk;

struct Seq {
  uint32_t symbol;
  DoublyLinkedList<Seq>::Node* next;
  DoublyLinkedList<Seq>::Node* prev;
};

int main() {
  // push_front
  { 
    std::cout << "##### push_front ##### " << std::endl;

    DoublyLinkedList<uint32_t> list;
    list.push_front(1);
    list.push_front(2);
    list.print();

    DoublyLinkedList<uint32_t> list2({1});
    list2.push_front(2);
    list2.push_front(3);
    list2.print();

    std::stack<DoublyLinkedList<uint32_t>::Node*> stack;
    DoublyLinkedList<uint32_t>::Node* node = new DoublyLinkedList<uint32_t>::Node;
    stack.push(node);

    DoublyLinkedList<uint32_t> list3(&stack);
    list3.push_front(1);
    if(stack.empty()) {
      std::cout << "stack is empty" << std::endl;
    }
    list3.push_front(2);
    list3.print();

    std::cout << std::endl;
  }

  // push_back
  {
    std::cout << "##### push_back ##### " << std::endl;

    DoublyLinkedList<uint32_t> list;
    list.push_back(1);
    list.push_back(2);
    list.print();

    DoublyLinkedList<uint32_t> list2({1});
    list2.push_back(2);
    list2.push_back(3);
    list2.print();

    std::cout << std::endl;
  }

  // front
  {
    std::cout << "##### front ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    std::cout << list.front()->data << std::endl;

    list.front()->data = 10;
    list.print();

    std::cout << std::endl;
  }

  // back
  {
    std::cout << "##### back ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    std::cout << list.back()->data << std::endl;

    list.back()->data = 10;
    list.print();

    std::cout << std::endl;
  }

  // current_node
  {
    std::cout << "##### current_node ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    list.front();
    std::cout << list.current_node()->data << std::endl;

    list.back();
    std::cout << list.current_node()->data << std::endl;

    std::cout << std::endl;
  }

  // next
  {
    std::cout << "##### next ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    auto current = list.front();
    std::cout << list.current_node()->data << std::endl;

    current = list.next(current);
    std::cout << list.current_node()->data << std::endl;

    current = list.next(current, 2);
    std::cout << list.current_node()->data << std::endl;

    std::cout << std::endl;
  }

  // prev
  {
    std::cout << "##### prev ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    auto current = list.back();
    std::cout << list.current_node()->data << std::endl;

    current = list.prev(current);
    std::cout << list.current_node()->data << std::endl;

    current = list.prev(current, 2);
    std::cout << list.current_node()->data << std::endl;

    std::cout << std::endl;
  }

  // empty
  {
    std::cout << "##### empty ##### " << std::endl;

    DoublyLinkedList<uint32_t> list;
    if(list.empty()) {
      std::cout << "list is empty" << std::endl;
    }

    DoublyLinkedList<uint32_t> list2({1, 2});
    list2.pop_back();
    list2.pop_front();
    if(list.empty()) {
      std::cout << "list2 is empty" << std::endl;
    }

    std::cout << std::endl;
  }

  // size
  {
    std::cout << "##### size ##### " << std::endl;

    DoublyLinkedList<uint32_t> list;
    std::cout << list.size() << std::endl;

    DoublyLinkedList<uint32_t> list2({1, 2});
    std::cout << list2.size() << std::endl;

    std::cout << std::endl;
  }

  // insert
  {
    std::cout << "##### insert ##### " << std::endl;

    DoublyLinkedList<uint32_t> list;
    list.insert(0, 10);
    list.print();

    DoublyLinkedList<uint32_t> list2({1, 2, 3});
    list2.insert(0, 10);
    list2.print();

    list2.insert(4, 11);
    list2.print();

    list2.insert(2, 12);
    list2.print();

    std::cout << std::endl;
  }

  // insert_ptr
  {
    std::cout << "##### insert_ptr ##### " << std::endl;

    DoublyLinkedList<uint32_t> list;
    auto current = list.current_node();
    list.insert_ptr(current, 10);
    list.print();

    DoublyLinkedList<uint32_t> list2({1, 2, 3});
    auto current2 = list2.front();
    current2 = list2.insert_ptr(current2, 11);
    list2.print();

    current2 = list2.next(current2);
    list2.insert_ptr(current2, 12);
    list2.print();

    std::cout << std::endl;
  }

  // insert_after_ptr
  {
    std::cout << "##### insert_after_ptr ##### " << std::endl;

    DoublyLinkedList<uint32_t> list;
    auto current = list.current_node();
    list.insert_after_ptr(current, 10);
    list.print();

    DoublyLinkedList<uint32_t> list2({1, 2, 3});
    auto current2 = list2.front();
    current2 = list2.insert_after_ptr(current2, 11);
    list2.print();

    current2 = list2.next(current2);
    list2.insert_after_ptr(current2, 12);
    list2.print();

    std::cout << std::endl;
  }

  // erase
  {
    std::cout << "##### erase ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    list.erase(0);
    list.print();

    list.erase(3);
    list.print();

    std::cout << std::endl;
  }

  // pop_front
  {
    std::cout << "##### pop_front ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    list.pop_front();
    list.print();

    list.pop_front();
    list.print();

    std::cout << std::endl;
  }

  // pop_back
  {
    std::cout << "##### pop_back ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    list.pop_back();
    list.print();

    list.pop_back();
    list.print();
    
    std::cout << std::endl;
  }

  // clear
  {
    std::cout << "##### clear ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    list.clear();
    list.print();
    
    std::cout << std::endl;
  }

  // constructor
  {
    std::cout << "##### constructor ##### " << std::endl;

    DoublyLinkedList<uint32_t> list;
    list.print();

    DoublyLinkedList<uint32_t> list2({1, 2, 3, 4, 5});
    list2.print();

    DoublyLinkedList<uint32_t> list3(list2);
    list3.print();

    std::cout << std::endl;
  }

  // copy assignment
  {
    std::cout << "##### copy assignment ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    DoublyLinkedList<uint32_t> list2({5, 4, 3, 4, 5});
    DoublyLinkedList<uint32_t> list3({5, 4, 3});
    DoublyLinkedList<uint32_t> list4({5, 4, 3, 4, 5, 6});

    list = list2;
    list.print();

    list = list3;
    list.print();

    list = list4;
    list.print();

    std::cout << std::endl;
  }

  // accessor
  {
    std::cout << "##### accessor ##### " << std::endl;

    DoublyLinkedList<uint32_t> list({1, 2, 3, 4, 5});
    list[0].data = 10;
    list[4].data = 20;
    list.print();
    
    std::cout << std::endl;
  }

  // DoublyLinkedList<Seq>
  {
    std::cout << "##### DoublyLinkedList<Seq> ##### " << std::endl;
    
    DoublyLinkedList<Seq> list4({{3, nullptr, nullptr}});
    list4.print_struct();

    std::cout << std::endl;
  }

  // dlist_vec
  {
    std::cout << "##### dlist_vec #####" << std::endl;

    std::vector<DoublyLinkedList<uint32_t>> list(5);
    list[0].push_front(1);
    list[4].push_back(5);

    for(auto x : list) {
      x.print();
    }

    std::cout << std::endl;
  }

  return 0;
}

