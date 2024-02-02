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
    // Конструктор узла для удобства
    node(const T &d, node *nd = nullptr) : data(d), next(nd) {}
  } node;

public:
  // инициализируем список из 0 элементов
  list() : head(nullptr), tail(nullptr), count(0) {}

  // создаем список с n пустыми элементами
  list(size_t n) : head(nullptr), tail(nullptr), count(0) {
    if (n == 0)
      return;
    head = new node(T());
    node *p = head;
    for (size_t i = 1; i < n; i++) {
      p->next = new node(T());
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

    bool operator==(ListIterator &other) { return current == other.current; }
    bool operator!=(const ListIterator &other) {
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
  bool empty();
  size_type size();
  size_type max_size();

  // List Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

private:
  node *head;
  node *tail;

  size_t count;
};
#endif