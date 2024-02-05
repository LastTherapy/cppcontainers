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
    node *prev;
    // Конструктор узла для удобства
    node(const T &d, node *nx = nullptr, node *pw = nullptr)
        : data(d), next(nx), prev(pw) {}
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
      p->next->prev = p;
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
      p->next->prev = p;
      p = p->next;
    }
    tail = p;
    count = items.size();
  }

  // copy constructor
  list(const list &l) {}
  // move constructor
  list(list &&l) {}

  // destructor
  ~list() {}

  // --------I T E R A T O R------------------------------------------ //

  class ListIterator {
  public:
    ListIterator(node *ptr, node *tl = nullptr) : current(ptr), tail(tl){};

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

    //--it
    ListIterator &operator--() {
      if (current == nullptr) {
        current = tail;
        tail = nullptr;
      } else
        current = current->prev;
      return (*this);
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

    node *getCurrent() { return current; }

    friend ListIterator list<T>::insert(ListIterator pos,
                                        const_reference value);
    friend void list<T>::erase(ListIterator pos);
    friend void list<T>::splice(const_iterator pos, list &other)

  private:
    node *current;
    // furry moment
    node *tail;
  }; // end of ListIterator
  // ------E N D---I T E R A T O R-------//

  using iterator = ListIterator;
  using const_iterator = const ListIterator;

  // List Element access
  const_reference front() { return head->data; }
  const_reference back() { return tail->data; }

  // List Iterators
  iterator begin() { return iterator(head); };
  iterator end() { return iterator(nullptr, tail); }

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
      node *new_node = new node(value, pos.current, pos.current->prev);
      pos.current->prev->next = new_node;
      pos.current->prev = new_node;
      count++;
      return iterator(new_node);
    }
  }

  void erase(iterator pos) {
    node *temp = pos.current;
    if (!temp)
      return;
    if (temp == head) {
      head = head->next;
      if (head) {
        head->prev = nullptr;
      } else {
        tail = nullptr;
      }
    } else if (temp == tail) {
      tail = temp->prev;

      if (tail) {
        tail->next = nullptr;
      } else {
        head = nullptr;
      }
    } else {
      // !
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
    }

    --count;
    delete temp;
  }

  void push_back(const_reference value) {
    // list is empty
    if (head == nullptr) {
      head = new node(value);
      tail = head;
    } else {
      tail->next = new node(value, nullptr, tail);
      tail = tail->next;
    }
    count++;
  }

  void pop_back() {
    if (tail == nullptr)
      return;
    if (tail == head) {
      clear();
    } else {
      node *temp = tail;
      tail = tail->prev;
      tail->next = nullptr;
      delete temp;
      count--;
    }
  }

  void push_front(const_reference value) {
    // list is empty
    if (head == nullptr) {
      head = new node(value);
      tail = head;
    } else {
      node *new_node = new node(value, head);
      head->prev = new_node;
      head = new_node;
    }
    count++;
  }

  void pop_front() {
    if (head == nullptr)
      return;
    if (tail == head) {
      clear();
    } else {
      node *temp = head;
      head = head->next;
      head->prev = nullptr;
      delete temp;
      count--;
    }
  }

  void swap(list &other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(count, other.count);
  }


  void merge(list &other) {
    iterator it = this->begin();
    while (!other.empty()) {
      T value = std::move(other.front());
       while (it != this->end() && *it < value) { ++it; }
      this->insert(it, std::move(value));
      other.pop_front();
    }
  }

  void splice(const_iterator pos, list &other) {
     if (pos == begin()) {
          other.tail->next = head;
          head->prev = other.tail;
          count += other.count;
          head = other.head;
          other = nullptr;    
      }
  }
  void reverse() {}
  void unique() {}
  void sort() {}

  node *getHead() { return head; }

private:
  // void swap(node* a, node *b) {
  //   if (a == b) return;
  //   else if (a->next == b) {

  //   }

  //   std::swap(a->next, b->next);
  //   std::swap(a->prev, b->prev);

  //   if (a->next)  a->next->prev = a;
  //   if (b->next) b->next->prev = b;
  //   if (a->prev) a->prev->next = a;
  //   if (b->prev) b->prev.next = b;

  //   if (head == a) head = b;
  //   if (head == b) head = a;
  //   if (tail == a) tail = b;
  //   if (tail == b) tail = a;

  // }

  node *head;
  node *tail;

  size_t count;
};
#endif