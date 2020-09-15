#pragma once
#include <cstddef>

namespace task {

class list {
 public:
  list();
  list(size_t count, const int& value = int());
  list(const list& other);

  ~list();
  list& operator=(const list& other);

  int& front();
  const int& front() const;

  int& back();
  const int& back() const;

  bool empty() const;
  size_t size() const;
  void clear();

  void push_back(const int& value);
  void pop_back();
  void push_front(const int& value);
  void pop_front();
  void resize(size_t count);
  void swap(list& other);

  void remove(const int& value);
  void unique();
  void sort();


 private:
  struct Node;

  static void HoareSort(Node*& nodes, size_t size);

  struct Node {
    // Note: task.md says I need to implement list only for int.
    using ElementType = int;

    Node* previous_;
    Node* next_;
    ElementType value_;
  };

  Node* head_;
  Node* tail_;
  size_t size_;
};

}  // namespace task
