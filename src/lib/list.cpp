#include "list.h"
#include <iostream>
#include <list>

// template <typename T>
// list<T>::list() : head(nullptr), tail(nullptr), data(nullptr), num(0) {}

// template <typename T>
// list<T>::list(size_t n) {
//     if (n == 0) return list();

//     head = new node(T())
//     node *p = head;
//     for (size_t i = 1; i < n; i++)
//     {
//        p->next = new node(T())
//        p = p->next;
//     }
//     tail = p;
//     num = n;
// }

// template <typename T>
// list<T>::list(std::initializer_list<T> const &items) {
//     // head = {T(), nullptr};
//     // node p = head;
//     // for (T i : items) {
//     //     p.next
//     // }
// }
int main() {
  std::list<int> x = {7, 0, 1, 2, 3};


  for (int n : x)
    std::cout << n << " ";
  std::cout  << std::endl;

  list<float> l = {7, 0, 1, 2, 3};
  std::cout << "size array: " << l.size() << std::endl;

  for (auto it = l.begin(); it != l.end(); ++it) {
    // *it теперь ссылается на текущий элемент списка.
    std::cout <<  *it << " "; // Вывод текущего элемента.
  }
  return 0;
}