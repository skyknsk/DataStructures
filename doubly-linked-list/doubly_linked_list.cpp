#include "doubly_linked_list.hpp"
#include <vector>

using namespace skyknsk;

struct Seq {
  uint32_t symbol;
  DoublyLikedList<Seq>::Node* next;
  DoublyLikedList<Seq>::Node* prev;
};

int main() {
  {
    std::stack<DoublyLikedList<uint32_t>::Node*> stack;
    DoublyLikedList<uint32_t>::Node* node = new DoublyLikedList<uint32_t>::Node;
    stack.push(node);

    DoublyLikedList<uint32_t> list({1, 2, 3, 4, 5}, &stack);
    std::cout << "list_size = " << list.size() << std::endl;
    list.print();
    list.pop_back();
    list.print();
    list.erase(3);
    list.pop_back();
    list.pop_back();
    list.print();
    list.pop_front();
    list.print();

    list.push_front(10);
    list.push_back(11);
    list.print();

    list.insert_after_ptr(list.front(), 5);
    list.print();
    list.insert_after_ptr(list.back(), 100);
    list.print();
    list.insert_after_ptr(list.next(list.front(), 2), {55, 56});
    list.print();
    list.insert_ptr(list.front(), {10, 20});
    list.print();

    DoublyLikedList<uint32_t> list2(list);
    DoublyLikedList<uint32_t> list3({1, 2});
    list3.print();
    list3 = list;
    list3.print();

    DoublyLikedList<Seq> list4({{3, nullptr, nullptr}});
    list4.print_struct();

  }

  {
    std::stack<DoublyLikedList<uint32_t>::Node*> stack;
    DoublyLikedList<uint32_t>::Node* node = new DoublyLikedList<uint32_t>::Node;
    stack.push(node);

    std::cout << "dlist_array\n";
    std::vector<DoublyLikedList<uint32_t>> list;
      list.resize(5);

    list[0].push_front(1);
    list[0].print();
    std::cout << list.size() << std::endl;
    for(auto x : list) {
      x.print();
    }
  }
  return 0;
}

