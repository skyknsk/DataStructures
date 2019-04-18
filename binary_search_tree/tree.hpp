#include <iostream>
#include <utility>
#include <vector>

template <typename TYPE>
class Node {
  private:
    TYPE val_;
    Node<TYPE> *left_;
    Node<TYPE> *right_;

  public:
    explicit Node(const TYPE &val, Node *left = nullptr, Node *right = nullptr)
      : val_{val},
        left_{left},
        right_{right} {}
    ~Node() {}

    // accessor
    TYPE GetVal() const;
    Node<TYPE> *GetLeftNode() const;
    Node<TYPE> *GetRightNode() const;
    Node<TYPE> *GetMaxValNode() ;

    void InsertLeft(const TYPE val);
    void InsertRight(const TYPE val);
    void InsertVal(const TYPE val);
    Node<TYPE> * RemoveVal(const TYPE val);
    bool FindVal(const TYPE val) const;
    void ShowVal() const;
};

template <typename TYPE>
class BSTree {
  private:
    Node<TYPE> *root_;

  public:
    explicit BSTree()
      : root_{nullptr} {}
    ~BSTree() {
      delete root_;  
    }

    void Insert(const TYPE val);
    void InsertAll(const std::vector<TYPE> vals);
    void Remove(const TYPE val);
    bool Find(const TYPE val) const;
    void Show() const;
};


template <typename TYPE>
inline TYPE Node<TYPE>::GetVal() const {
  return val_;
}

template <typename TYPE>
inline Node<TYPE> *Node<TYPE>::GetLeftNode() const {
  return left_;
}

template <typename TYPE>
inline Node<TYPE> *Node<TYPE>::GetRightNode() const {
  return right_;
}
