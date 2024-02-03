#ifndef LIST_H
#define LIST_H
#include <iterator>

template <typename T> class list {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using pointer = T *;

  // структура узла внутри класса
  typedef struct node {
    T data;
    node *next;
    node *prew;
    // Конструктор узла для удобства
    node(const T &d, node *nx = nullptr, node *pw = nullptr) : data(d), next(nx), prew(pw) {}
  } node;

public:
  // инициализируем список из 0 элементов
  list() : head(nullptr), tail(nullptr), count(0) {}

  // создаем список с n пустыми элементами
  list(size_type n) : head(nullptr), tail(nullptr), count(0) {
    if (n == 0)
      return;
    head = new node(T());
    node *p = head;
    for (size_type i = 1; i < n; i++) {
      p->next = new node(T());
      p->next->prew = p;
      p = p->next;
    }
    tail = p;
    count = n;
  }

  list(std::initializer_list<T> const &items) {
    if (items.size() == 0)
      return;

    auto it = items.begin();
    head = new node(*it, nullptr);
    node *p = head;
    for (++it; it != items.end(); ++it) {
      p->next = new node(*it, nullptr);
      p->next->prew = p;
      p = p->next;
    }
    tail = p;
    count = items.size();
  }

  // --------I T E R A T O R------------------------------------------ //

  class ListIterator {
  public:
    ListIterator(node *ptr) : current(ptr){};

    reference operator*() const { return current->data; }
    pointer operator->() { return &(current->data); }

    ListIterator &operator++() {
      current = current->next;
      return (*this);
    }

    ListIterator operator++(int) {
      ListIterator temp = *this;
      ++(*this);
      return temp;
    }

    ListIterator &operator--() {  
    }

    ListIterator operator--(int) {
      ListIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const ListIterator &other) const {
      return current == other.current;
    }
    bool operator!=(const ListIterator &other) const {
      return current != other.current;
    }

  private:
    node *current;
  }; // end of ListIterator

  using iterator = ListIterator;
  using const_iterator = const ListIterator;

  // List Element access
  const_reference front() { return head->data; }
  const_reference back() { return tail->data; }

  // List Iterators
  iterator begin() { return iterator(head); };
  iterator end() { return iterator(nullptr); }

  // List Capacity
  bool empty() { return count == 0 ? true : false; }
  size_type size() { return count; }
  size_type max_size() { return count; }

  // List Modifiers
  void clear() {
    node *current = head;
    while (current != nullptr) {
      node *next = current->next;
      delete current;
      current = next;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
  }
  iterator insert(iterator pos, const_reference value) {
    if (pos == begin()) {
      push_front(value); // +count in push front
      return begin();
    } else if (pos == end()) {
      push_back(value);
      return iterator(tail);
    } else {
      node *current = pos.current;
      node *temp_prew  = current->prew;
      current->prew = new node(value, current, temp_prew);
      count++;
      return (iterator(current->prew));
      // node *current = head;
      // while (current != nullptr && iterator(current->next) != pos)
      //   current = current->next;

      // if (current) {
      //   node *temp = current->next;
      //   current->next = new node(value, temp);
      //   count++;
      //   return iterator(current->next);
      // } else {
      //   return end();
      // }
    }
  }

  void erase(iterator pos) {}

  void push_back(const_reference value) {
    node *new_node = new node(value);
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      tail->next = new node(value);
      tail = tail->next;
    }
    count++;
  }

  void pop_back() {}

  void push_front(const_reference value) {
    node *temp = head;
    head = new node(value);
    head->next = temp;
    if (temp == nullptr) {
      tail = head;
    }
    count++;
  }

  void pop_front() {}
  void swap(list &other) {}
  void merge(list &other) {}
  void splice(const_iterator pos, list &other) {}
  void reverse() {}
  void unique() {}
  void sort() {}

node *getHead()  {
    return head;
}
private:
  node *head;
  node *tail;

  size_t count;
};
#endif