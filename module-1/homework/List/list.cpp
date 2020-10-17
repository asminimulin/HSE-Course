#include "list.h"

#include <stdexcept>

task::list::list(): head_(nullptr), tail_(nullptr), size_(0) {}

task::list::list(size_t count, const int& value) {
  if (count == 0) {
    head_ = tail_ = nullptr;
    size_ = 0;
    return;
  }

  Node* inserter = new Node{nullptr, nullptr, value};
  head_ = inserter;

  for (size_t i = 1; i < count; ++i) {
    inserter->next_ = new Node{inserter, nullptr, value};
    inserter = inserter->next_;
  }

  tail_ = inserter;
  size_ = count;
}

task::list::list(const task::list& other) {
  // Other list is empty, so no need any allocations
  if (other.size_ == 0) {
    head_ = tail_ = nullptr;
    size_ = 0;
    return;
  }

  Node* cur = other.head_;
  Node* inserter = new Node{nullptr, nullptr, cur->value_};
  head_ = inserter;
  cur = cur->next_;

  for (size_t i = 1; i < other.size_; ++i) {
    inserter->next_ = new Node{inserter, nullptr, cur->value_};
    inserter = inserter->next_;
    cur = cur->next_;
  }

  tail_ = inserter;
  size_ = other.size_;
}

task::list::~list() { clear(); }

task::list& task::list::operator=(const task::list& other) {
  // Handle self assignment
  if (this == &other) {
    return *this;
  }

  if (other.empty()) {
    clear();
    return *this;
  }

  resize(other.size());

  Node* this_cur = head_;
  Node* other_cur = other.head_;
  while (this_cur != nullptr) {
    this_cur->value_ = other_cur->value_;
    this_cur = this_cur->next_;
    other_cur = other_cur->next_;
  }

  return *this;
}

int& task::list::front() {
  if (size_ == 0) {
    throw std::runtime_error("Cannot do list::front because list is empty");
  }
  return head_->value_;
}

const int& task::list::front() const {
  if (size_ == 0) {
    throw std::runtime_error("Cannot do list::front because list is empty");
  }
  return head_->value_;
}

int& task::list::back() {
  if (size_ == 0) {
    throw std::runtime_error("Cannot do list::back because list is empty");
  }
  return tail_->value_;
}

const int& task::list::back() const {
  if (size_ == 0) {
    throw std::runtime_error("Cannot do list::back because list is empty");
  }
  return tail_->value_;
}

bool task::list::empty() const {
  return size_ == 0;
}

size_t task::list::size() const { return size_; }

void task::list::clear() {
  if (empty()) {
    // No need to clear it if it is already empty
    return;
  }

  Node* cur = head_;
  while (cur != nullptr) {
    auto next = cur->next_;
    delete cur;
    cur = next;
  }

  size_ = 0;
  head_ = tail_ = nullptr;
}

void task::list::push_back(const int& value) {
  if (empty()) {

    tail_ = head_ = new Node{nullptr, nullptr, value};
    size_ = 1;

  } else {

    tail_->next_ = new Node{tail_, nullptr, value};
    tail_ = tail_->next_;
    size_++;

  }
}

void task::list::pop_back() {
  if (empty()) {
    throw std::runtime_error("Cannot do list::pop_back(): list is empty");
  }

  if (size_ == 1) {

    delete head_;
    tail_ = head_ = nullptr;
    size_ = 0;

  } else {

    tail_ = tail_->previous_;
    delete tail_->next_;
    tail_->next_ = nullptr;
    size_--;

  }
}

void task::list::push_front(const int& value) {
  if (empty()) {

    head_ = tail_ = new Node{nullptr, nullptr, value};
    size_ = 1;

  } else {

    head_->previous_ = new Node{nullptr, head_, value};
    head_ = head_->previous_;
    size_++;

  }
}

void task::list::pop_front() {
  if (empty()) {
    throw std::runtime_error("Cannot do list::pop_front(): list is empty");
  }

  if (size_ == 1) {

    delete head_;
    head_ = tail_ = nullptr;
    size_ = 0;

  } else {

    head_ = head_->next_;
    delete head_->previous_;
    head_->previous_ = nullptr;
    size_--;

  }
}

void task::list::resize(size_t count) {
  if (count == 0) {
    clear();
    return;
  }

  if (size_ == count) {
    // no need to do anything
    return;
  } else if (size_ > count) {

    Node* cur = head_;
    size_t pos = 0;
    while (pos < count) {
      cur = cur->next_;
      pos++;
    }

    tail_ = cur->previous_;
    tail_->next_ = nullptr;
    while (cur != nullptr) {
      Node* next = cur->next_;
      delete cur;
      cur = next;
    }

  } else {  // (size_ < count)

    Node* inserter = new Node{nullptr, nullptr, Node::ElementType()};
    head_ = inserter;
    for (size_t i = 1; i < count - size_; ++i) {
      inserter->next_ = new Node{inserter, nullptr, Node::ElementType()};
      inserter = inserter->next_;
    }

    tail_ = inserter;

  }
  size_ = count;
}

