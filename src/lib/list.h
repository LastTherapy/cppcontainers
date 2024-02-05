#ifndef LIST_H
#define LIST_H
#include <iostream>
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
  list(const list &l) {
    for (element : this) {
      element
    }
  }
  // move constructor
  list(list &&l) {}

  // destructor
  ~list() {}

  // --------I T E R A T O R------------------------------------------ //

  class ListIterator {
  public:
    ListIterator(node *ptr, node *tl = nullptr) : current(ptr), tail(tl) {}

    // сначала думал что нужно переопределить оператор копирования, но потом осталось, что не нужно

    // ListIterator(const ListIterator &other) {
    //   current = other.current;
    //   tail = other.tail;
    // }

    // ListIterator(ListIterator &&i) : current(i.current), tail(i.tail) {}

    // ~ListIterator() {}

    // ListIterator &operator=(const ListIterator &other) {
    //   if (this != &other) {
    //     current = other.current;
    //     tail = other.tail;
    //   }
    //   return *this;
    // }

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
    friend void list<T>::splice(const ListIterator pos, list &other);
    friend void list<T>::reverse();

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
      while (it != this->end() && *it < value) {
        ++it;
      }
      this->insert(it, std::move(value));
      other.pop_front();
    }
  }

  void splice(const_iterator pos, list &other) {
    if (other.empty() || this == &other)
      return;

    if (pos == begin()) {
      other.tail->next = head;
      head->prev = other.tail;
      head = other.head;
    } else if (pos == end()) {
      tail->next = other.head;
      other.head->prev = tail;
      tail = other.tail;
    } else {
      pos.current->prev->next = other.head;
      other.head->prev = pos.current->prev;

      other.tail->next = pos.current;
      pos.current->prev = other.tail;
    }
    count += other.count;
    // other to null
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
  }
  void reverse() {
    if (this->count <= 1)
      return;
    for (iterator it_left = this->begin(), it_right = --this->end();
         it_left != it_right && it_left.current != it_right.current->next;
         ++it_left, --it_right) {
      std::swap(it_left.current->data, it_right.current->data);
    }
  }

  void unique() {
    if (empty() || head == tail)
      return;
    auto current = begin();

    while (current != end()) {
      auto next = current;
      ++next;

      while (next != end()) {
        if (*current == *next) {
          auto temp = next;
          ++next;
          erase(temp);
        } else {
          break;
        }
      }
      if (next != end()) {
        current = next;
      } else {
        break;
      }
    }
  }

  // just buble for example ((
  void sort() {
    if (empty() || head == tail)
      return;

    auto start = begin();
    auto end_marker = end();
    while (start != end_marker)
    {

    auto max = start;
    auto v = max;
    ++v;
    while (v != end_marker) {
      // std::cout << "v is " << *v << " , max is " << *max << std::endl;
      if (*max > *v) {
        // std::cout << "swaping " << *max << " wtidh " << *v << std::endl;
        std::swap(*v, *max);
        max = v;

      } else {        
        max = v;
        // std::cout << "new max is " << *max;
      }
      ++v;
    }
    --end_marker;
    }
  }
  // bool swapped;
  // auto end_marker = end();
  // do {
  //     swapped = false;
  //     auto current = begin();
  //     auto next = current;
  //     ++next;

  //     while (next != end_marker) {
  //         if (*current > *next) {
  //             std::swap(*current, *next);
  //             swapped = true;
  //         }
  //         ++current;
  //         ++next;
  //     }
  //     end_marker = current; // Уменьшаем диапазон сортировки
  // } while (swapped);

private:
  node *head;
  node *tail;
  size_t count;
};
#endif