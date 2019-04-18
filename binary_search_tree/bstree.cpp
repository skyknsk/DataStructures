#include "bstree.hpp"

/*
  Node functions
*/
template <typename TYPE>
void Node<TYPE>::InsertLeft(const TYPE val) {
  Node<TYPE> *left = new Node<TYPE>{val};
  left_ = left;
}

template <typename TYPE>
void Node<TYPE>::InsertRight(const TYPE val) {
  Node<TYPE> *right = new Node<TYPE>{val};
  right_ = right;
}

template <typename TYPE>
void Node<TYPE>::InsertVal(const TYPE val) {
  if(val_ > val) {
    if(left_ == nullptr) {
      InsertLeft(val);
    }
    else {
      left_->InsertVal(val);
    }
  }
  else {
    if(right_ == nullptr) {
      InsertRight(val);
    }
    else {
      right_->InsertVal(val);
    }
  }
}

template <typename TYPE>
Node<TYPE> *Node<TYPE>::GetMaxValNode() {
  if(right_ == nullptr) {
    return this;
  }
  else {
    return right_->GetMaxValNode();
  }
}

template <typename TYPE>
Node<TYPE> *Node<TYPE>::RemoveVal(const TYPE val) {
  if(this == nullptr) {
    return nullptr;
  }
  else if(val_ > val) {
    left_ = left_->RemoveVal(val);
  }
  else if(val_ < val) {
    right_ = right_->RemoveVal(val);
  }
  else if(val_ == val) {
    if(left_ == nullptr) {
      auto q = right_;
      delete this;
      return q;
    }
    else if(left_->right_ == nullptr) {
      auto q = left_;
      q->right_ = right_;
      delete this;
      return q;
    }
    else {
      Node<TYPE> *q;
      for(q = left_; q->right_->right_ != nullptr; q = q->right_);
      auto r = q->right_;
      q->right_ = r->left_;
      r->left_ = left_;
      r->right_ = right_;
      delete this;
      return r;
    }
  }
  return this;
}

template <typename TYPE>
bool Node<TYPE>::FindVal(const TYPE val) const {
  if(val_ == val) {
    return true;
  }
  else {
    if(val_ > val and left_ != nullptr) {
      return left_->FindVal(val);
    }
    else if(val_ <= val and right_ != nullptr) {
      return right_->FindVal(val);
    }
  }
  return false;
}

template <typename TYPE>
void Node<TYPE>::ShowVal() const {
  std::cout << "(" << val_;
  if(left_ != nullptr)
    left_->ShowVal();
  if(right_ != nullptr)
    right_->ShowVal();
  std::cout << ")";
}

/*
  BSTree functions
*/
template <typename TYPE>
void BSTree<TYPE>::Insert(const TYPE val) {
  if(root_ == nullptr) {
    Node<TYPE> *root = new Node<TYPE>{val};
    root_ = root;
  }
  else {
    root_->InsertVal(val);
  }
}

template <typename TYPE>
void BSTree<TYPE>::InsertAll(const std::vector<TYPE> vals) {
  for(auto val : vals) {
    if(root_ == nullptr) {
      Node<TYPE> *root = new Node<TYPE>{val};
      root_ = root;
    }
    else {
      root_->InsertVal(val);
    }
  }
}

template <typename TYPE>
void BSTree<TYPE>::Remove(const TYPE val) {
  if(root_ != nullptr) {
    root_ = root_->RemoveVal(val);
  }
}


template <typename TYPE>
bool BSTree<TYPE>::Find(const TYPE val) const {
  if(root_ == nullptr) {
    return false;
  }
  else {
    return root_->FindVal(val);
  }
}

template <typename TYPE>
void BSTree<TYPE>::Show() const {
  if(root_ != nullptr) {
    root_->ShowVal();
    std::cout << std::endl;
  }
}

int main() {
  BSTree<int> tree;
  tree.InsertAll(std::vector<int>{7, 2, 1, 5, 4});
  tree.InsertAll(std::vector<int>{15, 10, 8, 11, 17, 16, 19});
  tree.Show();

  tree.Remove(15);
  tree.Show();

  return 0;
}