void task::list::swap(task::list& other) {
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

void task::list::remove(const int& value) {
  Node* cur = head_;
  Node* delete_later = nullptr;
  while (cur != nullptr) {
    if (cur->value_ == value) {
      if (cur->previous_ != nullptr) {
        cur->previous_->next_ = cur->next_;
      }

      if (cur->next_ != nullptr) {
        cur->next_->previous_ = cur->previous_;
      }

      Node* next = cur->next_;

      if (cur == head_) {
        head_ = next;
      }

      if (cur == tail_) {
        tail_ = cur->previous_;
      }

      if (std::addressof(value) != std::addressof(cur->value_)) {
        delete cur;
      } else {
        delete_later = cur;
      }

      cur = next;
      size_--;
    } else {
      cur = cur->next_;
    }
  }

  if (delete_later != nullptr) {
    delete delete_later;
  }
}

void task::list::unique() {
  Node* cur = head_;
  while (cur != nullptr) {
    while (cur->next_ != nullptr && cur->next_->value_ == cur->value_) {

      Node* next_next = cur->next_->next_;
      delete cur->next_;
      cur->next_ = next_next;

      if (next_next == nullptr) {
        tail_ = cur;
      }

      size_--;
    }

    if (cur->next_ != nullptr) {
      cur->next_->previous_ = cur;
    }

    cur = cur->next_;
  }
}

void task::list::sort() {
  if (empty()) {
    // no need to do anything
    return;
  }

  // All Node::previous_ pointers would be broken after HoareSort and
  // I would be to fix them up
  // And also I need to get correct pointer to tail_
  HoareSort(head_, size_);

  // Fix up pointers
  Node* cur = head_;
  cur->previous_ = nullptr;

  while (cur->next_ != nullptr) {
    cur->next_->previous_ = cur;
    cur = cur->next_;
  }

  tail_ = cur;
}

/**
 * It is private function so I can break the whole internal structure
 * of the object. To improve performance I do not care the Node::previous_
 * pointers. So outside code for that method needs to fix up the these pointers
 * after operation complete.
 *
 * Also need to mention, that I do not split this whole method into several
 * separate methods because I want to avoid function calls time and memory
 * overhead
 *
 * The algorithm:
 * 1. choose the element called pivot
 * 2. split the whole array into left part, center part and right part
 *    a) every element from left part is less then pivot
 *    b) every element from center part is equal to the pivot
 *    c) every element from right part is greater the pivot
 * 3. If left part is not empty then sort it recursively
 * 4. If right part is not empty then sort it recursively
 * 5. Merge parts back into one array
 *
 * @param nodes - array needs to be sorted
 * @param size - size of array
 */
void task::list::HoareSort(task::list::Node*& nodes, size_t size) {
  Node* pivot;
  {  // Get pivot
    size_t pivot_pos = random() % size;
    size_t pos = 0;
    pivot = nodes;

    while (pos + 1 < pivot_pos) {
      pivot = pivot->next_;
      pos++;
    }
  }

  Node *left = nullptr, *right = nullptr;
  size_t left_size = 0, right_size = 0;
  Node* center = nullptr;
  {  // Get left part, center and right part
    Node *left_inserter = nullptr, *center_inserter = nullptr,
         *right_inserter = nullptr;
    Node* cur = nodes;
    while (cur != nullptr) {

      Node* next = cur->next_;

      if (cur->value_ < pivot->value_) {

        if (left == nullptr) {
          left = left_inserter = cur;
        } else {
          left_inserter->next_ = cur;
          left_inserter = left_inserter->next_;
        }

        left_inserter->next_ = nullptr;
        left_size++;

      } else if (cur->value_ > pivot->value_) {

        if (right == nullptr) {
          right = right_inserter = cur;
        } else {
          right_inserter->next_ = cur;
          right_inserter = right_inserter->next_;
        }

        right_inserter->next_ = nullptr;
        right_size++;

      } else {  // (cur->value_ == pivot->value_)

        if (center == nullptr) {
          center = center_inserter = cur;
        } else {
          center_inserter->next_ = cur;
          center_inserter = center_inserter->next_;
        }

        center_inserter->next_ = nullptr;

      }
      cur = next;
    }

  }

  {  // Sort parts
    if (left != nullptr) {
      HoareSort(left, left_size);
    }

    if (right != nullptr) {
      HoareSort(right, right_size);
    }
  }

  auto JoinList = [](Node*& inserter, Node* list) {
    Node* cur = list;
    while (cur != nullptr) {
      inserter->next_ = cur;
      cur = cur->next_;
      inserter = inserter->next_;
    }

    inserter->next_ = nullptr;
  };

  if (left != nullptr) {

    Node* last_node = left;
    while (last_node->next_ != nullptr) {
      last_node = last_node->next_;
    }

    JoinList(last_node, center);
    JoinList(last_node, right);
    nodes = left;

  } else if (center != nullptr) {

    Node* last_node = center;
    while (last_node->next_ != nullptr) {
      last_node = last_node->next_;
    }

    JoinList(last_node, right);
    nodes = center;

  } else {
    nodes = right;
  }
}
